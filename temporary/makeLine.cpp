#include "dataStruct.h"
#include <vector>
#include <sstream>
#include <string>
#include <stack>
Station* stations[9];
stack<Station*> stackStation;

void tokenized(string str, int& line, string& name, W& weight, int& flag)
{
	string a[4];
	stringstream ss(str);

	ss >> a[0] >> a[1] >> a[2] >> a[3];
	line = stoi(a[0]);
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	flag = stoi(a[3]);
}

Station* allocStation(string str, W& weight, int &flag)
{
	Station *alloc = new Station;
	tokenized(str, alloc->line, alloc->name, weight, flag);

	return alloc;
}

void middleStation(Station *n,Station *current,Station *N,W nWeight, W weight)
{
	current->ptr[0] = new Edge;
	current->ptr[0]->line = n->line;
	current->ptr[0]->weight = nWeight;
	current->ptr[0]->next = n;

	current->ptr[1] = new Edge;
	current->ptr[1]->line = N->line;
	current->ptr[1]->weight = weight;
	current->ptr[1]->next = N;
}

void lastStation(Station* n, Station* current, W nWeight)
{
	current->ptr[0] = new Edge;
	current->ptr[0]->line = n->line;
	current->ptr[0]->weight = nWeight;
	current->ptr[0]->next = n;
}

void swapStaion(Station* n, Station* current, Station* N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag)
{
	n = current;
	current = N;
	nWeight = weight;
	weight = Nweight;
	flag = Nflag;
}

void makeGraph(Station *s, vector<string> str)
{
	Station* n, * N, * current, * branchEndStation, *mergeStation;
	EdgePtr ptr;

	W nWeight, weight, Nweight;
	int flag, Nflag;

	s = allocStation(str[0], weight, flag);
	current = allocStation(str[1], Nweight, flag);
	s->ptr[1] = new Edge;
	s->ptr[1]->line = current->line;
	s->ptr[1]->weight = weight;
	s->ptr[1]->next = current;
	n = s;
	nWeight = weight;
	weight = Nweight;

	for (int i = 1; i < str.size() - 1; i++)
	{
		if (flag == 0)
		{
			N = allocStation(str[i + 1], Nweight, Nflag);
			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 1)
		{
			N = allocStation(str[i + 1], Nweight, Nflag);

			current->ptr[0] = new Edge;
			current->ptr[0]->line = n->line;
			current->ptr[0]->weight = nWeight;
			current->ptr[0]->next = n;

			current->ptr[1] = new Edge[2];
			current->ptr[1][0].line = N->line;
			current->ptr[1][0].weight = weight;
			current->ptr[1][0].next = N;

			stackStation.push(current);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 2)
		{
			N = allocStation(str[i + 1], Nweight, Nflag);
			middleStation(n, current, N, nWeight, weight);

			branchEndStation = current;
			mergeStation = N;
			nWeight = Nweight; //성수역에 있는 가중치는 신도림 -> 문래 가중치임

			N = allocStation(str[++i + 1], Nweight, Nflag);
			n = stackStation.top(); stackStation.pop();
			current = N;
			weight = Nweight;
			flag = Nflag;

			N = allocStation(str[++i + 1], Nweight, Nflag);
			n->ptr[1][1].line = current->line;
			n->ptr[1][1].next = current;
			n->ptr[1][1].weight = nWeight;

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 3)
		{
			N = allocStation(str[i + 1], Nweight, Nflag);
			N = mergeStation;

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);

			N = allocStation(str[++i + 1], Nweight, Nflag);
			current->ptr[0] = new Edge[2];
			current->ptr[0][1].line = n->line;
			current->ptr[0][1].weight = nWeight;
			current->ptr[0][1].next = n;

			current->ptr[0][0].line = branchEndStation->line;
			current->ptr[0][0].weight = branchEndStation->ptr[1]->weight;
			current->ptr[0][0].next = branchEndStation;

			current->ptr[1] = new Edge;
			current->ptr[1]->line = N->line;
			current->ptr[1]->weight = weight;
			current->ptr[1]->next = N;

			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 4)
		{
			lastStation(n, current, nWeight);

			nWeight = weight; //flag 4의 역에 있는 가중치는 branchstation의 다음역으로 가는 가중치
			current = allocStation(str[i++ + 1], weight, flag);
			n = stackStation.top(); stackStation.pop();
			N = allocStation(str[i + 1], Nweight, Nflag);
			
			n->ptr[1][1].line = current->line;
			n->ptr[1][1].next = current;
			n->ptr[1][1].weight = nWeight;

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}
	}

	lastStation(n, current, nWeight);
}