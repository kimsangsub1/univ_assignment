// READ_VERTICAL.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;
int main()
{
	int n_pro;
	cin >> n_pro;
	for (int n_pro_idx = 0; n_pro_idx < n_pro; n_pro_idx++) {
		char data[5][15];
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 15; j++) 
				data[i][j] = '*';
			
		for (int i = 0; i < 5; i++) {
			string str;
			cin >> str;
			for (int j = 0; j < str.length(); j++)
				data[i][j] = str[j];
		}
		
		cout << "#" << n_pro_idx + 1 << " ";

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 5; j++) {
				if (data[j][i] != '*')
					cout << data[j][i];
			}
		}
	}
    return 0;
}

