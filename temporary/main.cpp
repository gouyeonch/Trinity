#include "header/makeSubway.h"
#include "header/Astar.h"
#include <queue>
#include <map>
#include <string>


extern Station* stations[9];
extern int stationNum[9];

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
	alt = stod(a[2]);
	lat = stod(a[3]);
}

void setPlace(){
	string txtName = "ÇÑ»ó¹ÎÀü¼Û¿ë/ÁÂÇ¥_1È£¼±";
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

int main()
{
	makeAllLine();
	setPlace();
	
	//searchMiddle();

	return 0;
}
