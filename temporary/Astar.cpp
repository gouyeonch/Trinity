#include "header/Astar.h"

using namespace std;

extern Station* stations[9];
extern int stationNum[9];

pair<double, double> center = make_pair(0, 0); // 무게중심

double calDistFromCenter(pair<double, double> stat)
{
    return sqrt(pow(stat.first - center.first, 2) + pow(stat.second - center.second, 2));
}

struct comp
{
    bool operator()(Station* s1, Station* s2)
    {
        pair<double, double> a = make_pair(s1->alt, s1->lat);
        pair<double, double> b = make_pair(s2->alt, s2->lat);

        return calDistFromCenter(a) > calDistFromCenter(b);
    }
};
priority_queue<Station*, vector<Station*>, comp> statFromCen;

//해당역을 찾아주는 함수
Station* findStat(string name, int line)
{
    Station* temp = stations[line-1];

    while(temp->name != name) goNext(temp); 

    return temp;
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
    for(int i = 0; i < 9; i++)
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

double Astar(Station* s, Station* e)
{
    double min = DOUBLE_MAX;
    int f;
	Station* temp;

    while(s != e)
    {
        min = s->ptr[0]->weight + h(s->ptr[0]->next, e);
		temp = s->ptr[0]->next;
        for(int i = 1; i < s->ptr.size(); i++)
        {
            if(s->ptr[i]->next->visit == 0)
            {
                f = s->ptr[i]->weight + h(s, e);
				if (min > f)
				{
					min = f;
					temp = s->ptr[i]->next;
				}
            }
        }
		s = temp;
    }

    return min;
}

void searchMiddle()
{
    int total;
    vector<pair<Station*, int>> start_list; // 출발역 리스트
    
    Station* target;

	cout << "총 몇개 역인지 입력해주세요";
	cin >> total;

	for(int i = 0; i < total; i++){
		int n , input_line;	// 사람수, 몇호선인지
		string station_name; // 역이름

		cout << "사람수 몇호선 역이름 : ";
		cin >> n >> input_line >> station_name;

        //출발역과 일치하는 노드를 가져오고
        //출발역과 사람 수를 출발역 리스트에 저장
        start_list.push_back(pair<Station*, int>(findStat(station_name, input_line), n));
	}

    //make center
    calCenter(start_list);
    
    //center로 부터의 거리에 따른 pq생성
    makeCenterMap();

    //일단 10개만 우선적으로 최적거리 계산
    for(int i = 0; i < 10; i++)
    {
        //center로 부터 가까운 순으로 역을 뽑아냄
        target = statFromCen.top();
        statFromCen.pop();
        
        for(int j = 0; j < total; j++)
        {
            cout << Astar(start_list[j].first, target) << endl;
        }
    }
}