#include<iostream>

using namespace std;

int T;
int N, W, H;

int **map;
int **s_map;
int pos[4];
int min_block_n; //최소 블록 수

void resetMap() {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			map[i][j] = s_map[i][j];
}

void init() {
	for (int i = 0; i < N; i++)
		pos[i] = 0;
	resetMap();
	min_block_n = 99999;
}

//공의 포지션을 잡는다.
void setPosition() {
	pos[0]++;
	for (int i = 0; i < N - 1; i++) {
		if (pos[i] >= W) {
			pos[i + 1]++;
			pos[i] = 0;
		}
	}
}

//해당 인덱스의 공을 다운시킨 후
//가장 위에 있는 블록의 높이를 반환한다.
//오류 발생시 -1
//param : width position.
int ballDown(int wp) {
	for (int i = 0; i < H; i++)
		if (map[i][wp] != 0)
			return i;
	return -1;
}

//해당 w,h에 있는 볼을 파괴시킨다.
void breakBall(int height, int width) {
	int value = map[height][width];
	map[height][width] = 0;

	//가로
	for (int i = 1; i < value; i++)
		if (width + i < W)
			breakBall(height, width + i);

	for (int i = 1; i < value; i++)
		if (width - i >= 0)
			breakBall(height, width - i);

	//세로
	for (int i = 1; i < value; i++)
		if (height + i < H)
			breakBall(height + i, width);

	for (int i = 1; i < value; i++)
		if (height - i >= 0)
			breakBall(height - i, width);
}

void downBlock() {
	for (int i = 0; i < W; i++) {
		int j = H - 2; // 맨 밑줄은 고려 안한다.
		while (j >= 0) {
			if (map[j][i] != 0) {
				while (true) {
					j++; if (j == H || map[j][i] != 0) break;
					map[j][i] = map[j-1][i]; map[j-1][i] = 0;
				}
				j--;
			}
			j--;
		}
	}
}

//남은 블록의 최솟값을 찾는다.
void FindMin() {
	int cnt = 0;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			if (map[i][j] != 0)
				cnt++;

	if (min_block_n > cnt)
		min_block_n = cnt;
}

void debug() {
	cout << endl << "current map " << endl;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

void solve() {
	for (int iter = 0; iter < pow(W, N) - 1; iter++) {
		for (int i = 0; i < N; i++) {
			if (pos[0] == 2 && pos[1] == 2)
				int dbg = 0;
			int dest = ballDown(pos[i]);
			if (dest != -1) {
				//cout << "dp(" << pos[i] << "," << dest << ")" << endl;
				breakBall(dest, pos[i]);
				downBlock();
				//debug();
			}
		}

		FindMin();
		resetMap();
		setPosition();
	}

}
int main() {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> N >> W >> H;
		map = new int*[H];
		s_map = new int*[H];
		for (int i = 0; i < H; i++) {
			map[i] = new int[W];
			s_map[i] = new int[W];
		}

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
				cin >> s_map[i][j];

		init();
		solve();
		cout << "#" << test + 1 << " " << min_block_n << endl;
	}
	return 0;
}

/*


1. 입력 값은 전체를 고려한다. 구슬이 최대 4개가 떨어지는데, width는 최대 12이므로, 모든 경우를 고려해도 상관 없음
2. 선택된 구슬들의 포지션을 각각 a,b,c,d라 하자. 해당되는 포지션에서 구슬을 떨구는 작업을 한다.
3. 구슬이 블록에 맞았을 때, 블록을 깨트리는 함수를 작성한다.
	- 맞은 블록의 값만큼 가로 세로로 블록을 깨트린다.
	- 깨트리고 떠있는 블록을 아래로 내린다.
	- 깨트리는 블록에 써있는 숫자만큼 다시 같은 함수를 반복한다.
4. 모든 구슬을 떨어트렸을 때, 남은 블록의 수를 구한다.

5. 위의 과정을 모든 구슬에 대해서 적용한 뒤, 최소로 남은 블록의 수를 출력한다.
*/