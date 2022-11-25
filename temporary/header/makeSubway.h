#pragma once
#include "dataStruct.h"
#include "makeLine.h"
#include "moveStation.h"

void transferToken(string& str, int& num, string& name, W& weight, int& transfer);
void linkTransfer(vector<string>& vectorStr);
void readFile(string name, vector<string>& vectorStr);
void makeAllLine();