#include<iostream>

using namespace std;

typedef struct {
	int x, y;
	int num;
	int direct;
}Team;

Team *team;
int **map;

int **bac;
int N, M, K; // N : ���簢�� �� ���� ���� , M �ð��� ���� �� �̻����� �󸶳� ���Ҵ��� �����ؾ� �Ѵ�.
			 // K : �̻��� ������ ��
int result;

void checkBacteriaMap() {
	bac = new int*[N];
	for (int i = 0; i < N; i++)
		bac[i] = new int[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			bac[i][j] = 0;

	for (int i = 0; i < K; i++)
		if (team[i].direct != 0)
			bac[team[i].y][team[i].x] = team[i].num;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << bac[i][j] << "\t";
		}
		cout << endl;
	}
	delete bac;
}

void debug() {
	cout << endl << "debug" << endl;
	checkBacteriaMap();
	/*
	for (int i = 0; i < 10; i++) {
		cout << "(" << team[i].x << "," << team[i].y << ") = " << team[i].num << "," << team[i].direct << endl;
	}
	*/
	/*
	cout << "map infomation" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
	*/
}

void init() {
	if (team != NULL)
		delete team;
	team = new Team[K];
	map = new int*[N];
	for (int i = 0; i < N; i++)
		map[i] = new int[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = 0;
	result = 0;
}

//���׸��Ƹ� ���⿡ ���� �� ĭ�� �̵��Ѵ�.
void move() {
	for (int i = 0; i < K; i++) {
		if (team[i].direct != 0) {
			map[team[i].y][team[i].x]--;

			if (team[i].direct == 1) { // ��
				team[i].y--;
				map[team[i].y][team[i].x]++;
			}
			if (team[i].direct == 2) { // ��
				team[i].y++;
				map[team[i].y][team[i].x]++;
			}
			if (team[i].direct == 3) { // ��
				team[i].x--;
				map[team[i].y][team[i].x]++;
			}
			if (team[i].direct == 4) { // ��
				team[i].x++;
				map[team[i].y][team[i].x]++;
			}
		}
	}
}

void merge(int row, int col) {
	int idx[4]; int db_idx = 0;
	for (int i = 0; i < K; i++)
		if (team[i].y == row && team[i].x == col)
			idx[db_idx++] = i;

	//find max idx;
	int max_idx; int max_val = -1;
	for (int i = 0; i < db_idx; i++) {
		if (max_val < team[idx[i]].num){
			max_val = team[idx[i]].num; max_idx = idx[i];
		}
	}
	//�ְ� �ƴ϶�� �״´�.	
	for (int i = 0; i < db_idx; i++) {
		if (idx[i] != max_idx) {
			team[max_idx].num += team[idx[i]].num;
			team[idx[i]].num = 0;
			team[idx[i]].direct = 0;
		}
	}
	map[row][col] = 1;
}

//�ߺ��� ���� �ִ��� Ȯ���ϰ�, �ִٸ� �ߺ�ó���� �����Ѵ�.
void checkDubble() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] >= 2)  // �ߺ��Ǵ� ���� �ִٸ�
				merge(i, j);
}

//��輱�� ������ ���� �ִ��� Ȯ���ϰ�, �ִٸ� ���ó���� �����Ѵ�.
void checkBorder() {
	for (int i = 0; i < K; i++) {
		if (team[i].x == 0 || team[i].x == N - 1 || team[i].y == 0 || team[i].y == N - 1) {
			team[i].num /= 2;
			if (team[i].num == 0) {
				team[i].direct = 0;
				map[team[i].y][team[i].x] = 0;
			}
			if (team[i].direct == 1) team[i].direct = 2;
			else if (team[i].direct == 2) team[i].direct = 1;
			else if (team[i].direct == 3) team[i].direct = 4;
			else if (team[i].direct == 4) team[i].direct = 3;
			else team[i].direct = 0;
		}
	}
}

//���� ���׸����� ���� ���Ѵ�.
int countNum() {
	int ret_val = 0;
	for (int i = 0; i < K; i++)
		if (team[i].direct != 0)
			ret_val += team[i].num;
	return ret_val;
}

void solve() {
	for (int time = 0; time < M; time++) {
		//debug();
		move();
		checkDubble();
		checkBorder();
	}
	result = countNum();
}

int main() {

	int T;
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> N >> M >> K;
		init();
		for (int i = 0; i < K; i++) {
			cin >> team[i].y >> team[i].x >> team[i].num >> team[i].direct;
			map[team[i].y][team[i].x]++;
		}
		solve();
		cout << "#" << test + 1 << " " << result << endl;
	}

	return 0;
}