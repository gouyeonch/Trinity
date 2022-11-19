#include <iostream>

using namespace std;

typedef struct edge* EdgePtr;

typedef struct station {
	int line;
	EdgePtr ptr;
	string name;
	int transfer = 0;
}Station;

typedef struct edge {
	int line;
	unsigned long long weight;
	Station* next = NULL;
}Edge;



int main()
{
	Station a, b, c;
	a.name = "面公肺";
	a.transfer = 1;
	a.line = 4;

	b.name = "疙悼";
	b.transfer = 0;
	b.line = 4;

	c.name = "面公肺";
	c.line = 3;
	c.transfer = 1;

	a.ptr = new Edge[2];
	a.ptr[0].line = b.line;
	a.ptr[0].weight = 400;
	a.ptr[0].next = &b;

	cout << a.ptr[0].next->name;
}