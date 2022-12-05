#include "header/shareFunc.h"

extern Station* stations[MAX];
extern int stationNum[MAX];

Station* findStat(string name, int line)
{
    Station* temp = stations[line - 1];
    int flag = 0;
	if (temp->name == name)
		return temp;

    for (int i = 0; i < stationNum[line - 1]; i++)
    {
		goNext(temp);
        if (temp->name == name)
        {
            flag = 1;
            break;
        }
    }
	visitClear();
    if (!flag)
    {
        cout << name + "은 " << line << "에 있는 역이 아닙니다.\n";
        exit(1);
    }

    return temp;
}

void reset()
{
	for (int i = 0; i < MAX; i++)
	{
		Station* tmp = stations[i];
		tmp->opt = ULLONG_MAX;
		for (int j = 0; j < stationNum[i]; j++)
		{
			goNext(tmp);
			tmp->opt = ULLONG_MAX;
		}
		visitClear();
	}
}

void compareStation(map<Station*, W>* dist, unsigned int size)
{
	vector <pair<Station*, W>>* rst = new vector <pair<Station*, W>>[size];
	pair<Station*, W>max;
	W min = ULLONG_MAX;
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
				max.first = it[j]->first; 
				max.second = it[j]->second;
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

	if (rst[0].size() > 1)
	{
		W tmp; W avrMin = ULLONG_MAX; vector<int> ind;
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
		cout << "다음 나오는 역들은 상한시간은 " << min << " 로 같고 평균시간도 같습니다\n";
		for (int i = 0; i < ind.size(); i++)
		{
			W sum = 0;
			cout << "중간역은 " << rst[0][ind[i]].first->line << "호선 " << rst[0][ind[i]].first->name << "이고 평균시간은 ";
			for (int j = 0; j < size; j++)
				sum += rst[j][ind[i]].second;
			cout << sum / size << "입니다.\n";
		}
		
	}

	else if (rst[0].size() == 1)
		cout << "중간역은 " << rst[0][0].first->line << "호선 " << rst[0][0].first->name << min << " 입니다.\n";
}