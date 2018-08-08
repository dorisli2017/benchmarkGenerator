//============================================================================
// Name        : commandConverter.cpp
// Author      : Ping
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
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
ofstream outFP;
ifstream fp1;// File 1 with assignment
string buff;
void readFile_1();
using namespace std;
const char s[2] = " ";

int main(int argc, char *argv[]) {
	fp1.open(argv[1],std::ios::in);
	if(!fp1.is_open()){
		perror("read file1 fails");
		exit(EXIT_FAILURE);
	}
	outFP.open((string(argv[1])+".cnfS").c_str(),std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	readFile_1();
	return 0;
}

void readFile_1(){
	char head;
	getline(fp1,buff);
	while(!fp1.eof()){
			if(buff.empty()) break;
			head =buff.at(0);
			if(head == 'p'){
				char* str = strdup(buff.c_str());
				strtok(str, s);
				int numVs=atoi(strtok(NULL, s));
				strtok(NULL, s);
				int numCs=atoi(strtok(NULL, s));
				outFP<<"p cnf "<<numVs<<" "<< numCs<< endl;
				break;
			}
			getline(fp1,buff);
	}
	while(!fp1.eof()){
	  getline(fp1,buff);
	  if(buff.empty()) break;
	  head =buff.at(0);
		if(head == 'c'){
			continue;
		}
	  outFP<< buff<<endl;
	}
}
