#include "edge.h"
#include "station.h"

int main()
{
	Station a("�湫��",4,3), b("�湫��",3,3), c("��",4,2);
	Edge *edge = new Edge[2];
	edge[0].setLine(3);
	edge[0].setWeight(300);
	edge[0].setStaion(b);
	edge[1].setLine(4);
	edge[1].setWeight(400);
	edge[1].setStaion(c);
	a.setEdge(edge);
	a.setEdgeNum(2);
	cout << a.getEdge()[1].getStaion().getName() << '\n';
}