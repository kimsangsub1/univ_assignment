#include<iostream>
#include<iomanip>
#include<queue>

using namespace std;

//(상, 하, 좌, 우) 로 길이 있는지 확인한다.
int direct[8][4] = {
	{0, 0, 0, 0}, //0
	{-1, 1, -1, 1}, //1
	{-1, 1, 0, 0}, //2
	{0, 0, -1, 1}, //3
	{-1, 0, 0, 1}, //4
	{0, 1, 0, 1}, //5
	{0, 1, -1, 0}, //6
	{-1, 0, -1, 0}  //7
}; // direct[0]은 안쓸꺼다. (상,하,좌,우)

int N, M, R, C, L; //N,M : 맵의 세로, 가로 크기, R,C : 맨홀의 세로, 가로 위치, L : 탈주 후 경과시간
int result;
typedef struct {
	int info;
	bool visit;
	int depth;
	int c, r;
}Map;

Map **map;

void debug() {
	/*
	cout << endl << "map info" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j].info << " ";
		}
		cout << endl;
	}
	*/

	cout << "depth map" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << setw(3) << map[i][j].depth;
		}
		cout << endl;
	}
}

void receive() {
	cin >> N >> M >> R >> C >> L;
	map = new Map*[N];
	for (int i = 0; i < N; i++)
		map[i] = new Map[M];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j].info;
}

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			map[i][j].visit = false;
			map[i][j].depth = 0;
			map[i][j].r = i;
			map[i][j].c = j;
		}
}

queue<Map> q;

bool checkNext(int R, int C, int next_R, int next_C) {
	bool ret = false;
	if ( (next_R != R || next_C != C) &&
		map[next_R][next_C].visit == false &&
		map[next_R][next_C].info != 0){
		if (next_R < R)
			if(direct[map[next_R][next_C].info][1] == 1 && direct[map[R][C].info][0] == -1)
				ret = true;
		
		if (next_R > R)
			if (direct[map[next_R][next_C].info][0] == -1 && direct[map[R][C].info][1] == 1) 
				ret = true;

		if(next_C < C)
			if (direct[map[next_R][next_C].info][3] == 1 && direct[map[R][C].info][2] == -1)
				ret = true;

		if (next_C > C)
			if (direct[map[next_R][next_C].info][2] == -1 && direct[map[R][C].info][3] == 1)
				ret = true;
	}
	return ret;
}

void bfs(int R, int C) {
	int next_C, next_R;

	map[R][C].visit = true;
	map[R][C].depth = 1;
	q.push(map[R][C]);

	while (!q.empty()) {
		Map tmp = q.front(); q.pop();
		R = tmp.r; C = tmp.c;
		
		for (int i = 0; i < 4; i++) {
			next_R = R; next_C = C;
			if (i < 2) next_R = R + direct[map[R][C].info][i];
			if (i >= 2) next_C = C + direct[map[R][C].info][i];

			if (0<= next_R && next_R < N && 0<= next_C && next_C < M && checkNext(R, C, next_R, next_C)) { // 변화가 생기고, 해당 지역에 파이프가 있으며, 현재 파이프와 다음 파이프가 이어져있다면
				map[next_R][next_C].depth = map[R][C].depth + 1;
				map[next_R][next_C].visit = true;
				q.push(map[next_R][next_C]);
				//debug();
			}
		}
	}
}

int count() {
	int ret_val = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (1 <= map[i][j].depth && map[i][j].depth <= L)
				ret_val++;
	return ret_val;
}

void solve() {
	bfs(R, C);
	result = count();
}
void print(int n) {
	cout << "#" << n + 1 << " " << result << endl;
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		receive();
		init();
		solve();
		print(i);
		delete map;
	}
	return 0;
}