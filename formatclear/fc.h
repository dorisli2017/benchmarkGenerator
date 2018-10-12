/*
 * fc.h
 *
 *  Created on: Oct 12, 2018
 *      Author: ping
 */

#ifndef FC_H_
#define FC_H_
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
vector<int> clauseT;
vector<int> backup;
char* fileName;
string outfile;
ofstream outFP;
void readFile(const char* fileName);
void parseLine(string line);
void printVector(vector<int>& vec);




#endif /* FC_H_ */
