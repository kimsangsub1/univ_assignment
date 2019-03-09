// ODDPAIRPROBLEM.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
using namespace std;
long long int sum;
int data[1000001];
void func(int *data, int low, int high) {
	/*
	cout << "high : " << high << ", low : " << low << endl;
	for (int i = 1; i <= high ; i+=2){
		sum += i * (int(high / i) - (int((low - 1) / i) + 1) + 1);
		cout << "i : (" << i << ") , L idx : " << int((low - 1) / i) + 1 << ", R idx : " << int(high / i);
		cout << ", part sum : " << i * (int(high / i) - (int((low - 1) / i) + 1) + 1);
		cout << endl;
	}
	*/
	sum = data[high] - data[low];
}

int main()
{
	for (int i = 1; i < 1000001; i++)
		data[i] = 0;
	for (int i = 1; i <= 1000000; i++) {
		for (int j = 1; j <= 1000000 / i; j++) {
			data[i*j] += i;
		}
	}
	int n_pro;
	cin >> n_pro;
	for (int n_pro_idx = 0; n_pro_idx < n_pro; n_pro_idx++) {
		int s, f;
		sum = 0;
		cin >> s >> f;
		func(data,s, f);
		cout << "#" << n_pro_idx + 1 << " " << sum << endl;
	}
	return 0;
}

