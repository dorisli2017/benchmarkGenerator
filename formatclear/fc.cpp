/*
 * fp.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: ping
 *      for format cleanser (v v)-> v and (v -v)->v
 */

#include "fc.h"
int main(int argc, char *argv[]){
	fileName = argv[1];
	outfile = string(fileName)+".cnfC";
	outFP.open(outfile,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	readFile(fileName);
}

void readFile(const char* fileName){
	//cout<< "in readFile"<<endl;
	ifstream fp;
	//fp.open("Debug/instance.cnf",std::ios::in);
	fp.open(fileName,std::ios::in);
	if(!fp.is_open()){
		perror("read file fails");
		exit(EXIT_FAILURE);
	}
	string buff;
	char head;
   	getline(fp,buff);
   	// Get the p line
   	while(!fp.eof()){
		//cout<<buff<<endl;
		//todo:parseLine
   		if(buff.empty()) break;
		head =buff.at(0);
		if(head == 'p'){
			outFP<< buff<<endl;
			break;
		}
		outFP<< buff<<endl;
	  getline(fp,buff);
	}

   	while(!fp.eof()){
		getline(fp,buff);
		if(buff.empty()) break;
		parseLine(buff);
   	}
};

void parseLine(string line){
	char* str = strdup(line.c_str());
    const char s[2] = " ";
    int lit;
    int size = 0;
    char* token = strtok(str, s);
    while(token != NULL){
		if(*token== '-'){
			lit = atoi(token);
			clauseT.push_back(lit);
			token = strtok(NULL, s);
			size++;
			continue;
		}
		if(*token == '0'){
			printVector(clauseT);
			clauseT.clear();
		    return;
		}
		lit = atoi(token);
		clauseT.push_back(lit);
	    size++;
		token = strtok(NULL, s);
    }
	perror("a clause line does not terminates");
	exit(EXIT_FAILURE);
}
void printVector(vector<int>& vec){
	backup.clear();
	int vT;
	bool in;
	for (std::vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i){
		in = false;
		vT = abs(*i);
		for(int i = 0; i < backup.size(); i++){
			if(backup[i] == vT){
				in = true;
				break;
			}
		}
		if(!in){
			backup.push_back(vT);
			outFP << *i << ' ';
		}
	}
	outFP <<'0'<< endl;
}

