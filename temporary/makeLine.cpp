#include "makeLine.h"

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
	alloc->flag = flag;

	return alloc;
}

Edge* allocEdge(int line, W weight, Station* station)
{
	Edge* rst = new Edge;
	rst->line = line;
	rst->weight = weight;
	rst->next = station;

	return rst;
}

void middleStation(Station *n,Station *current,Station *N,W nWeight, W weight)
{
	Edge* tmp;
	
	tmp = allocEdge(n->line,nWeight,n);
	current->ptr.push_back(tmp);

	tmp = allocEdge(N->line, weight, N);
	current->ptr.push_back(tmp);
}

void lastStation(Station* n, Station* current, W nWeight)
{
	Edge* tmp;

	tmp = allocEdge(n->line, nWeight, n);
	current->ptr.push_back(tmp);
}

void swapStaion(Station*&n, Station*& current, Station*& N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag)
{
	n = current;
	current = N;
	nWeight = weight;
	weight = Nweight;
	flag = Nflag;
}

void makeLine(Station *&s, vector<string> str)
{
	Station* n, * N, * current, * branchEndStation = 0, * mergeStation = 0;
	Edge* tmp = 0;
	W nWeight, weight, Nweight;
	int flag, Nflag, num = 2;

	s = allocStation(str[0], weight, flag);
	current = allocStation(str[1], Nweight, flag);
	tmp = allocEdge(current->line,weight,current);
	s->ptr.push_back(tmp);
	
	n = s;
	nWeight = weight;
	weight = Nweight;

	for (int i = 1; i < (signed int)str.size() - 1; i++)
	{
		if (flag == 0)
		{
			num++;
			N = allocStation(str[i + 1], Nweight, Nflag);
			if (Nflag == 5 && branchEndStation)
				N = branchEndStation;

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
			
		}

		else if (flag == 1)
		{
			num++;
			N = allocStation(str[i + 1], Nweight, Nflag);
			
			middleStation(n, current, N, nWeight, weight);
			current->flag = 1;
			
			stackStation.push(current);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 2)
		{
			num += 3;
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
			tmp = allocEdge(current->line, nWeight, current);
			n->ptr.push_back(tmp);

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 3)
		{
			++num;
			N = allocStation(str[i + 1], Nweight, Nflag);
			N = mergeStation;

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);

			N = allocStation(str[++i + 1], Nweight, Nflag);
			tmp = allocEdge(n->line, nWeight, n);
			current->ptr.push_back(tmp);

			tmp = allocEdge(branchEndStation->line, branchEndStation->ptr[1]->weight, branchEndStation);
			current->ptr.push_back(tmp);
			branchEndStation = 0;
			tmp = allocEdge(N->line, weight, N);
			current->ptr.push_back(tmp);

			current->flag = 3;

			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 4)
		{
			num += 2;
			lastStation(n, current, nWeight);
			current->flag = 4;

			nWeight = weight; //flag 4의 역에 있는 가중치는 branchstation의 다음역으로 가는 가중치
			current = allocStation(str[i++ + 1], weight, flag);
			n = stackStation.top(); stackStation.pop();
			N = allocStation(str[i + 1], Nweight, Nflag);
			
			tmp = allocEdge(current->line, nWeight, current);
			n->ptr.push_back(tmp);
			

			middleStation(n, current, N, nWeight, weight);
			swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
		}

		else if (flag == 5)
		{
			if (!branchEndStation)
			{
				num++;
				N = allocStation(str[i + 1], Nweight, Nflag);
				middleStation(n, current, N, nWeight, weight);
				branchEndStation = current;
				swapStaion(n, current, N, nWeight, weight, Nweight, flag, Nflag);
			}
			else
			{
				current = branchEndStation;
				lastStation(n, current, nWeight);
				branchEndStation = 0;
			}
		}
	}
	if (flag == 5)
		current = branchEndStation;
	lastStation(n, current, nWeight);
}

void readFile(string name, vector<string>& vectorStr)
{
	ifstream txtFile;
	string str;
	txtFile.open(name);
	if (!txtFile.is_open())
	{
		cout << name + "파일이 없습니다.\n";
		exit(1);
	}
	while (getline(txtFile, str))
		vectorStr.push_back(str);
}