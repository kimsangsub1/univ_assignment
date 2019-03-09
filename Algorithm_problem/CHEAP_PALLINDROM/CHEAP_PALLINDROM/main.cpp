#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long

const int MAX = 2009;
const int MDD = 998244353;
const int INF = 1000000001;

int L, K;
string str;
int cost[26];
int dp[MAX][MAX];

void init() {
	cin >> L >> K >> str;
	for (int i = 0; i < K; ++i) {
		int a, b;
		cin >> a >> b;
		cost[i] = min(a, b);
	}
}

void solve() {
	/*
		dp[i][j]�� ���� i���� j���� �Ӹ������ �����ϴµ� ��� �ּ� ����� ����� ���̴�. 
		���� dp[i][j]���� ���� a(j+1)�� �߰��Ѵٸ�, a(j+1)�� ������ ���� �߰��� ��, �ƴϸ� ���������� ����ϸ� �ȴ�.
		�� �� ����� ���� ���� �߰� ��� �� �� �� ������ ����ϸ� �ȴ�.
		�ֳ��ϸ� dp[i][j]�� �̹� �Ӹ������ ����� ����, �̸� ����ϴ� �ּ� ����� ����ֱ� �����̴�.
	*/
	for (int i = 0; i < L; ++i) {
		for (int a = 0; a + i < L; ++a) {
			int b = a + i;
			if (a == b){
				dp[a][b] = 0;
			}
			else {
				dp[a][b] = min(cost[str[a] - 'a'] + dp[a + 1][b], dp[a][b - 1] + cost[str[b] - 'a']);
				/*
					���� ���� ������ ���� ���� ���ڸ� �Ӹ������ �����ϴµ� ����� ���� �ʿ� ���� ������ 
					������ �ִ� ����� �״�� �����Ѵ�.
				*/
				if (str[a] == str[b])
					dp[a][b] = dp[a + 1][b - 1];
					
			}
		}
	}
	printf("%d\n", dp[0][L - 1]);
}

int main() {
	int t = 1;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		init();
		printf("#%d ", i + 1);
		solve();
	}
	return 0;
}