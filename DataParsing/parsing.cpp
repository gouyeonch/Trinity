#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) 
{
    string str, pos;
    ifstream readName, read;
    ofstream writeInf;
    int npos, diffTime;

    readName.open("StatData.txt");
    read.open("posit.txt");
    writeInf.open("StatData_221128.txt", ios_base::out);

    if(readName.is_open() && writeInf.is_open())
    {
        //호선 받아오기
        

        while(!readName.eof())
        {
            getline(readName, str);
            getline(read, pos);
            npos = str.substr(str.find(' ',3)+1).find(' ');
            str.erase(str.find(' ',3) + npos + 1);
            str = str.substr(str.find(' ')+1);
            pos = pos.substr(pos.find('1'));
            writeInf << str << '\t' << pos << '\n';
        }
    }

    readName.close();
    writeInf.close();

    return 0;
}