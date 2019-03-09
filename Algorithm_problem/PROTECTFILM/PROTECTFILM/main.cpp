#include<iostream>

using namespace std;

int D, W, K;
int **film;
int **origin_film;
int *chosen;
int min;

void init() {
	min = 9999;
	delete film;
}

void receive() {
	cin >> D >> W >> K;

	film = new int*[D];
	origin_film = new int*[D];
	for (int i = 0; i < D; i++){
		film[i] = new int[W];
		origin_film[i] = new int[W];
	}

	chosen = new int[D];
	for (int i = 0; i < D; i++)
		for (int j = 0; j < W; j++)
			cin >> film[i][j];
		
	for (int i = 0; i < D; i++)
		for (int j = 0; j < W; j++)
			origin_film[i][j] = film[i][j];

}

bool seeNext(int depth , int width, int type){
	bool ret = true;
	if (depth <= D - K) 
		for(int i = 0 ; i < K - 1; i++)
			if (film[depth][width] != film[depth + i + 1][width])
				ret = false;

	return ret;
}

bool check() {
	bool ret = true;
	for (int i = 0; i < W; i++) {
		bool colchk = false;
		for (int j = 0; j < D; j++) 
			if (seeNext(j, i, film[j][i])) 
				colchk = true;
		if (colchk == false)
			ret = false;
	}
	return ret;
}

int numOfMedicine() {
	int cnt = 0;
	for (int i = 0; i < D; i++)
		if (chosen[i] != 0)
			cnt++;
	return cnt;
}

void changeMap() {
	for (int i = 0; i < D; i++) {
		if (chosen[i] == 1)
			for (int j = 0; j < W; j++)
				film[i][j] = 0;

		if (chosen[i] == 2)
			for (int j = 0; j < W; j++)
				film[i][j] = 1;
	}
}

void restoreMap() {
	for (int i = 0; i < D; i++)
		for (int j = 0; j < W; j++)
			film[i][j] = origin_film[i][j];
}

void dfs(int idx, int flag) {
	if (idx >= D){
		changeMap();
		if (check()) 
			if (min > numOfMedicine()) 
				min = numOfMedicine();
		restoreMap();
		return;
	}
	
	chosen[idx] = flag;
	for (int i = 0; i < 3; i++)
		dfs(idx + 1, i);
}

void solve() {
	for (int i = 0; i < 3; i++)
		dfs(0, i);
}

void print(int tc) {
	cout << "#" << tc + 1 << " " << min << endl;
}

int main() {
	int T;
	cin >> T;
	for (int tc = 0; tc < T; tc++) {
		init();
		receive();
		solve();
		print(tc);
	}
	return 0;
}