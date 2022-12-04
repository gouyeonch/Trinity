#include "header/Astar.h"

extern Station* stations[MAX];
extern int stationNum[MAX];

pair<double, double> center = make_pair(0, 0); // 무게중심
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

//출발역 리스트를 받아서 중간역을 반환하는 함수
void calCenter(vector<pair<Station*, int>> &list)
{
    int n = 0, size = list.size();

    for(int i = 0; i < size; i++)
    {
        n += list[i].second;
        center.first += list[i].first->alt * list[i].second;
        center.second += list[i].first->lat * list[i].second;
    }
    center.first /= n;
    center.second /= n;
}

//center로부터의 거리를 기준으로 pq생성
void makeCenterMap()
{
    for(int i = 0; i < MAX; i++)
    {
		Station* tmp = stations[i];

        statFromCen.push(tmp);

		for(int j = 1; j < stationNum[i]; j++)
        {
			goNext(tmp);
			statFromCen.push(tmp);
		}
	}
}

//휴리스틱 함수
double h(Station* a, Station* b)
{
	double g = sqrt(pow(b->alt - a->alt, 2) + pow(b->lat - a->lat, 2));
    return g;
}

int Astar(Station* start, Station* end)
{
	map<double, Anode*> O; //열린목록 // 근데 이거 pq로 해도되지 않을까
	vector<Anode*> C; // 닫힌 목록
	double F, H;
	int G, dist = 0;
	Station *ID, *temp;
	Anode *parent;

	//시작역 O에 넣으면서 초기화
	O.insert({ 0, new Anode(start, 0, 0, 0, NULL) });

	while (start != end)
	{
		//C에 O에서 F값이 가장 작은 값을 넣음
		O.begin()->second->ID->visit = 1; // C에 넣으면서 visit flag on
		C.push_back(O.begin()->second); // O에서 가장 F가 작은 값 C에 삽입
		//cout << O.begin()->second->ID->name << endl;
		parent = O.begin()->second;
		temp = O.begin()->second->ID; //O에서 가장 F 값이 작은 값 임시저장
		O.erase(O.begin()); // O에서 가장 작은 값 삭제
		
		if (temp == end) break;
		
		//현재 노드의 인접리스트들 O에 삽입
		for (int i = 0; i < temp->ptr.size(); i++)
		{
			if (temp->ptr[i]->next->visit == 0) // C에 없는 것만 O에 추가
			{
				ID = temp->ptr[i]->next;
				G = temp->ptr[i]->weight + parent->G;
				H = h(temp->ptr[i]->next, end);
				F = G + H;

				//이거 나중에 시간 되면 개선
				for (auto iter = O.begin(); iter != O.end(); iter++)
				{
					if (iter->second->ID == ID && iter->second->F > F)
					{
						O.erase(iter);
						break;
					}
				}
				O.insert({ F, new Anode(ID, F, G, H, parent) });
			}
		}
	}

	return C.back()->G;
}

void printMin(vector < pair<vector<pair<Station*, int>>, Station*>> end_list)
{
	vector < pair<vector<pair<Station*, int>>, Station*>> min_list;
	vector<pair<Station*, int>> result;
	int max = 0, min = INT_MAX, len_i, len_j, avg= 0;

	//상한 값이 제일 작은 역을 리스트 형태로 저장
	len_i = end_list.size();
	for (int i = 0; i < len_i; i++)
	{
		//Astar list에서 상한 값을 찾음
		max = end_list[i].first[0].second;
		len_j = end_list[i].first.size();
		for (int j = 0; j < len_j; j++)
		{
			if (end_list[i].first[j].second > max) max = end_list[i].first[j].second;
		}

		if (max < min)
		{
			min_list = vector < pair<vector<pair<Station*, int>>, Station*>>();
			min_list.push_back(make_pair(end_list[i].first, end_list[i].second));
			min = max;
		}
		else if(max == min) min_list.push_back(make_pair(end_list[i].first, end_list[i].second));
	}

	
	//상한 시간이 제일 작은 역이 여러개면 돌면서 평균저장하고 평균이 제일 적은 값을 출력함
	len_i = min_list.size();
	min = INT_MAX;
	for (int i = 0; i < len_i; i++)
	{
		len_j = min_list[i].first.size();
		for (int j = 0; j < len_j; j++) avg += min_list[i].first[j].second;
		avg /= (len_j + 1);

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
	cout << "A* 알고리즘\n";
	for (int i = 0; i < len_i; i++)
		cout << "중간역은 " << result[i].first->line << "호선 " + result[i].first->name + "입니다." << endl;

}

void MiddleAstar(vector<string>name, vector<int>num, vector<int>line)
{
    int total = name.size();
	int dist;
	int flag = 0;
    vector<pair<Station*, int>> start_list; // 출발역 리스트
	vector < pair<Station*, int>> AstarList; // 출발역, 도착역까지의거리
	vector < pair<vector<pair<Station*, int>>, Station*>> end_list; // astarlist, 도착역
    
    Station* target;

	for(int i = 0; i < name.size(); i++)
		start_list.push_back(pair<Station*, int>(findStat(name[i], line[i]), num[i]));

    //make center
    calCenter(start_list);
    
    //center로 부터의 거리에 따른 pq생성
    makeCenterMap();

    //일단 10개만 우선적으로 최적거리 계산
    for(int i = 0; i < 100; i++)
    {
		flag = 0;
        //center로 부터 가까운 순으로 역을 뽑아냄
        target = statFromCen.top();
        statFromCen.pop();
		AstarList = vector < pair<Station*, int>>();
        
        for(int j = 0; j < total; j++)
        {
			initVisit();
			if (start_list[j].first == target)
			{
				flag = 1;
				break;
			}
			AstarList.push_back(make_pair(start_list[j].first, Astar(start_list[j].first, target) * start_list[j].second)); // 모든 출발역에서 도착역까지의 모든 거리를 list형태로 받음
			//cout << AstarList[j].first->name << " " << AstarList[j].second << " " << target->name << endl;
        }
		if(flag != 1) end_list.push_back(make_pair(AstarList, target)); // 위에서 받은 list와 도착역을 list형태로 저장 추후에 min함수에서 비교
    }

	printMin(end_list);
}