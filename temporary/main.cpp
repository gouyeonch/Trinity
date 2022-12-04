#include "header/makeSubway.h"
#include "header/Dijkstra.h"
#include "header/Astar.h"
#include "header/SPFA.h"

using namespace std;
extern Station* stations[MAX];
extern int stationNum[MAX];

int main()
{
	makeAllLine();

	vector<string>name;
	vector<int> line, num;
	int i;
	cout << "input :";
	cin >> i;

	for (int k = 0; k < i; k++)
	{
		int _num, _line; string _name;
		cout << "사람수 호선 역이름 : ";
		cin >> _num >> _line >> _name;
		name.push_back(_name);
		line.push_back(_line);
		num.push_back(_num);
	}

	MiddleSPFA(name, num, line);
	MiddleDijkstra(name, num, line);
	MiddleAstar(name, num, line);
}