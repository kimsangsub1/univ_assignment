#include<iostream>

using namespace std;

typedef struct {
	int n1d;
	int n1m;
	int n3m;
}Pay;

Pay pay[12];
int p1d, p1m, p3m, p1y;
int plan[12];
int sum = 0;
int min_sum = 999999;

int test[12];
void debug() {
	cout << "chosen idx" << endl;
	for (int i = 0; i < 12; i++) {
		if (test[i] != -1) {
			cout << "(" << i << "," << test[i] << ")";
		}
	}
	cout << endl;
}

void init() {
	for (int i = 0; i < 12; i++) {
		pay[i].n1d = 0;
		pay[i].n1m = 0;
		pay[i].n3m = 0;
	}
	sum = 0;
	min_sum = 999999;
}

void receive() {
	cin >> p1d >> p1m >> p3m >> p1y;
	for (int i = 0; i < 12; i++)
		cin >> plan[i];
}

void writePay() {
	for (int i = 0; i < 12; i++) {
		if (plan[i] > 0) {
			pay[i].n1d = plan[i];
			pay[i].n1m = 1;
			bool is_day = false;
			for (int j = i + 1; j < i + 3; j++)
				if (plan[i] > 0)
					is_day = true;

			if (is_day == true)
				pay[i].n3m = 1;
		}
	}
}

void dfs(int idx, int flag) {
	if (idx >= 12) {
//		debug();
		if (min_sum > sum)
			min_sum = sum;
		return;
	}

	if (idx < 12) {
		if (flag == 0 && pay[idx].n1d > 0) { //1d
			sum += plan[idx] * p1d;
			for (int i = 0; i < 3; i++)
				dfs(idx+1, i);
			sum -= plan[idx] * p1d;
		}
		else if (flag == 1 && pay[idx].n1m > 0) { //1m
			sum += p1m;
			for (int i = 0; i < 3; i++)
				dfs(idx+1, i);
			sum -= p1m;
		}
		else if (flag == 2 && pay[idx].n3m > 0) { //3m
			sum += p3m;
			for (int i = 0; i < 3; i++)
				dfs(idx+3, i);
			sum -= p3m;
		}
		else {
			if (pay[idx + 1].n1d != 0) {
				for (int i = 0; i < 3; i++)
					dfs(idx + 1, i);
			}
			else
				dfs(idx + 1, 0);
		}
	}
}

void solve() {
	for (int i = 0; i < 12; i++)
		test[i] = -1;
	writePay();
	for (int i = 0; i < 3; i++)
		dfs(0, i);
	if (min_sum > p1y)
		min_sum = p1y;
}

void print(int n) {
	cout << "#" << n + 1 << " " << min_sum << endl;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		receive();
		solve();
		print(i);
		init();
	}
	return 0;
}