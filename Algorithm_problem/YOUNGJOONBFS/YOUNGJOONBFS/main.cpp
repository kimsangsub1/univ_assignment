#include<iostream>
#include<queue>
#include<vector>
#include<cstring>

#define MAX_SIZE 100001

using namespace std;

typedef struct {
	int level; // depth
	int parent; // parent of node

}Node;
Node a[MAX_SIZE];

typedef struct {
	int prev;
	int cur;
	int val;
}Dp;

Dp dp[MAX_SIZE];
int size_dp = 0;

queue<int> q;
vector<int> v[MAX_SIZE];

/*
	prev�� cur�� �ε����� ������
	DP struct array�� ���� ��, �� ���� ��ȯ�Ѵ�.
*/

int func(int prev, int cur) {
	if (prev == cur)
		return 0;

	if (prev == a[cur].parent)
		return 1;

	if (a[prev].parent == a[cur].parent)
		return 2;

	else
		return func(a[prev].parent, a[cur].parent) + 2;
}

//int func(int prev, int cur) {
//	int p_t, c_t; // prev temp , current temp
//	int cnt = 0;
//	int ret_val;
//
//	//������ ���� ó��
//	if (prev == cur) {
//		//dp[size_dp].prev = prev;
//		//dp[size_dp].cur = cur;
//		dp[size_dp++].val = ret_val = 0;
//		return ret_val;
//	}
//
//	/*prev�� cur�� ������ ��*/
//	if (prev == a[cur].parent) {
//		//dp[size_dp].prev = prev;
//		//dp[size_dp].cur = cur;
//		dp[size_dp++].val = ret_val = 1;
//		return ret_val;
//	}
//
//	/*���� ������ ���ٸ�*/
//	if (a[prev].parent == a[cur].parent) {
//		//dp[size_dp].prev = prev;
//		//dp[size_dp].cur = cur;
//		dp[size_dp++].val = ret_val = 2;
//		return ret_val;
//	}
//
//	/*������ ���, dynamic programming�� �����Ѵ�. */
//	else {
//		//dp[size_dp].prev = prev;
//		//dp[size_dp].cur = cur;
//
//		//int parents_idx = -1;
//
//		//for (int i = 0; i < size_dp; i++)
//		//	if (a[prev].parent == dp[i].prev && a[cur].parent == dp[i].cur)
//		//		parents_idx = i;
//
//		//if (parents_idx == -1) {
//		//	cout << "something wrong when finding dp idx" << endl;
//		//	cout << "Information => ";
//		//	cout << "prev : " << prev << ", cur : " << cur << endl;
//		//	exit;
//		//}
//		dp[size_dp++].val = ret_val = func(a[prev].parent, a[cur].parent) + 2;
//		return ret_val;
//	}
//	return -1;
//
//}

int main() {

	int T;
	int N;
	int data;
	cin >> T;
	for (int idx = 0; idx < T; idx++) {
		cin >> N;

		for (int i = 0; i < N - 1; i++) { // N-1��
			cin >> data;
			//v[i + 2].push_back(data);
			v[data].push_back(i + 2);
			a[i + 2].parent = data;
		}
		a[1].parent = 1;

		q.push(1);
		a[1].level = 0;
		int sum = 0;
		int result;
		int prev, cur, tmp;
		tmp = 1;
		//bfs
		while (!q.empty()) {
			prev = tmp;
			tmp = q.front(); q.pop();
			cur = tmp;
			//cout << "prev : " << prev << ", cur : " << cur << endl;
			//cout << "prev parent : " << a[prev].parent << ", cur parent : " << a[cur].parent << endl << endl;
			sum += func(prev, cur);

			for (int i = 0; i < v[tmp].size(); i++) {
				q.push(v[tmp][i]);
				a[v[tmp][i]].level = a[tmp].level + 1;
			}
		}
		cout << "#" << idx + 1 << " " << sum << endl;
		memset(v, 0, sizeof(v));
	}


	return 0;
}


/*
if (a[prev].level == a[cur].level) {
p_t = prev; c_t = cur;

while (p_t != 1 && c_t != 1) {
cnt += 2;
p_t = a[p_t].parent;
c_t = a[c_t].parent;

if (p_t == c_t) break;
}
return cnt;
}

//cur�� ������ 1 �ٿ��ְ�, �� if���� ���� �۾��� �Ѵ�.
if (a[prev].level != a[cur].level) {
p_t = prev; c_t = a[cur].parent;
cnt++;

while (p_t != 1 && c_t != 1) {
cnt += 2;
p_t = a[p_t].parent;
c_t = a[c_t].parent;

if (p_t == c_t) break;
}
return cnt;
}
*/