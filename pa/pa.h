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

vector<vector<vector<int>>> clauses;
vector<int> clauseT = {1,2,3};
int pa = 2;
void printVector(vector<int>& vec);
int numCs;
int numVs;
void memAllocate(string buff);
void readFile(const char* fileName);










#endif /* MAIN_H_ */
