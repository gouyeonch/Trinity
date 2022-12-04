#include "header/Dijkstra.h"

extern Station* stations[MAX];
extern int stationNum[MAX];

priority_queue<pair<Edge*,W>,vector<pair<Edge*,W>>,comp> pq;

map<Station*, W> dijkstra(int n, int l, string name) {

	Station* temp;
	
	temp = findStat(name, l);

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

void MiddleDijkstra(vector<string>name,vector<int>num,vector<int>line){

    int total=name.size();
    map<Station*,W> *m = new map<Station*,W>[total];
	for(int i=0;i<total;i++){
		int n = num[i];
		int input_line = line[i];	
		string station_name = name[i]; 
		m[i] = dijkstra(n,input_line,station_name);
		reset();
	}

	cout << "Dijkstra 알고리즘\n";
	compareStation(m, total);
}