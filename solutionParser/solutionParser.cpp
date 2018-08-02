//============================================================================
// Name        : solutionParser.cpp
// Author      : Ping
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "solutionParser.h"

int main(int argc, char *argv[]) {
	vector<int> solution;
	char fileName1[80];
	strcpy(fileName1, argv[1]);
	strcat(fileName1, ".probsat");
	cout<< fileName1;
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	fp1.open(fileName1,std::ios::in);
	if(!fp1.is_open()){
		perror("read file1 fails");
		exit(EXIT_FAILURE);
	}
	// strat read
	char head;
	// Get the first v line
	while(true){
		getline(fp1,buff);
		if(buff.empty()){
			continue;
		}
		head =buff.at(0);
		if(head == 'v'){
			char* str = strdup(buff.c_str());
			strtok(str, s);
			char* token = strtok(NULL, s);
			while(token != NULL){
				solution.push_back(atoi(token));
				token = strtok(NULL, s);
			}
		}

		//cout<< buff<<endl;
		if(fp1.eof()) break;
	}
	fp1.close();

	//get solution
	char fileName[80];
	strcpy(fileName, argv[1]);
	strcat(fileName, ".ct");
    outFP.open(fileName,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails");
				exit(EXIT_FAILURE);
	}
	outFP<< "s";
	for(int i =0; i < solution.size(); i++){
		outFP<<' '<< solution[i];
	}
	outFP<<endl;
	cout<< "A";
	fp2.open(argv[1],std::ios::in);
	if(!fp2.is_open()){
		perror("read file2 fails");
		exit(EXIT_FAILURE);
	}
	while(true){
		getline(fp2,buff);
		if(buff.empty()){
			if(fp2.eof()) break;
			continue;
		}

		head =buff.at(0);
		if(head == 's'){
			continue;
		}
		outFP<< buff<<endl;
		if(fp2.eof()) break;
	}
	fp2.close();
	outFP.close();
	return 0;
}

