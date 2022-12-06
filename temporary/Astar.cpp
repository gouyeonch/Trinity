#include "header/Astar.h"

extern Station* stations[MAX];
extern int stationNum[MAX];

pair<double, double> center = make_pair(0, 0); // �����߽�
priority_queue<Station*, vector<Station*>, comp2> statFromCen;

void initVisit()
{
	for (int i = 0; i < MAX; i++)
	{
		Station* tmp = stations[i];
		tmp->visit = 0;
		for (int j = 0; j < stationNum[i]; j++)
		{
			goNext(tmp);
			tmp->visit = 0;
		}
	}
}

double calDistFromCenter(pair<double, double> stat)
{
	return sqrt(pow(stat.first - center.first, 2) + pow(stat.second - center.second, 2));
}

//��߿� ����Ʈ�� �޾Ƽ� �߰����� ��ȯ�ϴ� �Լ�
void calCenter(vector<pair<Station*, int>> &list)
{
	int n = 0, size = list.size();

	for (int i = 0; i < size; i++)
	{
		n += list[i].second;
		center.first += list[i].first->alt * list[i].second;
		center.second += list[i].first->lat * list[i].second;
	}
	center.first /= n;
	center.second /= n;
}

//center�κ����� �Ÿ��� �������� pq����
void makeCenterMap()
{
	for (int i = 0; i < MAX; i++)
	{
		Station* tmp = stations[i];

		statFromCen.push(tmp);

		for (int j = 1; j < stationNum[i]; j++)
		{
			goNext(tmp);
			statFromCen.push(tmp);
		}
	}
}

//�޸���ƽ �Լ�
double h(Station* a, Station* b)
{
	double g = sqrt(pow(b->alt - a->alt, 2) + pow(b->lat - a->lat, 2));
	return g;
}

int Astar(Station* start, Station* end)
{
	map<double, Anode*> O; //������� // �ٵ� �̰� pq�� �ص����� ������
	map<Station*, Anode*> O_find;
	vector<Anode*> C; // ���� ���
	//Anode *C;
	double F, H;
	int G, dist = 0, len;
	Station *ID, *temp;
	Anode *parent;

	//���ۿ� O�� �����鼭 �ʱ�ȭ
	O.insert({ 0, new Anode(start, 0, 0, 0, NULL) });

	while (start != end)
	{
		//C�� O���� F���� ���� ���� ���� ����
		O.begin()->second->ID->visit = 1; // C�� �����鼭 visit flag on
		//C = O.begin()->second;
		C.push_back(O.begin()->second); // O���� ���� F�� ���� �� C�� ����
		//cout << O.begin()->second->ID->name << endl;
		parent = O.begin()->second;
		temp = O.begin()->second->ID; //O���� ���� F ���� ���� �� �ӽ�����
		O.erase(O.begin()); // O���� ���� ���� �� ����

		if (temp == end) break;

		//���� ����� ��������Ʈ�� O�� ����
		for (int i = 0; i < temp->ptr.size(); i++)
		{
			if (temp->ptr[i]->next->visit == 0) // C�� ���� �͸� O�� �߰�
			{
				ID = temp->ptr[i]->next;
				G = temp->ptr[i]->weight + parent->G;
				H = h(temp->ptr[i]->next, end);
				F = G + H;

				//�̰� ���߿� �ð� �Ǹ� ����
				auto iter = O_find.find(ID);
				if (iter != O_find.end())
				{
					O_find.erase(iter);
					for (auto iter = O.begin(); iter != O.end(); iter++)
					{
						if (iter->second->ID == ID && iter->second->F > F)
						{
							O.erase(iter);
							break;
						}
					}
				}

				O.insert({ F, new Anode(ID, F, G, H, parent) });
				O_find.insert({ ID, new Anode(ID, F, G, H, parent) });
			}
		}

	}
	len = C.size();
	for (int i = 0; i < len; i++) C[i]->ID->visit = 0;

	return C.back()->G;
}

void printMin(vector < pair<vector<pair<Station*, int>>, Station*>> print_list)
{
	vector < pair<vector<pair<Station*, int>>, Station*>> min_list;
	vector<pair<Station*, int>> result;
	int max = 0, min = INT_MAX, len_i, len_j, avg = 0;

	//���� ���� ���� ���� ���� ����Ʈ ���·� ����
	len_i = print_list.size();
	for (int i = 0; i < len_i; i++)
	{
		//Astar list���� ���� ���� ã��
		max = print_list[i].first[0].second;
		len_j = print_list[i].first.size();
		for (int j = 0; j < len_j; j++)
		{
			if (print_list[i].first[j].second > max) max = print_list[i].first[j].second;
		}

		if (max < min)
		{
			min_list = vector < pair<vector<pair<Station*, int>>, Station*>>();
			min_list.push_back(make_pair(print_list[i].first, print_list[i].second));
			min = max;
		}
		else if (max == min) min_list.push_back(make_pair(print_list[i].first, print_list[i].second));
	}

	//���� �ð��� ���� ���� ���� �������� ���鼭 ��������ϰ� ����� ���� ���� ���� �����
	len_i = min_list.size();
	min = INT_MAX;
	for (int i = 0; i < len_i; i++)
	{
		avg = 0;
		len_j = min_list[i].first.size();
		for (int j = 0; j < len_j; j++) avg += min_list[i].first[j].second;
		avg /= (len_j);

		if (avg < min)
		{
			result = vector<pair<Station*, int>>();
			max = min_list[i].first[0].second;
			for (int j = 0; j < len_j; j++)
			{
				if (min_list[i].first[j].second > max) max = min_list[i].first[j].second;
			}
			result.push_back(make_pair(min_list[i].second, max));
			min = avg;
		}
		else if (avg == min)
		{
			max = min_list[i].first[0].second;
			for (int j = 0; j < len_j; j++)
			{
				if (min_list[i].first[j].second > max) max = min_list[i].first[j].second;
			}
			result.push_back(make_pair(min_list[i].second, max));
		}
	}

	len_i = result.size();

	if (len_i > 1)
	{
		cout << "A* �˰���\n";
		for (int i = 0; i < len_i; i++)
			cout << "�߰����� " << result[i].first->line << "ȣ�� " + result[i].first->name + "�Դϴ�." << endl;
	}
	else
	{
		cout << "A* �˰���\n";
		cout << "�߰����� " << result[0].first->line << "ȣ�� " + result[0].first->name + " �Դϴ�."<< endl;
	}
}

double calLimit(vector<pair<Station*, int>> start_list)
{
	int len;
	double max, temp;

	max = calDistFromCenter(make_pair(start_list[0].first->alt, start_list[0].first->lat));

	len = start_list.size();
	for (int i = 1; i < len; i++)
	{
		temp = calDistFromCenter(make_pair(start_list[i].first->alt, start_list[i].first->lat));
		if (max < temp) max = temp;
	}

	return max;
}

void MiddleAstar(vector<string>name, vector<int>num, vector<int>line)
{
	int total = name.size();
	int dist;
	int flag = 0;
	double limit;
	vector<pair<Station*, int>> start_list; // ��߿� ����Ʈ
	vector < pair<Station*, int>> TargetList; // ��߿�, �����������ǰŸ�
	vector < pair<vector<pair<Station*, int>>, Station*>> print_list; // TargetList, ������

	Station* target;

	for (int i = 0; i < name.size(); i++)
		start_list.push_back(pair<Station*, int>(findStat(name[i], line[i]), num[i]));

	//make center
	calCenter(start_list);

	limit = calLimit(start_list);

	//center�� ������ �Ÿ��� ���� pq����
	makeCenterMap();

	initVisit();
	//�ϴ� 10���� �켱������ �����Ÿ� ���
	for (int i = 0; i < 449; i++)
	{
		flag = 0;
		//center�� ���� ����� ������ ���� �̾Ƴ�
		target = statFromCen.top();
		//cout << target->name << endl;

		if (calDistFromCenter(make_pair(target->alt, target->lat)) > limit) break;

		statFromCen.pop();
		TargetList = vector < pair<Station*, int>>();

		for (int j = 0; j < total; j++)
		{
			//initVisit();
			if (start_list[j].first == target)
			{
				flag = 1;
				break;
			}
			TargetList.push_back(make_pair(start_list[j].first, Astar(start_list[j].first, target) * start_list[j].second)); // ��� ��߿����� ������������ ��� �Ÿ��� list���·� ����
			//cout << TargetList[j].first->name << " " << TargetList[j].second << " " << target->name << endl;
		}
		if (flag != 1) print_list.push_back(make_pair(TargetList, target)); // ������ ���� list�� �������� list���·� ���� ���Ŀ� min�Լ����� ��
	}

	printMin(print_list);
}