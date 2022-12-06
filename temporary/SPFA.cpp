#include "header/SPFA.h"

extern Station* stations[MAX];
extern int stationNum[MAX];

void MiddleSPFA(vector<string> name, vector<int> num, vector<int> line)
{
	map<Station*, W>* dist = new map<Station*, W>[name.size()];
	for (int i = 0; i < name.size(); i++)
	{
		if (!SPFA(dist[i], num[i], line[i], name[i]))
		{
			cout << "음수 사이클입니다. 중간역은 없습니다.\n";
			return;
		}
		reset();
		if (dist[i].size() != MAX_STAION)
			cout << "모든 역을 방문하지 않았습니다 " << i + 1 << endl;
	}
	
	cout << "SPFA 알고리즘\n";
	compareStation(dist, name.size());
}

bool SPFA(map<Station*, W>& dist, int num, int line, string name)
{
	map<Station*, bool> inq;
	queue<Station*> q;
	map<Station*, int> nodeCnt;
	Station* start;

	start = findStat(name, line);
	start->opt = 0;
	dist[start] = 0;
	inq[start] = 1;
	nodeCnt[start]++;
	q.push(start);
	while (q.size())
	{
		Station* cur = q.front(); q.pop(); inq[cur] = 0;
		for (int i = 0; i < cur->ptr.size(); i++)
		{
			Station* tmp = cur->ptr[i]->next;
			W tmpW = cur->ptr[i]->weight;
			if (dist[cur] + tmpW < tmp->opt)
			{
				dist[tmp] = tmp->opt = dist[cur] + tmpW;
				if (!inq[tmp]) {
					//if (++nodeCnt[tmp] >= MAX_STAION) //음수 사이클
					//	return false;
					inq[tmp] = 1;
					q.push(tmp);
				}
			}
		}
	}

	if (num != 1)
	{
		for (auto& i : dist)
			i.second *= num;
	}
	
	return true;
}