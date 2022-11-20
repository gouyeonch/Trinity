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
	vector<Edge> eList; //�������̸� size = 0
	
	//int transfer = 0;

	station(string N, int L) { line = L; name = N; }
};


void readStr(string str, string& stat, int& line, string& nxt_stat, int& nxt_line, unsigned long long& w)
{
	//�ѻ���� �� ������ �� ���Ĵ�� 
	//�о�� �� ���� �����͸� ������ ��������
	//�������̸� w = -1 ����
}

void readTrans(string str, string& present, int& line, string& next, int& nxt_line, unsigned long long& w)
{
	//ȯ�µ����� �������� �� �پ� �о��
	//�о�� �� ���� �����͸� ������ ��������
}

StatPtr findStat(string name, int line)
{
	// dfs�� ã�Ƽ� �ش� ������ ��ȯ
}

void make_graph()
{
	ifstream readFile;
	string str;
	string stat, nxt_stat;
	int line, nxt_line;
	unsigned long long  w;
	StatPtr temp, present, next;

	readFile.open("1~9 �����ð�");

	if (readFile.is_open())
	{
		//������ ���� ������ �ݺ�
		while (readFile.eof())
		{
			//�� ȣ���� Head������ �ʱ�ȭ
			getline(readFile, str);
			readStr(str, stat, line, nxt_stat, nxt_line, w);

			temp = new Station(stat, line);

			Line[line] = present =  temp;

			temp = new Station(nxt_stat, nxt_line);

			getline(readFile, str);
			readStr(str, stat, line, nxt_stat, nxt_line, w);

			//���� ȣ���� �� ������ �ݺ�
			while (line == present->line)
			{
				//���࿡ ������ �ݺ������� ������ ��������, ���� �޾ƿ� ���ڿ������� ���翪�� �ٸ��ٸ�
				//������ ���� ���� �������� �κ��̹Ƿ� ���� ���� ���� ������Ʈ ���ش�
				if (stat == next->name) present = findStat(stat, line);

				next = new Station(nxt_stat, nxt_line);

				present->eList.push_back(edge(w, next));
				present = next;

				getline(readFile, str);
				readStr(str, stat, line, nxt_stat, nxt_line, w);
			}
		}
	}

	readFile.open("ȯ�µ�����(�ߺ�����)");

	if (readFile.is_open())
	{
		//������ ���� ������ �ݺ�
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