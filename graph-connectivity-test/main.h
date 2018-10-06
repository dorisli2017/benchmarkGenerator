/*
 * main.h
 *
 *  Created on: Aug 1, 2018
 *      Author: ping
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
#include <string.h>
#include <vector>
#include <iostream>
#include <set>
#include <assert.h>
#include <iterator>
#include <algorithm>
using namespace std;
string fileName;
int seed;
int numFs;
string l = "-";
int numCs;
vector<int> numV;
vector<int> offsetV;
vector<int> offsetC;
vector<int> numC;
float alpha3;// percentage cut clauses in all clauses
float timeLimit;// time limit to get the intersection clauses in seconds.
ofstream outFP;
string buff;
vector<bool> assign;
set<int> inter;
set<int> realinter;
int is1;
int is2;
int ics;
int numI = 3;
const char s[2] = " ";
void setAssignment(string buff);
void parseLine(string line,int indexC,int index);
void setIntersection();
void readIntersection();
void testLine(string line);
void test();
vector<vector<int>> clauses;
vector<int> clauseT;
void printVector(vector<int>& vec, int off);
void printClauses();





#endif /* MAIN_H_ */
