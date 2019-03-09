#include<iostream>

using namespace std;

int T;
int N, W, H;

int **map;
int **s_map;
int pos[4];
int min_block_n; //�ּ� ��� ��

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

//���� �������� ��´�.
void setPosition() {
	pos[0]++;
	for (int i = 0; i < N - 1; i++) {
		if (pos[i] >= W) {
			pos[i + 1]++;
			pos[i] = 0;
		}
	}
}

//�ش� �ε����� ���� �ٿ��Ų ��
//���� ���� �ִ� ����� ���̸� ��ȯ�Ѵ�.
//���� �߻��� -1
//param : width position.
int ballDown(int wp) {
	for (int i = 0; i < H; i++)
		if (map[i][wp] != 0)
			return i;
	return -1;
}

//�ش� w,h�� �ִ� ���� �ı���Ų��.
void breakBall(int height, int width) {
	int value = map[height][width];
	map[height][width] = 0;

	//����
	for (int i = 1; i < value; i++)
		if (width + i < W)
			breakBall(height, width + i);

	for (int i = 1; i < value; i++)
		if (width - i >= 0)
			breakBall(height, width - i);

	//����
	for (int i = 1; i < value; i++)
		if (height + i < H)
			breakBall(height + i, width);

	for (int i = 1; i < value; i++)
		if (height - i >= 0)
			breakBall(height - i, width);
}

void downBlock() {
	for (int i = 0; i < W; i++) {
		int j = H - 2; // �� ������ ��� ���Ѵ�.
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

//���� ����� �ּڰ��� ã�´�.
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


1. �Է� ���� ��ü�� ����Ѵ�. ������ �ִ� 4���� �������µ�, width�� �ִ� 12�̹Ƿ�, ��� ��츦 ����ص� ��� ����
2. ���õ� �������� �������� ���� a,b,c,d�� ����. �ش�Ǵ� �����ǿ��� ������ ������ �۾��� �Ѵ�.
3. ������ ��Ͽ� �¾��� ��, ����� ��Ʈ���� �Լ��� �ۼ��Ѵ�.
	- ���� ����� ����ŭ ���� ���η� ����� ��Ʈ����.
	- ��Ʈ���� ���ִ� ����� �Ʒ��� ������.
	- ��Ʈ���� ��Ͽ� ���ִ� ���ڸ�ŭ �ٽ� ���� �Լ��� �ݺ��Ѵ�.
4. ��� ������ ����Ʈ���� ��, ���� ����� ���� ���Ѵ�.

5. ���� ������ ��� ������ ���ؼ� ������ ��, �ּҷ� ���� ����� ���� ����Ѵ�.
*/