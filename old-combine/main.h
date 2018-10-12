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
ifstream fp3;// File 3 with assignment
ifstream fp4;// File 4 with assignment
ifstream fp5;// File 5 with assignment
ifstream fp6;// File 6 with assignment
ifstream fp7;// File 7 with assignment
ifstream fp8;// File 8 with assignment
string l = "-";
int numC1;
int numV1;
int numC2;
int numV2;
int numC3;
int numV3;
int numC4;
int numV4;
int numC5;
int numV5;
int numC6;
int numV6;
int numC7;
int numV7;
int numC8;
int numV8;
int numCs;
int numVs;
float alpha1;
float alpha2;
float alpha3;
float alpha4;
float alpha5;
float alpha6;
float alpha7;
float alpha8;
float alpha;// percentage cut clauses in all clauses
ofstream outFP;
string buff;
vector<bool> assign;
vector<int> inter;
set<int> realinter;
int is1;
int is2;
int is3;
int is4;
int is5;
int is6;
int is7;
int is8;
int ics;
int seed = 1000;
int numI = 3;
const char s[2] = " ";
void readFile();
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
