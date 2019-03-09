#-*- coding: utf-8 -*-
# mongoDB connection method
# mongo -u "db20131526" -p "db20131526" --authenticationDatabase "db20131526": mongo -u "db20131526" -p "db20131526" --authenticationDatabase "db20131526"
import datetime
import time
import sys
import MeCab
import operator
from pymongo import MongoClient
from bson import ObjectId
from itertools import combinations
reload(sys)
sys.setdefaultencoding('utf-8')

DBname = "db20131526"
conn = MongoClient('dbpurple.sogang.ac.kr')
db = conn[DBname]
db.authenticate(DBname, DBname)

def printMenu():
    print "0. CopyData"
    print "1. Morph"
    print "2. print morphs"
    print "3. print wordset"
    print "4. frequent item set"
    print "5. association rule"

stop_word = {}
def make_stop_word():
    f=open("wordList.txt", 'r')
    while True:
        line = f.readline()
        if not line: break
        stop_word[line.strip('\n')] = line.strip('\n')
    f.close()

def morphing(content):
#형태소 분석기 불러오기
    t = MeCab.Tagger('-d/usr/local/lib/mecab/dic/mecab-ko-dic')
#형태소 분석 및 불용어 제거
    nodes = t.parseToNode(content.encode('utf-8'))
    MorpList = []
    while nodes:
        if nodes.feature[0] == 'N' and nodes.feature[1] == 'N':
            w = nodes.surface
            if not w in stop_word:
                try:
                    w = w.encode('utf-8')
                    MorpList.append(w)
                except:
                    pass
        nodes = nodes.next
    return MorpList

def p0():
#CopyData news to news_freq
    col1 = db['news']
    col2 = db['news_freq']
    col2.drop()

    for doc in col1.find():
        contentDic = {}
        for key in doc.keys():#[ "_id", "title", ... ]
            if key != "_id":# "_id"는 스스로 저장되나??
                contentDic[key] = doc[key] #store all key except "_id"
        col2.insert(contentDic)

def p1():
#Morph news and update news db
#MongoDB에 저장
    for doc in db['news_freq'].find():
        doc['morph'] = morphing(doc['content'])
        db['news_freq'].update({"_id":doc['_id']}, doc)#여기서 "_id"를 업데이트 한다.

def p2(url):
#input : news url
#output: news morphs
    col1 = db['news_freq']
    for doc in col1.find():
        if doc['url'] == url:
            for word in doc['morph']:
                print word

def p3():
#copy news morph to new db named news_wordset
    col1 = db['news_freq']
    col2 = db['news_wordset']
    col2.drop()
    for doc in col1.find():
        new_doc = {}
        new_set = set()
        for w in doc['morph']: #[ "전주", "문요한", ...]
            new_set.add(w.encode('utf-8'))
        new_doc['word_set'] = list(new_set)
        new_doc['url'] = doc['url']
        col2.insert(new_doc)

def p4(url):
#input  : news url
#output : news wordset
    col1 = db['news_wordset']
    for doc in col1.find():
        if doc['url'] == url:
            for word in doc['word_set']:
                print word

def p5(length):
#make frequent item_set
#and inset new dbs(dbname = candidate_L+"legnth")
#ex) l-th frequent item set dbbname = candidate_L1
    col1 = db['news_wordset']
    col2 = db['candidate_L1']
    col2.drop()
    ##########################
    ### freq1 itemset make ###
    ##########################
    freq1_dic = {}
    msc = int(col1.find().count() * 0.1)
    for doc in col1.find():
        #dic['morph'] = ["전주", "문요한", ... ]
        for w in doc['word_set']: 
            #case1 : first insert
            if w not in freq1_dic:
                freq1_dic[w] = 1;
            #case2 : second or more insert
            else:
                freq1_dic[w] += 1;
    for key in freq1_dic.keys():
        if freq1_dic[key] < msc:
            del freq1_dic[key]
    
    for key in freq1_dic.keys():
        contentDic = {}
        contentDic['item_set'] = key
        contentDic['support'] = freq1_dic[key]
        col2.insert(contentDic)

    ##########################
    ### freq2 itemset make ###
    ##########################
    if(length >= 2):       
        col2 = db['candidate_L2']
        col2.drop()
        # 1. dictionary key를 list로 바꾼다.
        freq1_list = []
        for key in freq1_dic.keys():
            freq1_list.insert(0,key)

        # 2. list indexing을 하고 w1, w2 를 정한다.
        freq2_list = []
        freq2_dic = {}
        #print "len : " + str(len(freq1_list))
        for i in range(0, len(freq1_list)):
            for j in range(i+1, len(freq1_list)):
                w1 = freq1_list[i]
                w2 = freq1_list[j]
                freq2_list.insert(0, (w1,w2))

        # 3. db["news_wordset"]에 있는 데이터 doc의 "morph" 에서 w1, w2를 찾는다.
        listNum = len(freq2_list)
        for idx in range(0, listNum):
            w1, w2 = freq2_list[idx]
#            cur_per = float(idx)/float(listNum)*100
#            print "{0:.2f}".format(cur_per) + "% Done in freq2"
            for doc in col1.find() :
                # 3.1 이때 w1, w2가 있으면 (w1, w2)를 새로운 dict에 추가한다.
                if (w1 in doc['word_set']) and (w2 in doc['word_set']):
                    if (w1,w2) not in freq2_dic.keys():
                        freq2_dic[(w1,w2)] = 1
                    else :
                        freq2_dic[(w1,w2)] += 1

        for key in freq2_dic.keys():
            if freq2_dic[key] < msc:
                del freq2_dic[key]
        for key in freq2_dic.keys():
            contentDic = {}
            contentDic['item_set'] = list(key)
            contentDic['support'] = freq2_dic[key]
            col2.insert(contentDic)
    ##########################
    ### freq3 itemset make ###
    ##########################
    if length >=3 : 
        col2 = db['candidate_L3']
        col2.drop()
        key_list = freq2_dic.keys()
        freq3_list = []
        freq3_dic = {}
        for i in range(0, len(key_list)) :
            for j in range(i+1, len(key_list)):
                t1 = sorted(list(key_list[i]))
                t2 = sorted(list(key_list[j]))
                if t1[0] == t2[0] :
                    t3 = sorted([t1[1] , t2[1]])
                    for elem in key_list:
                        if t3 == sorted(list(elem)):
                            freq3_list.insert(0, (t1[0], t1[1], t2[1]))

        # 3. db["news_wordset"]에 있는 데이터 doc의 "morph" 에서 w1, w2를 찾는다.
        listNum = len(freq3_list)
        for idx in range(0, listNum):
            w1, w2, w3 = freq3_list[idx]
#            cur_per = float(idx)/float(listNum)*100
#            print "{0:.2f}".format(cur_per) + "% Done in freq3"
            for doc in col1.find() :
                # 3.1 이때 w1, w2, w3 가 있으면 (w1, w2, w3)를 새로운 dict에 추가한다.
                if (w1 in doc['word_set']) and (w2 in doc['word_set']) and (w3 in doc['word_set']):
                    if (w1, w2, w3) not in freq3_dic.keys():
                        freq3_dic[(w1,w2,w3)] = 1
                    else :
                        freq3_dic[(w1,w2,w3)] += 1
    
        # freq3_dic 에 freq값을 만족하지 못하는 것들 제거
        for key in freq3_dic.keys():
            if freq3_dic[key] < msc:
                del freq3_dic[key]
        for key in freq3_dic.keys():
            contentDic = {}
            contentDic['item_set'] = list(key)
            contentDic['support'] = freq3_dic[key]
            col2.insert(contentDic)
"""        
    #데이터 불러오기
    col3 = db['candidate_L3']
    #change freq3_list to dic type
    freq3_dic = {}
    key_tup = ()
    for doc in col3.find():
        item_set = doc['item_set']
        support = doc['support']
        for elem in temp_list:
            key_tup = elem[0][0], elem[0][1], elem[0][2]
            freq3_dic[key_tup] = elem[1]
    for i in range(0, 10):
        key_max = max(freq3_dic.keys(), key=(lambda k: freq3_dic[k]))
        print str(i+1) , ' : ', str(key_max[0]),str(key_max[1]), str(key_max[2]), str(freq3_dic[key_max])
        del freq3_dic[key_max]
"""
""" 
# In mongoDB, python dictionary key is not supported for tuple type.
# So, change the dictionary type to list type
    freq3_list = []
    for key in freq3_dic.keys():
        freq3_list.insert(0, [key, freq3_dic[key]])
# ex) freq3_list = [ [key1, freq_val1 ], [key2, freq_val2 ], ... ]
    new_doc = {}
    new_doc['freq_set'] = freq3_list
    col2.insert(new_doc)
"""
def p6(length):
#make strong association rule
#and print all of strong rules
#by length-th frequent item set
    #데이터 불러오기
    col1 = db['candidate_L1']
    col2 = db['candidate_L2']
    col3 = db['candidate_L3']
    min_conf = 0.5
    #change freq3_list to dic type
    freq1_dic = {}
    freq2_dic = {}
    freq3_dic = {}
    key_tup = ()
    for elem in col1.find():
        freq1_dic[elem['item_set']] = elem['support']
    for elem in col2.find():
        freq2_dic[ tuple( sorted( [elem['item_set'][0], elem['item_set'][1]] ) ) ] = elem['support']
    for elem in col3.find():
        freq3_dic[ tuple( sorted( [elem['item_set'][0], elem['item_set'][1], elem['item_set'][2] ] ) ) ] = elem['support']
    if length == 2:
        for key in freq2_dic.keys():
            AB = float(freq2_dic[key])
            A = float(freq1_dic[key[0]])
            B = float(freq1_dic[key[1]])
            A_B = AB/A
            B_A = AB/B
            if A_B >= min_conf :
                print key[0], "=>" , key[1], A_B
            if B_A >= min_conf :
                print key[1], "=>", key[0], B_A

    if length == 3:
        for key in freq3_dic.keys():
            ABC = float(freq3_dic[key])
            A = float(freq1_dic[key[0]])
            B = float(freq1_dic[key[1]])
            C = float(freq1_dic[key[2]])
            AB = float(freq2_dic[ (key[0], key[1]) ])
            AC = float(freq2_dic[ (key[0], key[2]) ])
            BC = float(freq2_dic[ (key[1], key[2]) ])
            AB_C = ABC/AB
            AC_B = ABC/AC
            BC_A = ABC/BC
            A_BC = ABC/A
            B_AC = ABC/B
            C_AB = ABC/C
            if AB_C >= min_conf:
                print key[0],",",key[1],"=>",key[2],AB_C
            if AC_B >= min_conf:
                print key[0],",",key[2],"=>",key[1],AC_B
            if BC_A >= min_conf:
                print key[1],",",key[2],"=>",key[0],BC_A
            if A_BC >= min_conf:
                print key[0],"=>",key[1],",",key[2],A_BC
            if B_AC >= min_conf:
                print key[1],"=>",key[0],",",key[2],B_AC
            if C_AB >= min_conf:
                print key[2],"=>",key[0],",",key[1],C_AB

if __name__ == "__main__" :
    make_stop_word()
    printMenu()
    selector = input()
    if selector == 0:
        p0()
    elif selector == 1:
        p1()
        p3()
    elif selector == 2:
        url = str(raw_input("input news url:"))
        p2(url)
    elif selector == 3:
        url = str(raw_input("input news url:"))
        p4(url)
    elif selector == 4:
        length = int(raw_input("input length of the frequent item:"))
        p5(length)
    elif selector == 5:
        length = int(raw_input("input length of the frequnet item:"))
        p6(length)

