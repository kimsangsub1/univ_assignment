// MILLIONAIRE PLAN.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;

typedef struct {
	int a;			// 주식 값
	int d;			// 피크점과의 주식 값 차이
	bool flag_pick; //피크점인지 아닌지를 나타내는 플래그
}Data;
int n; // size of problem

void WritePick(Data* data) {
	// 해당 데이터에 대해서 pick 점인지 아닌지를 판단해서
	// bool값으로 true false를 새겨준다.

	int bef_idx = 0; // 

	/*첫 번째 피크점 찾기*/
	for (int i = 0; i < n; i++)
		if (data[bef_idx].a <= data[i].a)
			bef_idx = i;
	data[bef_idx].flag_pick = true;
	cout << "pick idx : " << bef_idx << ", value : " << data[bef_idx].a << endl;

	/*첫 번째 피크점이 가장 마지막 값이라면 작업을 끝낸다.*/
	if (bef_idx == n - 1)
		return;

	/*다음에 나오는 피크점들을 모두 찾는다.*/
	while (bef_idx < n) {
		int cur_idx = bef_idx + 1;
		int t_max_idx = -1;
		int t_max = -1;
		for (; cur_idx < n; cur_idx++) {
			if (cur_idx < n - 1) { 
				if (data[bef_idx].a > data[cur_idx].a		&&
					data[cur_idx - 1].a < data[cur_idx].a	&&
					data[cur_idx + 1].a < data[cur_idx].a) {
					if (t_max <= data[cur_idx].a){
						t_max_idx = cur_idx;
						t_max = data[cur_idx].a;
					}
				}
			}
			else { // cur_idx = n-1일때는 예외처리
				if (data[bef_idx].a > data[cur_idx].a	&&
					data[cur_idx - 1].a < data[cur_idx].a) {
					if (t_max <= data[cur_idx].a) {
						t_max_idx = cur_idx;
						t_max = data[cur_idx].a;
					}
				}
			}
		}

		/* 피크점이 오직 하나일 때, 이 점 이후로 내림차순으로 간다면 더 이상 피크점이 없으므로 함수 종료 */
		if (t_max_idx == -1) return; 
		
		/*pick point 설정 */
		bef_idx = t_max_idx;
		data[bef_idx].flag_pick = true;
		cout << "pick idx : " << bef_idx << ", value : " << data[bef_idx].a << endl;
		//if (cur_idx >= n) break;
	}
}

void WriteDifference(Data *data, int start_idx) {
	if (start_idx >= n)
		return;
	int p_idx = -1;
	for (int i = start_idx; i < n; i++) {
		if (data[i].flag_pick == true) {
			p_idx = i;
			break;
		}
	}
	if (p_idx == -1) {
		for (int i = start_idx; i < n; i++)
			data[i].d = 0;
		return;
	}

	for (int i = start_idx; i <= p_idx; i++)
		data[i].d = data[p_idx].a - data[i].a;

	WriteDifference(data, p_idx + 1);
}

int main()
{
	ifstream fin;
	fin.open("input.txt");
	int n_pro;
	fin >> n_pro;
	for (int n_pro_idx = 0; n_pro_idx < n_pro; n_pro_idx++) {
		fin >> n;
		Data *data = new Data[n];
		for (int i = 0; i < n; i++) {
			data[i].d = 0; data[i].flag_pick = false;
		}
		for (int i = 0; i < n; i++){
			fin >> data[i].a;
		}

		WritePick(data);

		WriteDifference(data, 0);

		long long sum = 0;
		for (int i = 0; i < n; i++)
			if (data[i].d > 0)
				sum += data[i].d;

		cout << "#" << n_pro_idx + 1<< " " << sum << endl;
	}
	return 0;
}


