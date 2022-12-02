#include "header/makeSubway.h"
#include "header/Dijkstra.h"
#include "header/Astar.h"
#include <queue>
#include <map>
#include <string>

void MiddleSPFA(vector<string> name, vector<int> num, vector<int> line);
void reset();
bool SPFA(map<Station*, W>& dist, int num, int line, string name);
void initVisit();

using namespace std;
extern Station* stations[9];
extern int stationNum[9];

void initVisit()
{
	for (int i = 0; i < 9; i++)
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

void readPlaceFile(string name,vector<string> &vectorStr)
{
	ifstream txtFile(name+".txt");
	string str;
	while (getline(txtFile,str))
		vectorStr.push_back(str);
}

void tokenPlace(string str,string &name,W &weight,double &alt,double &lat){
	stringstream ss(str);
	string a[4];
	ss >> a[0] >> a[1] >> a[2] >> a[3];
	name =a[0];
	weight=static_cast<W>(stoi(a[1]));
	alt = stod(a[2]) * 10000;
	lat = stod(a[3]) * 10000;
}

void setPlace(){
	string txtName = "한상민전송용/좌표_1호선";
	for(int i=0;i<9;i++,txtName[18]++){
		
		vector<string> vectorStr;
		readPlaceFile(txtName,vectorStr);
		Station * tmp = stations[i];
		for(int j=0;j<vectorStr.size();j++){
			string name ;
			double alt,lat;
			W weight;
			tokenPlace(vectorStr[j],name,weight,alt,lat);
			if(name==tmp->name){
				tmp->lat=lat;
				tmp->alt=alt;
				tmp->visit = 1;
				goNext(tmp);
			}
			else{
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

void tokenName(string str, string& name, W& weight, string& Nname) {
	stringstream ss(str);
	string a[4];
	ss >> a[0] >> a[1] >> a[2] >> a[3];
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	Nname = a[3];
}

void setWeight() {
	string txtName = "한상민전송용/가중치_1호선";
	for (int i = 0; i < 9; i++, txtName[20]++)
	{
		vector<string> vectorStr;
		readPlaceFile(txtName, vectorStr);
		Station* tmp = stations[i];
		for (int j = 0; j < vectorStr.size(); j++) {
			string name, Name;
			W weight;
			tokenName(vectorStr[j], name, weight, Name);
			
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
							if(!flag)
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
				cout << name + " "+ Name << "is " << i + 1 << " not station";
				exit(1);
			}
			visitClear();
		}
	}
}

int main()
{
	makeAllLine();
	setPlace();
	setWeight();
	initVisit();
	//vector<string>name;
	//vector<int> line, num;
	//int i;
	//cout << "input :";
	//cin >> i;

	//for (int k = 0; k < i; k++)
	//{
	//	int _num, _line; string _name;
	//	cout << "사람수 호선 역이름 : ";
	//	cin >> _num >> _line >> _name;
	//	name.push_back(_name);
	//	line.push_back(_line);
	//	num.push_back(_num);
	//}

	//MiddleSPFA(name, num, line);
	//DijkstraMiddle(name, num, line);
	searchMiddle();
	/*for (int i = 0; i < 9; i++)
	{
		Station* tmp = stations[i];
		for (int j = 0; j < stationNum[i]; j++)
		{
			Station* Tmp = tmp;
			goNext(Tmp);
			for (int k = 0; k < tmp->ptr.size(); k++)
				if (tmp->ptr[k]->next == Tmp)
				{
					cout << tmp->name + " " << tmp->ptr[k]->weight << endl;
					break;
				}
			tmp = Tmp;
		}
		cout << endl;
	}*/

	/*Station* tmp = stations[1];
	while (tmp->name != "홍대입구")
		goNext(tmp);
	Station* Tmp;
	for (int j = 0; j < 5; j++)
	{
		Tmp = tmp;
		goNext(Tmp);
		for (int k = 0; k < tmp->ptr.size(); k++)
			if (tmp->ptr[k]->next == Tmp)
			{
				cout << tmp->name + " " << tmp->ptr[k]->weight << endl;
				break;
			}
		tmp = Tmp;
	}
	cout << tmp->name;*/
	
}