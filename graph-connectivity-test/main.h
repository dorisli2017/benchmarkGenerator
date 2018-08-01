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
using namespace std;
ifstream fp1;// File 1 with assignment
ifstream fp2;// File 2 with assignment
string l = "-";
int numC1;
int numV1;
int numC2;
int numV2;
int numC;
int numV;
float alpha1;// percentage of cut variables of P1 variables.
float alpha2;// percentage of cut variables of P2 variables.
float alpha3;// percentage cut clauses in all clauses
ofstream outFP;
string buff;
bool* assign1;
set<int> inter1;
set<int> inter2;
int is1;
int is2;
int ics;
bool* assign2;
const char s[2] = " ";
void readFile_1();
void readFile_2();
void combineFile();
void setAssignment(string buff, bool* assign);
void getClauses(int i);
void readIntersection();





#endif /* MAIN_H_ */
