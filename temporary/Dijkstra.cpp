#include "header/Dijkstra.h"
using namespace std;
extern Station* stations[9];
extern int stationNum[9];


struct comp
{
    bool operator()(pair<Edge*,W>a,pair<Edge*,W>b)
    {
        return a.first->weight>b.first->weight;
    }
};

priority_queue<pair<Edge*,W>,vector<pair<Edge*,W>>,comp> pq;

map<Station*, W> dijkstra(int n, int l, string name) {

	Station* temp = stations[l - 1];

	while (temp->name != name)
	{
		goNext(temp);
	}

	map<Station*, W> m;
	for (int i = 0; i < temp->ptr.size(); i++) {
		pq.push({ temp->ptr[i] , temp->ptr[i]->weight });
		temp->ptr[i]->next->opt = temp->ptr[i]->weight;
		m.insert({ temp->ptr[i]->next,temp->ptr[i]->weight });
	}

	m.insert({ temp,0 });
	//dijkstra start
	while (pq.size()) {

		temp = pq.top().first->next;
		W distance = pq.top().second;
		pq.pop();

		if (temp->opt < distance)
			continue;

		if (!m.insert({ temp,distance }).second) {
			if (m[temp] > distance) {
				m[temp] = distance;
			}
		}

		for (int i = 0; i < temp->ptr.size(); i++) {
			if (temp->ptr[i]->weight + distance < temp->ptr[i]->next->opt) {
				pq.push({ temp->ptr[i],temp->ptr[i]->weight + distance });
				temp->ptr[i]->next->opt = temp->ptr[i]->weight + distance;
			}
		}
	}

	if (n != 1) {
		for (auto it = m.begin(); it != m.end(); it++) {
			it->second *= n;
		}
	}

	return m;
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



void DijkstraMiddle(vector<string>name,vector<int>num,vector<int>line){

    int total=name.size();
    map<Station*,W> *m = new map<Station*,W>[total];
	for(int i=0;i<total;i++){
		int n = num[i];
		int input_line = line[i];	
		string station_name = name[i]; 
		m[i] = dijkstra(n,input_line,station_name);
		reset();
	}

	pair<string,vector<int>> p[449];
	for(int i=0;i<total;i++){
		int j=0;
		for(auto m : m[i]){
			p[j].first=to_string(m.first->line)+m.first->name;
			p[j].second.push_back(m.second);
            //cout << p[j].first << p[j].second.back() << endl;
			j++;
	 	}
	}

	int min=987654321;
	string res;

	for(int i=0;i<449;i++){
		int max = 0;

		for(int j=0;j<p[i].second.size();j++){
			if(max< p[i].second[j])
				max = p[i].second[j];
		}

		//TESTING CODE
		/*if (p[i].first == "1³ë·®Áø") {
			for (int j = 0; j < p[i].second.size(); j++) {
				cout << p[i].second[j] << endl;
			}
		}*/
		//TESTING CODE END

		if(min>max){
			min = max;
			res=(p[i].first);
		}
		
	}
	
	cout << res << "max : " << min;
}