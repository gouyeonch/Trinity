#include "dataStruct.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;
extern Station* stations[9];
extern int stationNum[9];

void tokenized(string str, int& line, string& name, W& weight, int& flag);
Station* allocStation(string str, W& weight, int& flag); 
void swapStaion(Station*& n, Station*& current, Station*& N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag);
void lastStation(Station* n, Station* current, W nWeight);
void makeLine(Station*& s, vector<string> str);
void readFile(string num, vector<string>& vectorStr);
void transferToken(string& str, int& num, string& name, W& weight, int& transfer);
bool goNext(Station*& tmp);
Edge* allocEdge(int line, W weight, Station* station);
void linkTransfer(vector<string>& vectorStr);
void makeAllLine();

int main()
{
	makeAllLine();
	string num = "1";
	for (int i = 0; i < 9; i++, num[0]++)
	{
		Station* tmp = stations[i];
		cout << num + "È£¼±"<<" "<<stationNum[i]<<"\n";
		for (int j = 0; j < stationNum[i]; j++)
		{
			if (i + 1 != tmp->line)
			{
				cout << tmp->name << tmp->line;
				return 0;
			}
			cout << j << " " << tmp->name << " " << tmp->flag << endl;
			if (!goNext(tmp))
				break;
		}
		cout << endl;
	}
	
	cout << endl;
	
}

