// QUADTREE.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<stdio.h>
#include <iostream>
#include<string.h>

using namespace std;

char * DivConq(char * QuardTree, int s_idx) {
	if (QuardTree[s_idx] == 'w' || QuardTree[s_idx] == 'b') {
		char * ret_val = new char[2];
		ret_val[0] = QuardTree[s_idx];
		ret_val[1] = '\0';
		return ret_val;
	}
	char *K1, *K2, *K3, *K4;

	K1 = DivConq(QuardTree, s_idx + 1);
	K2 = DivConq(QuardTree, s_idx + strlen(K1) + 1);
	K3 = DivConq(QuardTree, s_idx + strlen(K1) + strlen(K2) + 1);
	K4 = DivConq(QuardTree, s_idx + strlen(K1) + strlen(K2) + strlen(K3) + 1);

	char * ret_val = new char[strlen(K1) + strlen(K2) + strlen(K3) + strlen(K4) + 1];
	strcpy(ret_val, "x");
	strcat(ret_val, K3);
	strcat(ret_val, K4);
	strcat(ret_val, K1);
	strcat(ret_val, K2);
	return ret_val;
}

int main()
{
	int N_iter;
	cin >> N_iter;
	
	for (int i = 0; i < N_iter; i++) {
		char QuardTree[1000];
		cin >> QuardTree;
		cout << DivConq(QuardTree, 0) << endl;

	}

    return 0;
}

