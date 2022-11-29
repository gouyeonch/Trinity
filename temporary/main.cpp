#include "header/makeSubway.h"
#include <queue>
#include <map>
#include <string>



using namespace std;
extern Station* stations[9];
extern int stationNum[9];

void readPlaceFile(string name,vector<string> &vectorStr)
{
	ifstream txtFile(name+".txt");
	string str;
	while (getline(txtFile,str))
	{
		vectorStr.push_back(str);
	}
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
	string txtName = "txt/가중치1";
	for(int i=0;i<9;i++,txtName[10]++){
		
		vector<string> vectorStr;
		readPlaceFile(txtName,vectorStr);
		Station * tmp = stations[i];
		for(int j=0;j<stationNum[i];j++){
			string name ;
			double alt,lat;
			W weight;
			tokenPlace(vectorStr[i],name,weight,alt,lat);
			if(name==tmp->name){
				Station * p = tmp;
				
				tmp->lat=lat;
				tmp->alt=alt;
				if(j<stationNum[i]-1){
					goNext(p);
					for(int k=tmp->ptr.size()-1;k>=0;k--){
						if(tmp->ptr[k]->next->name==p->name){
							tmp->ptr[k]->weight=weight;
							break;
						}
					}
				}

				
			}
			else{
				cout << name << "is "<< j +1 << "not station" ;
				exit(1);
			}
		}

	}
}

struct comp
{
    bool operator()(pair<Edge*,W>a,pair<Edge*,W>b)
    {
        return a.first->weight>b.first->weight;
    }
};

priority_queue<pair<Edge*,W>,vector<pair<Edge*,W>>,comp> pq;


map<Station*,W> dijkstra(int n,int l,string name){

	Station * temp = stations[l-1];
	
	//노드 찾기
	while(temp->name != name)
	{
		goNext(temp); 
	}

	//초기 연결된 노드들 pq에 Push
	map<Station *,W> map; 
	for(int i=0;i<temp->ptr.size();i++){
		pq.push({temp->ptr[i] , temp->ptr[i]->weight});
		temp->ptr[i]->next->opt=temp->ptr[i]->weight;
		map.insert({temp->ptr[i]->next,temp->ptr[i]->weight});
	}

	map.insert({temp,0}); //시작역은 0

	//dijkstra start
	while(pq.size()){
		temp = pq.top().first->next;
		W distance = pq.top().second;
		pq.pop();

		if(temp->opt<distance)
			continue;

		if(!map.insert({temp,distance}).second){
			if(map[temp]>distance){
				map[temp] = distance;
			}
		}
		
		for(int i=0;i<temp->ptr.size();i++){
			if(temp->ptr[i]->weight+distance < temp->ptr[i]->next->opt){
				pq.push({temp->ptr[i],temp->ptr[i]->weight+distance});
				temp->ptr[i]->next->opt = temp->ptr[i]->weight+distance;
			}
		}
	}

	 for(auto i : map){
	 	i.second*=n;
	  }
	//  cout << map.size()<<endl;
	return map;
}

void reset(){
	for(int i=0;i<9;i++){
		Station * tmp = stations[i];
		tmp ->opt = 987654321;
		for(int j=0;j<stationNum[i];j++){
			goNext(tmp);
			tmp->opt = 987654321;
		}
	}
}

int main()
{
	makeAllLine();

	int total;
	cout << "총 몇개역인지 입력해주세요";
	cin >> total;
	map<Station*,W> map[total];
	for(int i=0;i<total;i++){
		int n , input_line;	//사람수, 몇호선인지
		string station_name; // 역이름
		cout << "사람수 몇호선 역이름";
		cin >> n >> input_line >> station_name ;
		map[i] = dijkstra(n,input_line,station_name);
		reset();
	}

	pair<string,vector<int>> p[450];
	for(int i=0;i<total;i++){
		int j=0;
		for(auto m : map[i]){
			p[j].first=to_string(m.first->line)+m.first->name;
			p[j].second.push_back(m.second);
	 		//cout << p[j].first <<"  " << p[j].second.back() << endl;
			j++;
	 	}
		//cout << map[i].size() << endl;
		
	}

	int min=987654321;
	string res;

	for(int i=0;i<449;i++){
		int max = 0;

		for(int j=0;j<p[i].second.size();j++){
			if(max< p[i].second[j])
				max = p[i].second[j];
		}

		if(min>max){
			min = max;
			res=(p[i].first);
		}
	}
	
	cout << res;

	 
	//  for(int i=0;i<9;i++){
	// 	cout << a[i] <<endl;
	// 	cout <<stationNum[i] << endl;
	//  }

	//  temp = stations[1];

	//  for(int i=0;i<52;i++){
	// 	cout << i << temp->name;
	// 	goNext(temp);
	//  }
}

