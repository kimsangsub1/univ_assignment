// FENCE.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace std;

int MaxArea(int * fence, int left, int right) {
	if (left == right) return fence[left];
	if (abs(left - right) == 1) return max(min(fence[left], fence[right]) * 2, max(fence[left], fence[right]));
	int m = (right + left) / 2;//middle index.
	int area_left = MaxArea(fence, left, m);
	int area_right = MaxArea(fence, m + 1, right);
	int height; int area; int max_area_mid; int width;
	area = max_area_mid = height = fence[m];
	int l, r; // left, right index.
	l = m - 1; r = m + 1;
	while (left <= l && r <= right) {
		if (fence[l] < fence[r]) {
			width = (r - l);
			height = min(height, fence[r]);
			area = width * height; r++;
		}
		else{ //fence[l] >= fence[r]
			width = (r - l);
			height = min(height, fence[l]);
			area = width * height; l--;
		}
		max_area_mid = max(max_area_mid, area);
	}
	while (r <= right) {
		width = r - l;
		height = min(height, fence[r]);
		area = width * height; r++;
		max_area_mid = max(max_area_mid, area);
	}
	while (left <= l) {
		width = r - l;
		height = min(height, fence[l]);
		area = width * height; l--;
		max_area_mid = max(max_area_mid, area);
	}

	return max(area_left, max(max_area_mid, area_right));
}

int main()
{
	int NumOfPro;
	cin >> NumOfPro;
	for (int big_iter = 0; big_iter < NumOfPro; big_iter++) {
		int NumOfCol;
		cin >> NumOfCol;
		int *fence = new int[NumOfCol];
		for (int i = 0; i < NumOfCol; i++)
			cin >> fence[i];
		cout << MaxArea(fence, 0, NumOfCol - 1) << endl;
	}
	return 0;
}

