#include "dataStruct.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;
extern Station* stations[9];

void tokenized(string str, int& line, string& name, W& weight, int& flag);
Station* allocStation(string str, W& weight, int& flag); 
void swapStaion(Station*& n, Station*& current, Station*& N, W& nWeight, W& weight, W& Nweight, int& flag, int& Nflag);
void lastStation(Station* n, Station* current, W nWeight);
void makeGraph(Station*& s, vector<string> str);
void readFile(string num, vector<string>& vectorStr);

bool goNext(Station*& tmp);

int main()
{
	vector<string> vectorStr;
	readFile("1", vectorStr);
	makeGraph(stations[0], vectorStr);
	Station* tmp = stations[0];
	for (int i = 0; i < vectorStr.size(); i++)
	{
		cout << tmp->name << endl;
		if (!goNext(tmp))
			break;
	}
	cout << endl;
	
}

