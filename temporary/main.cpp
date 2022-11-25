#include "header/makeSubway.h"

using namespace std;
extern Station* stations[9];
extern int stationNum[9];

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

