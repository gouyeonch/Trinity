#include "header/makeSubway.h"

extern Station* stations[9];
int stationNum[9];

void readFile(string name, vector<string>& vectorStr)
{
	ifstream txtFile;
	string str;
	txtFile.open(name);
	if (!txtFile.is_open())
	{
		cout << name + "������ �����ϴ�.\n";
		exit(1);
	}
	while (getline(txtFile, str))
		vectorStr.push_back(str);
}

void makeAllLine()
{
	vector<string> vectorStr;
	string name = "txt/����ö1.txt";
	for (int i = 0; i < 9; i++, name[10]++)
	{
		readFile(name, vectorStr);
		makeLine(stations[i], vectorStr);
		stationNum[i] = vectorStr.size();
		vectorStr.clear();
	}
	name = "txt/ȯ�¿�.txt";
	readFile(name, vectorStr);
	linkTransfer(vectorStr);
}

void linkTransfer(vector<string>& vectorStr)
{
	int num, transfer;
	string name;
	W weight;
	Station *tmp1, *tmp2;

	for (int i = 0; i < vectorStr.size(); i++)
	{
		transferToken(vectorStr[i], num, name, weight, transfer);
		tmp1 = stations[num];
		tmp2 = stations[transfer];
		for (int j = 0; tmp1->name != name; j++)
		{
			if (j == stationNum[num])
			{
				cout << name + "�� " << num + 1 << "ȣ���� �ִ� ȯ�¿��� �ƴմϴ�.\n";
				exit(1);
			}
			goNext(tmp1);
		}
		visitClear();
		for (int k = 0; tmp2->name != name; k++)
		{
			if (k == stationNum[transfer])
			{
				cout << name + "�� " << transfer + 1 << "ȣ���� �ִ� ȯ�¿��� �ƴմϴ�.\n";
				exit(1);
			}
			goNext(tmp2);
		}
		visitClear();
		lastStation(tmp2, tmp1, weight);
		tmp1->transfer = 1;
	}
}

void transferToken(string& str, int& num, string& name, W& weight, int& transfer)
{
	string a[4];
	stringstream ss(str);

	ss >> a[0] >> a[1] >> a[2] >> a[3];
	num = stoi(a[0]) - 1;
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	transfer = stoi(a[3]) - 1;
}