#include "header/fileFunc.h"

void tokenized(string& str, int& num, int& transfer, string& name, W& weight)
{
	string a[4];
	stringstream ss(str);

	ss >> a[0] >> a[1] >> a[2] >> a[3];
	num = stoi(a[0]) - 1;
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	transfer = stoi(a[3]) - 1;
}

void tokenized(string str, int& line, string& name, W& weight, int& flag)
{
	string a[4];
	stringstream ss(str);

	ss >> a[0] >> a[1] >> a[2] >> a[3];
	line = stoi(a[0]);
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	flag = stoi(a[3]);
}

void tokenized(string str, string& name, W& weight, double& alt, double& lat)
{
	stringstream ss(str);
	string a[4];
	ss >> a[0] >> a[1] >> a[2] >> a[3];
	name = a[0];
	weight = static_cast<W>(stoi(a[1]));
	alt = stod(a[2]) * 10000;
	lat = stod(a[3]) * 10000;
}

void tokenized(string str, string& name, W& weight, string& Nname)
{
	stringstream ss(str);
	string a[4];
	ss >> a[0] >> a[1] >> a[2] >> a[3];
	name = a[1];
	weight = static_cast<W>(stoi(a[2]));
	Nname = a[3];
}


void readFile(string name, vector<string>& vectorStr)
{
	ifstream txtFile;
	string str;
	txtFile.open(name);
	if (!txtFile.is_open())
	{
		cout << name + "파일이 없습니다.\n";
		exit(1);
	}
	while (getline(txtFile, str))
		vectorStr.push_back(str);
}

