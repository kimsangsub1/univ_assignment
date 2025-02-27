// ALLERGY.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"
#include <iostream>
#include <string>
#include <bitset>
#include <queue>
using namespace std;

typedef struct {
	long pos_food;	// bit_mask 형태이며, 현재 이 값은 해당 노드의 부모 노드들을 모두 고려하여 선택된 값이다. 
	short depth;		// bfs에서의 깊이를 나타내는 값
	short food_no;	// 몇 번째 푸드에서부터 시작하는지를 나타내는 인덱스
}node;

/*global variable*/
int min_comb = INT_MAX;
int n_food;
int n_people;
long *food;
bool find_result;

queue<node> data_queue;

void solvefunc(node cur_node) {
	if (find_result == true)
		return;
	if (cur_node.depth == 0) {// 시작점
		for (int i = 0; i < n_food; i++) {
			node new_node;
			new_node.depth = 1;
			new_node.food_no = i;
			new_node.pos_food = food[i];
			data_queue.push(new_node);
		}
		node next_node = data_queue.front(); data_queue.pop();
		solvefunc(next_node);
	}
	else {
		if (data_queue.empty())
			return;
		for (int i = cur_node.food_no + 1; i < n_food; i++) {
			node new_node;
			new_node.depth = cur_node.depth + 1;
			new_node.food_no = i;
			new_node.pos_food = cur_node.pos_food | food[i];
			data_queue.push(new_node);
		}

		if (cur_node.pos_food == (1 << n_people) - 1) {
			find_result = true;
			min_comb = cur_node.depth;
			return;
		}
		else {
			node next_node = data_queue.front(); data_queue.pop();
			solvefunc(next_node);
		}
	}
}

int main()
{
	int num_p; // number of problem.
	cin >> num_p;
	//문제 수에 대한 iteration.
	for (int num_p_idx = 0; num_p_idx < num_p; num_p_idx++) {
		cin >> n_people >> n_food;
		food = new long[n_food];
		memset(food, 0, n_food * sizeof(long)); // food 값을 0으로 초기화
		string can_eat_name[50]; //해당 음식에 대해 알러지가 있는 사람들의 이름을 저장한다. 10개의 푸드라면 각각에 대해서 알러지가 있는 사람들의 이름을 저장. 각 푸드마다 초기화를 시켜준다.
		string people_name[50]; //해당 문제에 대해 나열된 모든 사람들의 이름을 저장한다.

		//사람 이름을 받아서 저장한다.
		for (int i = 0; i < n_people; i++)
			cin >> people_name[i];

		//음식의 수 만큼 해당 음식에 대해 정보를 주기 때문에 그에 대한 iteration 반복
		for (int i = 0; i < n_food; i++) {
			int can_eat_people_n; // 그 음식을 먹을 수 있는 사람의 수를 저장하는 변수
			cin >> can_eat_people_n;

			//해당 음식을 먹을 수 있는 사람들의 이름이 위에서 받은 can_eat_people_n 변수에 들어있는 만큼 나열된다.
			//따라서 그에 대한 배열을 받아서 저장한다.
			for (int j = 0; j < can_eat_people_n; j++)
				cin >> can_eat_name[j];

			//해당 음식을 먹을 수 있는 사람들을 food[n_food] 배열에 bit mask 형식으로 저장한다.
			for (int j = 0; j < can_eat_people_n; j++)
				for (int k = 0; k < n_people; k++)
					if (can_eat_name[j].compare(people_name[k]) == 0) food[i] += 1 << k;
		}

		//solve 영역
		find_result = false;
		node start_node;
		start_node.depth = 0; start_node.food_no = 0; start_node.pos_food = 0;
		
		solvefunc(start_node);

		cout << min_comb << endl;
		n_food = 0; n_people = 0; min_comb = INT_MAX;
		delete food;
		queue<node> data_queue_new;
		data_queue = data_queue_new;
	}
	return 0;
}