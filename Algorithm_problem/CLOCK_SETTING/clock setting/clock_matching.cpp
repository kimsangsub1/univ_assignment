#include<stdio.h>
#include<iostream>
#include<vector>
#include<math.h>

#define ADDER 1
#define CLOCK_NUMBER 16
#define BUTTON_NUMBER 10

using namespace std;

vector< vector<int> > button({
	vector<int>({0,1,2}),
	vector<int>({ 3,7,9,11 }),
	vector<int>({ 4,10,14,15 }),
	vector<int>({ 0, 4, 5, 6, 7 }),
	vector<int>({ 6, 7, 8, 10, 12 }),
	vector<int>({ 0, 2, 14, 15 }),
	vector<int>({ 3, 14, 15 }),
	vector<int>({ 4, 5, 7, 14, 15 }),
	vector<int>({ 1, 2, 3, 4, 5 }),
	vector<int>({ 3, 4, 5, 9, 13 })
	});

vector<int> cuttingFunction(vector<int> clock_input) {
	vector<int> clock_out(16);
	for (vector<int>::size_type i = 0; i < clock_input.size(); i++)
		clock_out[i] = clock_input[i] % 12;
	return clock_out;
}

bool IsAllZero(vector<int> clock_input) {
	bool flag = true;
	for (vector<int>::size_type i = 0; i < clock_input.size(); i++)
		if (clock_input[i] != 0)
			flag = false;
	return flag;
}

int main() {
	int N;
	cin >> N;
	for (int N_idx = 0; N_idx < N; N_idx++) {
		vector<int> clock_input(16);
		vector<int> clock_output(16);
		vector<int> push_num(10);

		int tmp_input;
		for (vector<int>::size_type i = 0; i < 16; i++) {
			cin >> tmp_input;
			clock_input[i] = tmp_input;
		}

		int min_push_N = RAND_MAX;
		for (int iter = 0; iter < pow(4, 10); iter++) {
			clock_output = clock_input;
			for (vector<int>::size_type i = 0; i < button.size(); i++)
				for (vector<int>::size_type j = 0; j < button[i].size(); j++)
					clock_output[button[i][j]] += 3 * push_num[i];
			clock_output = cuttingFunction(clock_output);
			if (IsAllZero(clock_output)) {
				int temp_sum = 0;
				for (vector<int>::size_type i = 0; i < push_num.size(); i++)
					temp_sum += push_num[i];
				if (min_push_N > temp_sum) min_push_N = temp_sum;
			}

			push_num[0] += ADDER;
			for (vector<int>::size_type i = 0; i < BUTTON_NUMBER - 1; i++) {
				if (push_num[i] == 4){
					push_num[i + ADDER] += ADDER;
					push_num[i] = 0;
				}
			}
		}
		
		if (min_push_N == RAND_MAX)
			cout << -1 << endl;
		else
			cout << min_push_N << endl;
	}	
	return 0;
}