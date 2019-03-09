#include<iostream>
#include<algorithm>

using namespace std;

int T_n;
int N;
int N_p = 0;
int **map;
int man_n;
#define GOING 0
#define ARRIVE 1
#define READY 2
#define GOTODOWN 3
#define FINISH 4
typedef struct {
	int Path;
	int st_num;
	int state;
	int time;
	int x;
	int y;
}ManInfo;

typedef struct {
	int x;
	int y;
	int depth;
	int NumOfDownMan;
}Stair;

ManInfo mi[10];
Stair st[2];
int st_idx;
int min_result = 9999;

void calc() {
	ManInfo mi_tmp[10];

	for (int i = 0; i < man_n; i++) mi_tmp[i] = mi[i];

	bool finish_flag = false;
	int result = 0;

	while (finish_flag == false) {
		/*
		cout << "iteration : " << result << endl;
		for (int i = 0; i < man_n; i++) {
			cout << "man information(Path, st_num, state, time) : " << "(" <<
				mi_tmp[i].Path << "," <<
				mi_tmp[i].st_num << "," <<
				mi_tmp[i].state << "," <<
				mi_tmp[i].time << ")" << endl;
		}
		cout << "stair[0] ";
		cout << "num of people going to down : " << st[0].NumOfDownMan << endl;
		cout << "stair[1] ";
		cout << "num of people going to down : " << st[1].NumOfDownMan << endl << endl;
		*/
		finish_flag = true;

		for (int i = 0; i < man_n; i++) {
			//��ܿ� �������� �ʾҴٸ� ����� ���� �Ѱ����� ����.
			if (mi_tmp[i].Path > 0) mi_tmp[i].Path--;

		}for (int i = 0; i < man_n; i++) {
			//ARRIVE�� ������� READY ���·� ������ش�.
			if (mi_tmp[i].state == ARRIVE)
				mi_tmp[i].state = READY;

		}for (int i = 0; i < man_n; i++) {
			//�������� ���̶�� time�� �ϳ��� ���δ�.
			if (mi_tmp[i].state == GOTODOWN)
				mi_tmp[i].time--;

		}for (int i = 0; i < man_n; i++) {
			//�������� state�� FINISH�� �ٲٰ� ����� �������� ����� ���� �ϳ� ���δ�.
			if (mi_tmp[i].state == GOTODOWN && mi_tmp[i].time == 0) {
				mi_tmp[i].state = FINISH;
				st[mi_tmp[i].st_num].NumOfDownMan--;
			}

		}for (int i = 0; i < man_n; i++) {
			//����� �� �� �ִ� ����� �ִ��� Ȯ���Ѵ�.
			if ((mi_tmp[i].state == READY) && st[mi_tmp[i].st_num].NumOfDownMan < 3) {
				mi_tmp[i].state = GOTODOWN;
				mi_tmp[i].time = st[mi_tmp[i].st_num].depth;
				st[mi_tmp[i].st_num].NumOfDownMan++;
			}

		}for (int i = 0; i < man_n; i++) {
			//��ܿ� �������� �� ARRIVE�� ���¸� �ٲ۴�.
			if (mi_tmp[i].Path == 0 && mi_tmp[i].state == GOING) {
				mi_tmp[i].state = ARRIVE;
			}

		}for (int i = 0; i < man_n; i++) {
			//�ϳ��� FINISH���°� �ƴ϶�� �ݺ����� ��� �����Ѵ�.
			if (mi_tmp[i].state != FINISH)
				finish_flag = false;
		}
		result++;
	}
	min_result = min(min_result, result);
}

void dfs(int idx) {
	if (idx == man_n) {
		calc();
	}
	else {
		for (int i = 0; i < 2; i++) {
			mi[idx].st_num = i;
			if (i == 0) mi[idx].Path = abs(mi[idx].x - st[0].x) + abs(mi[idx].y - st[0].y);
			else mi[idx].Path = abs(mi[idx].x - st[1].x) + abs(mi[idx].y - st[1].y);
			dfs(idx + 1);
		}
	}
}

int main() {
	cin >> T_n;
	for (int T = 0; T < T_n; T++) {
		man_n = 0;
		st_idx = 0;

		cin >> N;
		map = new int*[N];
		for (int i = 0; i < N; i++)
			map[i] = new int[N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				if (map[i][j] == 1) {
					mi[man_n].x = i;
					mi[man_n].y = j;
					mi[man_n].state = GOING;
					mi[man_n].time = 0;
					man_n++;
				}
				if (map[i][j] >= 2) {
					st[st_idx].x = i;
					st[st_idx].y = j;
					st[st_idx].depth = map[i][j];
					st[st_idx].NumOfDownMan = 0;
					st_idx++;
				}
			}
		}

		dfs(0);

		cout << "#" << T + 1 << " " << min_result << endl;
		min_result = 9999;
		for (int i = 0; i < N; i++)
			delete map[i];
		delete map;
	}
	return 0;
}