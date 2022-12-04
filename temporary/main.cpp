#include "header/makeSubway.h"
#include "header/Dijkstra.h"
#include "header/Astar.h"
#include "header/SPFA.h"
#include <ctime>


using namespace std;
extern Station* stations[MAX];
extern int stationNum[MAX];

void input(vector<string>& name, vector<int>& num, vector<int>& line);

int main()
{
	vector<string>name;
	vector<int> line, num;
	clock_t start, finish;

	makeAllLine();
	
	input(name, num, line);

	map<int, int> b;
	start = clock();
	MiddleSPFA(name, num, line);
	finish = clock();
	cout << "SPFA �˰��� ���� �ð� : " << finish - start << "ms\n\n";

	start = clock();
	MiddleDijkstra(name, num, line);
	finish = clock();
	cout << "Dijkstra �˰��� ���� �ð� : " << finish - start << "ms\n\n";

	start = clock();
	MiddleAstar(name, num, line);
	finish = clock();
	cout << "A* �˰��� ���� �ð� : " << finish - start << "ms\n\n";
	cout << b[4];
	return 0;
}

void input(vector<string>& name, vector<int>& num, vector<int>& line)
{
	int i;

	cout << "����� ����� ���� �Է��ϼ��� :";
	cin >> i;
	cout << '\n';

	if (i < 2)
	{
		cout << "��� ��Ҵ� 2�� �̻��̿��� �˴ϴ�.\n";
		exit(1);
	}

	for (int k = 0; k < i; k++)
	{
		int _num, _line; string _name;
		cout << "�ش翪���� ž���ϴ� �ο��� ���� ȣ��, ���̸��� �Է��ϼ��� : ";
		cin >> _num >> _line >> _name;
		name.push_back(_name);
		line.push_back(_line);
		num.push_back(_num);
	}

	cout << "\n\n";
}