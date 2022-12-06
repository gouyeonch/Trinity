#include "header/makeSubway.h"
#include "header/Dijkstra.h"
#include "header/Astar.h"
#include "header/SPFA.h"
#include <ctime>


using namespace std;
extern Station* stations[MAX];
extern int stationNum[MAX];
int minMem;

void input(vector<string>& name, vector<int>& num, vector<int>& line);

int main()
{
	vector<string>name;
	vector<int> line, num;
	clock_t start, finish;
	minMem = INT_MAX;

	makeAllLine();
	
	input(name, num, line);

	start = clock();
	MiddleSPFA(name, num, line);
	finish = clock();
	cout << "SPFA 알고리즘 실행 시간 : " << finish - start << "ms\n\n";

	start = clock();
	MiddleDijkstra(name, num, line);
	finish = clock();
	cout << "Dijkstra 알고리즘 실행 시간 : " << finish - start << "ms\n\n";

	start = clock();
	MiddleAstar(name, num, line);
	finish = clock();
	cout << "A* 알고리즘 실행 시간 : " << finish - start << "ms\n\n";

	return 0;
}

void input(vector<string>& name, vector<int>& num, vector<int>& line)
{
	int i;

	cout << "출발할 장소의 수를 입력하세요 :";
	cin >> i;
	cout << '\n';

	if (i < 2)
	{
		cout << "출발 장소는 2개 이상이여야 됩니다.\n";
		exit(1);
	}

	for (int k = 0; k < i; k++)
	{
		int _num, _line; string _name;
		cout << "해당역에서 탑승하는 인원과 역의 호선, 역이름을 입력하세요 : ";
		cin >> _num >> _line >> _name;
		if (minMem > _num)
			minMem = _num;
		name.push_back(_name);
		line.push_back(_line);
		num.push_back(_num);
	}

	cout << "\n\n";
}