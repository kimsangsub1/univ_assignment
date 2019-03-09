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
		dp[i][j]의 값은 i부터 j까지 팰린드롬을 제작하는데 드는 최소 비용을 고려한 것이다. 
		만약 dp[i][j]에서 문자 a(j+1)을 추가한다면, a(j+1)을 오른쪽 끝에 추가할 지, 아니면 제거할지를 고민하면 된다.
		이 때 비용은 제거 비용과 추가 비용 중 더 싼 값으로 고려하면 된다.
		왜냐하면 dp[i][j]는 이미 팰린드롬을 만들어 놨고, 이를 계산하는 최소 비용이 담겨있기 때문이다.
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
					왼쪽 끝과 오른쪽 끝이 같은 문자면 팰린드롬을 제작하는데 비용이 따로 필요 없기 때문에 
					기존에 있던 비용을 그대로 대입한다.
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