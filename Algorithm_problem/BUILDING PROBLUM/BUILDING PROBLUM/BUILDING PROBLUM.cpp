// BUILDING PROBLUM.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>

using namespace std;
int main()
{
	for (int n_pro = 0; n_pro < 10; n_pro++) {
		int n_building;
		cin >> n_building;
		int *b = new int[n_building];
		for (int i = 0; i < n_building; i++)
			cin >> b[i];
		int sum = 0;
		for (int i = 0; i < n_building; i++) {
			int t_max = max(b[i - 2], max(b[i - 1], max(b[i + 1], b[i + 2])));
			if (t_max < b[i]) sum += b[i] - t_max;
		}
		cout << sum << endl;
	}
    return 0;
}

