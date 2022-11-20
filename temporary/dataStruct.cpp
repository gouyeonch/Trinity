#include <iostream>
#include <vector>

using namespace std;

typedef struct station Station;
typedef struct edge Edge;

struct edge {
	unsigned long long weight;
	Station* next = NULL;

	edge(unsigned long long W, Station* N) { weight = W; next = N;}
};

struct station {
	int line;
	vector<Edge> eList;
	string name;
	//int transfer = 0;
};

int main()
{
	Station a, b, c;
	a.name = "충무로";
	a.line = 4;

	b.name = "명동";
	b.line = 4;

	c.name = "충무로";
	c.line = 3;

	a.eList.push_back(edge(100, &b));
	b.eList.push_back(edge(999, &c));

	cout << a.eList[0].weight << " " << a.eList[0].next->name;
	//cout << 
}