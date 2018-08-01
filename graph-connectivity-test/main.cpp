/*
 * main.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: ping
 */
#include "main.h"

int main(int argc, char *argv[])
{
	fp1.open(argv[1],std::ios::in);
	if(!fp1.is_open()){
		perror("read file1 fails");
		exit(EXIT_FAILURE);
	}
	fp2.open(argv[2],std::ios::in);
	if(!fp2.is_open()){
		perror("read file2 fails");
		exit(EXIT_FAILURE);
	}
	alpha1 = atof(argv[3]);
	alpha2 = atof(argv[4]);
	alpha3 = atof(argv[5]);
	outFP.open((string(argv[1])+ l + string(argv[2])).c_str(),std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails");
				exit(EXIT_FAILURE);
	}
	combineFile();
	outFP.close();
	fp1.close();
	fp2.close();
}
// append
void combineFile(){
	readFile_1();
	readFile_2();
	readIntersection();

	outFP<<endl<<"p "<< numV-2 << ' '<< numC;


}
void readFile_1(){
	// strat read
	char head;
	getline(fp1,buff);
	// Get the p line
	while(!fp1.eof()){
		//cout<<buff<<endl;
		//todo:parseLine
		if(buff.empty()) break;
		head =buff.at(0);
		if(head == 'p'){
			char* str = strdup(buff.c_str());
	    	strtok(str, s);
			strtok(NULL, s);
			numV1 = atoi(strtok(NULL, s))+1;
			is1 = numV1* alpha1;
			numC1 = atoi(strtok(NULL, s));
			assign1= (bool*)malloc(sizeof(bool) * numV1);
			for(int i =0; i < numV1; i++){
				assign1[i] = 0;
			}
			break;
		}
	  getline(fp1,buff);
	}

	while(!fp1.eof()){
			if(buff.empty()) break;
			head =buff.at(0);
			if(head == 's'){
				setAssignment(buff,assign1);
				for(int i =0; i < numV1; i++){
					cout<< assign1[i];
				}
				cout<<endl;
				break;
			}
			getline(fp1,buff);
	}
	getClauses(1);
}

void readFile_2(){
	// strat read
	char head;
	getline(fp2,buff);
	// Get the p line
	while(!fp2.eof()){
		//cout<<buff<<endl;
		//todo:parseLine
		if(buff.empty()) break;
		head =buff.at(0);
		if(head == 'p'){
			char* str = strdup(buff.c_str());
	    	strtok(str, s);
			strtok(NULL, s);
			numV2 = atoi(strtok(NULL, s))+1;
			is2 = numV2* alpha2;
			numC2 = atoi(strtok(NULL, s));
			numV = numV1+numV2;
			numC = numC1+numC2;
			ics = alpha3* numC;
			//cout<< "is1 "<< is1 << " is2 "<< is2 << " ics "<< ics<<endl;
			assign2= (bool*)malloc(sizeof(bool) * numV2);
			for(int i =0; i < numV2; i++){
				assign2[i] = 0;
			}
			break;
		}
	  getline(fp2,buff);
	}
	while(!fp2.eof()){
			if(buff.empty()) break;
			head =buff.at(0);
			if(head == 's'){
				setAssignment(buff,assign2);
				for(int i =0; i < numV1; i++){
					cout<< assign2[i];
				}
				cout<<endl;
				break;
			}
			getline(fp2,buff);
	}
	getClauses(2);
}

void setAssignment(string buff, bool* assign){
	char* str = strdup(buff.c_str());
	char* token = strtok(str, s);
	 token = strtok(NULL, s);
	 while(token != NULL){
		 assign[atoi(token)] = 1;
		 token = strtok(NULL, s);
	 }
};

void readIntersection(){
	while(inter1.size() != is1){
		inter1.insert(rand()% is1);
	}
	while(inter2.size() != is2){
		inter2.insert(rand()% is2);
	}
}

void getClauses(int i){
	if(i==1){
		int line = 0;
		while(!fp1.eof() && line < numC1){
			getline(fp1,buff);
			outFP<<buff<< endl;
		}
	}
	else{
		// Get the clause
		int line = 0;
		while(!fp2.eof() && line < numC2){
			getline(fp2,buff);
			if(buff.empty()) break;
			char* str = strdup(buff.c_str());
			int lit;
			bool flag;
			char* token = strtok(str, s);
			 while(token != NULL){
				flag = false;
				if(*token== '-'){
					lit = -atoi(token);
					outFP<<-(lit+numV1) << ' ';
					token = strtok(NULL, s);
					continue;
				}
				if(*token == '0'){
					outFP<<'0'<<endl;
					flag = true;
					line++;
					break;
				}
				if(flag) break;
				lit = atoi(token);
				outFP<<lit+numV1 << ' ';
				token = strtok(NULL, s);
			 }
		}

	}
}




