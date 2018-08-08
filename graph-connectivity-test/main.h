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
ifstream fp1;// File 1 with assignment
ifstream fp2;// File 2 with assignment
string l = "-";
int numC1;
int numV1;
int numC2;
int numV2;
int numCs;
int numVs;
float alpha1;// percentage of cut variables of P1 variables.
float alpha2;// percentage of cut variables of P2 variables.
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
int seed = 1000;
int numI = 3;
const char s[2] = " ";
void readFile_1();
void readFile_2();
void combineFile();
void setAssignment(string buff);
void getClauses(int i);
void parseLine(string line,int indexC);
void setIntersection();
void readIntersection();
void testLine(string line);
void test();
vector<vector<int>> clauses;
vector<int> clauseT;
void printVector(vector<int>& vec, int off);
void printClauses();





#endif /* MAIN_H_ */
