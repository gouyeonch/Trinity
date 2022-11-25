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
void makeAllLine();
bool goNext(Station*& tmp);

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
			cout << j << tmp->name << endl;
			if (!goNext(tmp))
				break;
		}
		cout << endl;
	}
	
	cout << endl;
	
}

