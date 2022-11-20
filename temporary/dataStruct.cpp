#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

typedef struct station Station;
typedef struct edge Edge;

typedef Station* StatPtr;

StatPtr Head;
StatPtr Line[10];

struct edge {
	unsigned long long weight;
	Station* next = NULL;

	edge(unsigned long long W, Station* N) { weight = W; next = N; }
};

struct station {
	string name;
	int line;
	vector<Edge> eList; //종착역이면 size = 0
	
	//int transfer = 0;

	station(string N, int L) { line = L; name = N; }
};


void readStr(string str, string& stat, int& line, string& nxt_stat, int& nxt_line, unsigned long long& w)
{
	//한상민이 준 데이터 셋 형식대로 
	//읽어온 한 줄의 데이터를 변수에 저장해줌
	//종착역이면 w = -1 저장
}

void readTrans(string str, string& present, int& line, string& next, int& nxt_line, unsigned long long& w)
{
	//환승데이터 형식으로 한 줄씩 읽어옴
	//읽어온 한 줄의 데이터를 변수에 저장해줌
}

StatPtr findStat(string name, int line)
{
	// dfs로 찾아서 해당 포인터 반환
}

void make_graph()
{
	ifstream readFile;
	string str;
	string stat, nxt_stat;
	int line, nxt_line;
	unsigned long long  w;
	StatPtr temp, present, next;

	readFile.open("1~9 역간시간");

	if (readFile.is_open())
	{
		//파일이 끝날 때까지 반복
		while (readFile.eof())
		{
			//각 호선의 Head포인터 초기화
			getline(readFile, str);
			readStr(str, stat, line, nxt_stat, nxt_line, w);

			temp = new Station(stat, line);

			Line[line] = present =  temp;

			temp = new Station(nxt_stat, nxt_line);

			getline(readFile, str);
			readStr(str, stat, line, nxt_stat, nxt_line, w);

			//다음 호선이 올 때까지 반복
			while (line == present->line)
			{
				//만약에 직전의 반복문에서 저장한 다음역이, 새로 받아온 문자열에서의 현재역과 다르다면
				//다음에 오는 역이 갈라지는 부분이므로 현재 역을 새로 업데이트 해준다
				if (stat == next->name) present = findStat(stat, line);

				next = new Station(nxt_stat, nxt_line);

				present->eList.push_back(edge(w, next));
				present = next;

				getline(readFile, str);
				readStr(str, stat, line, nxt_stat, nxt_line, w);
			}
		}
	}

	readFile.open("환승데이터(중복없이)");

	if (readFile.is_open())
	{
		//파일이 끝날 때까지 반복
		while (readFile.eof())
		{
			getline(readFile, str);
			readTrans(str, stat, line, nxt_stat, nxt_line, w);
			present = findStat(stat, line);
			next = findStat(nxt_stat, nxt_line);

			present->eList.push_back(edge(w, next));
			next->eList.push_back(edge(w, present));
		}
	}
}

int main()
{
	make_graph();
	//cout << 
}