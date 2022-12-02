#include "header/makeSubway.h"
#include "header/Dijkstra.h"
#include <queue>
#include <map>
#include <set>
#define MAX_STAION 449

extern Station* stations[9];
extern int stationNum[9];

void reset();
void MiddleSPFA(vector<string> name, vector<int> num, vector<int> line);
bool SPFA(map<Station*, W>& dist, int num, int line, string name);

void compareStation(map<Station*, W>* dist, unsigned int size)
{
	vector <pair<Station*, W>>* rst = new vector <pair<Station*, W>>[size];
	pair<Station*, W>max;
	W min = 987654321;
	map<Station*, W>::iterator* it = new map<Station*, W>::iterator[size];
	for (int i = 0; i < size; i++)
		it[i] = dist[i].begin();

	for (int i = 0; i < MAX_STAION; i++)
	{
		max.first = it[0]->first; max.second = it[0]->second;
		for (int j = 1; j < size; j++) //상한시간 찾기
		{
			if (max.second < it[j]->second)
			{
				max.first = it[j]->first; max.second = it[j]->second;
			}
		}
		//TESTING CODE
		/*if (max.first->name == "노량진")
		{
			for (int i = 0; i < size; i++)
				cout << max.first->line<< name[i] << " 중간역은 " << it[i]->first->name << " 이며 상한시간은 " << it[i]->second << " 입니다.\n";
		}*/
		//TESTING CODE END
		if (min > max.second)
		{
			min = max.second;
			for (int j = 0; j < size; j++)
			{
				rst[j].clear();
				rst[j].push_back(make_pair(it[j]->first, it[j]->second));
			}
		}
		else if (min == max.second)
			for (int j = 0; j < size; j++)
				rst[j].push_back(make_pair(it[j]->first, it[j]->second));
		for (int j = 0; j < size; j++)
			it[j]++;
	}
	if (rst[0].size() != 1)
	{
		W tmp; W avrMin = 987654321; vector<int> ind;
		for (int i = 0; i < rst[0].size(); i++)
		{
			tmp = 0;
			for (int j = 0; j < size; j++)
				tmp += rst[j][i].second;
			if (avrMin > tmp)
			{
				ind.clear();
				ind.push_back(i);
				avrMin = tmp;
			}
			else if (avrMin == tmp)
				ind.push_back(i);
		}
		for (int i = 0; i < ind.size(); i++)
			cout << "중간역은 " << rst[0][ind[i]].first->name << " 이며 상한시간은 " << min << " 입니다.\n";
	}

	else
		cout << "중간역은 " << rst[0][0].first->name << " 이며 상한시간은 " << min << " 입니다.\n";
}

void MiddleSPFA(vector<string> name, vector<int> num, vector<int> line)
{
	map<Station*, W>* dist = new map<Station*, W>[name.size()];
	for (int i = 0; i < name.size(); i++)
	{
		SPFA(dist[i], num[i], line[i], name[i]);
		reset();
		if (dist[i].size() != MAX_STAION)
			cout << "시발 틀림 " << i << endl;
	}
	
	//vector <pair<Station*, W>>* rst = new vector <pair<Station*, W>>[name.size()];
	//pair<Station*, W>max;
	//W min = 987654321;
	//map<Station*, W>::iterator* it = new map<Station*, W>::iterator[name.size()];
	//for (int i = 0; i < name.size(); i++)
	//	it[i] = dist[i].begin();
	//
	//for (int i = 0; i < MAX_STAION; i++)
	//{
	//	max.first = it[0]->first; max.second = it[0]->second;
	//	for (int j = 1; j < name.size(); j++) //상한시간 찾기
	//	{
	//		if (max.second < it[j]->second)
	//		{
	//			max.first = it[j]->first; max.second = it[j]->second;
	//		}
	//	}
	//	//TESTING CODE
	//	/*if (max.first->name == "노량진")
	//	{
	//		for (int i = 0; i < name.size(); i++)
	//			cout << max.first->line<< name[i] << " 중간역은 " << it[i]->first->name << " 이며 상한시간은 " << it[i]->second << " 입니다.\n";
	//	}*/
	//	//TESTING CODE END
	//	if (min > max.second)
	//	{
	//		min = max.second;
	//		for (int j = 0; j < name.size(); j++)
	//		{
	//			rst[j].clear();
	//			rst[j].push_back(make_pair(it[j]->first, it[j]->second));
	//		}
	//	}
	//	else if(min == max.second)
	//		for (int j = 0; j < name.size(); j++)
	//			rst[j].push_back(make_pair(it[j]->first, it[j]->second));
	//	for (int j = 0; j < name.size(); j++)
	//		it[j]++;
	//}
	//if (rst[0].size() != 1)
	//{
	//	W tmp; W avrMin = 987654321; vector<int> ind;
	//	for (int i = 0; i < rst[0].size(); i++)
	//	{
	//		tmp = 0;
	//		for (int j = 0; j < name.size(); j++)
	//			tmp += rst[j][i].second;
	//		if (avrMin > tmp)
	//		{
	//			ind.clear();
	//			ind.push_back(i);
	//			avrMin = tmp;
	//		}
	//		else if (avrMin == tmp)
	//			ind.push_back(i);
	//	}
	//	for (int i = 0; i < ind.size(); i++)
	//		cout << "중간역은 " << rst[0][ind[i]].first->name << " 이며 상한시간은 " << min << " 입니다.\n";
	//}
	//
	//else
	//	cout << "중간역은 " << rst[0][0].first->name << " 이며 상한시간은 " << min << " 입니다.\n";
}

bool SPFA(map<Station*, W>& dist, int num, int line, string name)
{
	map<Station*, bool> inq;
	queue<Station*> q;
	map<Station*, int> nodeCnt;
	Station* start = stations[line - 1];

	while (start->name != name)
		goNext(start);

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
					if (++nodeCnt[tmp] >= MAX_STAION) //음수 사이클
						return false;
					inq[tmp] = 1;
					q.push(tmp);
				}
			}
		}
	}

	for (auto& i : dist)
		i.second *= num;

	return true;
}