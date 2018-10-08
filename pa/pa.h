#ifndef MAIN_H_
#define MAIN_H_

/* includes*/

#include <iostream>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <fstream>
#include <string.h>
#include <vector>
#include <assert.h>
#include <math.h>
#include <vector>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <functional>
using namespace std;
string l = "-";
char* fileName;
string outFile;
vector<vector<vector<int>>> clauses;
vector<int> numC;
vector<int> numV;
int step;
vector<int> clauseT;
int pa;
ofstream outFP;
void printVector(vector<int>& vec);
int numCs;
int numVs;
void memAllocate(string buff);
void readFile(const char* fileName);
void parseLine(string line);
void printClauses();










#endif /* MAIN_H_ */
