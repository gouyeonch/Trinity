#pragma once
#include "dataStruct.h"
#include <sstream>
#include <fstream>

void tokenized(string str, int& line, string& name, W& weight, int& flag);
void tokenized(string& str, int& num, int& transfer, string& name, W& weight);
void tokenized(string str, string& name, W& weight, double& alt, double& lat);
void tokenized(string str, string& name, W& weight, string& Nname);
void readFile(string name, vector<string>& vectorStr);