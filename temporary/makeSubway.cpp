#include "header/makeSubway.h"

extern Station* stations[MAX];
int stationNum[MAX];

void makeAllLine()
{
	vector<string> vectorStr;
	string name = "txt/지하철1.txt";
	for (int i = 0; i < MAX; i++, name[10]++)
	{
		readFile(name, vectorStr);
		makeLine(stations[i], vectorStr);
		stationNum[i] = vectorStr.size();
		vectorStr.clear();
	}
	name = "txt/환승역.txt";
	readFile(name, vectorStr);
	linkTransfer(vectorStr);
	setPlace();
	//setWeight(); 
}

void linkTransfer(vector<string>& vectorStr)
{
	int num, transfer;
	string name;
	W weight;
	Station *tmp1, *tmp2;

	for (int i = 0; i < vectorStr.size(); i++)
	{
		tokenized(vectorStr[i], num, transfer, name, weight);
		tmp1 = stations[num];
		tmp2 = stations[transfer];
		for (int j = 0; tmp1->name != name; j++)
		{
			if (j == stationNum[num])
			{
				cout << name + "은 " << num + 1 << "호선에 있는 환승역이 아닙니다.\n";
				exit(1);
			}
			goNext(tmp1);
		}
		visitClear();
		for (int k = 0; tmp2->name != name; k++)
		{
			if (k == stationNum[transfer])
			{
				cout << name + "은 " << transfer + 1 << "호선에 있는 환승역이 아닙니다.\n";
				exit(1);
			}
			goNext(tmp2);
		}
		visitClear();
		lastStation(tmp2, tmp1, weight);
		tmp1->transfer = 1;
	}
}

void setPlace() 
{
	string txtName = "한상민전송용/좌표_1호선.txt";
	for (int i = 0; i < MAX; i++, txtName[18]++) {

		vector<string> vectorStr;
		readFile(txtName, vectorStr);
		Station* tmp = stations[i];
		for (int j = 0; j < vectorStr.size(); j++) {
			string name;
			double alt, lat;
			W weight;
			tokenized(vectorStr[j], name, weight, alt, lat);
			if (name == tmp->name) {
				tmp->lat = lat;
				tmp->alt = alt;
				tmp->visit = 1;
				goNext(tmp);
			}
			else {
				tmp = stations[i];
				int flag = 0;
				for (int k = 0; k < stationNum[i]; k++)
				{
					if (tmp->name != name)
						goNext(tmp);
					else
					{
						tmp->lat = lat;
						tmp->alt = alt;
						tmp->visit = 1;
						flag = 1;
						goNext(tmp);
						break;
					}
				}

				if (!flag)
				{
					cout << name << "is " << i + 1 << " not station";
					exit(1);
				}
			}
		}
	}
}

void setWeight() 
{
	string txtName = "한상민전송용/가중치_1호선.txt";
	for (int i = 0; i < MAX; i++, txtName[20]++)
	{
		vector<string> vectorStr;
		readFile(txtName, vectorStr);
		Station* tmp = stations[i];
		for (int j = 0; j < vectorStr.size(); j++) {
			string name, Name;
			W weight;
			tokenized(vectorStr[j], name, weight, Name);

			tmp = stations[i];
			int flag = 0;
			for (int k = 0; k < stationNum[i]; k++)
			{
				if (tmp->name != name)
					goNext(tmp);
				else
				{
					Station* Ntmp;
					for (int l = 0; l < tmp->ptr.size(); l++)
					{
						if (Name == tmp->ptr[l]->next->name && tmp->ptr[l]->line == i + 1)
						{
							Ntmp = tmp->ptr[l]->next;
							tmp->ptr[l]->weight = weight;
							Ntmp->visit = 1;
							tmp->visit = 1;
							for (int m = 0; m < Ntmp->ptr.size(); m++)
							{
								if (name == Ntmp->ptr[m]->next->name && Ntmp->ptr[m]->line == i + 1)
								{
									Ntmp->ptr[m]->weight = weight;
									flag = 1;
									break;
								}
							}
							if (!flag)
							{
								cout << "2중포문 안 " << name + " " + Name << "is " << i + 1 << " not station";
								exit(1);
							}
							flag = 1;
							break;
						}
					}

					break;
				}
			}

			if (!flag)
			{
				cout << name + " " + Name << "is " << i + 1 << " not station";
				exit(1);
			}
			visitClear();
		}
	}
}
