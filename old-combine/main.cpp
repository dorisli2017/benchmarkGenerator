/*
 * main.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: ping
 */
#include "main.h"

int main(int argc, char *argv[])
{
	seed = atof(argv[6]);
	srand (seed);
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
	timeLimit = atof(argv[7]);
	string a = string(argv[1]);
	a.erase (0,32);
	string b = string(argv[2]);
	b.erase (0,32);
	fileName = ("../../combine/"+a+ l + b +l + string(argv[3])+
			l + string(argv[4])+l + string(argv[5])+l + string(argv[6])).c_str();
	outFP.open(fileName,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	combineFile();
	outFP.close();
	fp1.close();
	fp2.close();
	test();
}
// append
void combineFile(){
	readFile_1();
	readFile_2();
}
void readFile_1(){
	// strat read
	char head;
	getline(fp1,buff);
	// Get the s line
	assign.push_back(false);
	while(!fp1.eof()){
			if(buff.empty()) break;
			head =buff.at(0);
			if(head == 's'){
				setAssignment(buff);
				break;
			}
			getline(fp1,buff);
	}
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
			break;
		}
	  getline(fp1,buff);
	}
}

void readFile_2(){
	// strat read
	char head;
	getline(fp2,buff);
	// Get the p line
	while(!fp2.eof()){
			if(buff.empty()) break;
			head =buff.at(0);
			if(head == 's'){
				setAssignment(buff);
				break;
			}
			getline(fp2,buff);
	}
	while(!fp2.eof()){
		//cout<<buff<<endl;
		//todo:parseLine
		if(buff.empty()) break;
		head =buff.at(0);
		if(head == 'p'){
			char* str = strdup(buff.c_str());
	    	strtok(str, s);
			strtok(NULL, s);
			numV2 = atoi(strtok(NULL, s));
			is2 = numV2* alpha2;
			numC2 = atoi(strtok(NULL, s));
			numVs = numV1+numV2;
			numCs = numC1+numC2;
			ics = alpha3* numCs;
			setIntersection();
			break;
		}
	  getline(fp2,buff);
	}
	getClauses(1);
	getClauses(2);
	readIntersection();
	outFP<<"p "<< numVs-1 << ' '<<numV1-1<< ' ' << numCs<< ' '<< numC1<< ' '<< numC1+ics<<endl;
	outFP<<'c';
	 for (int const& iv : realinter)
	    {
	        outFP <<' '<<iv;
	    }
	 outFP<< endl;
	printClauses();
}

void setAssignment(string buff){
	char* str = strdup(buff.c_str());
	char* token = strtok(str, s);
	 token = strtok(NULL, s);
	 while(token != NULL){
		 if(*token== '-'){
			 assign.push_back(false);
		 }
		 else assign.push_back(true);
		 token = strtok(NULL, s);
	 }
};

void setIntersection(){
	while(inter.size() != is1){
		int c = rand()% numV1;
		if(c== 0) continue;
		inter.push_back(c);
	}
	int is = is1+is2;
	while(inter.size() != is){
		inter.push_back((rand()% numV2)+numV1);
	}
}
void readIntersection(){
	int is = is1+is2;
	clauseT.clear();
	 int i = 0;
	 while(i < ics){
		 clauseT.clear;
		 int crit = rand()%numI;
		 while(clauseT.size() < numI){
			if(rand%2 == 0) clauseT.push_back(inter[rand()%is]);
			else  clauseT.push_back(-inter[rand()%is]);
		 }
		 if(clauseT[crit] > 0 && assign[clauseT[crit]]<0) clauseT[crit]= -clauseT[crit];
		 if(clauseT[crit] < 0 && assign[clauseT[crit]]>0) clauseT[crit]= -clauseT[crit];
		 i++;
	 }
}
void parseLine(string line,int indexC){
	char* str = strdup(line.c_str());
    const char s[2] = " ";
    int lit;
    int size;
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
			clauses.push_back(clauseT);
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
void getClauses(int i){
	if(i==1){
		int line = 0;
		while(!fp1.eof() && line < numC1){
			getline(fp1,buff);
			if(buff.empty()) break;
			parseLine(buff, line);
			line++;
		}
	}
	else{
		// Get the clause
		int line = 0;
		while(!fp2.eof() && line < numC2){
			getline(fp2,buff);
			if(buff.empty()) break;
			parseLine(buff, line+numC1+ics);
			line++;
		}
	}
}

void test(){
	ifstream fp;
	int i = 0;
	fp.open(fileName,std::ios::in);
	if(!fp.is_open()){
		perror("read file fails");
		exit(EXIT_FAILURE);
	}
	string buff;
	char head;
   	getline(fp,buff);
   	while(!fp.eof()){
   		if(buff.empty()) break;
		head =buff.at(0);
		if(head == 'c'){
			break;
		}
	  getline(fp,buff);
	}
   	while(!fp.eof()){
		getline(fp,buff);
		if(buff.empty()) break;
   		i++;
		testLine(buff);
   	}
   	assert(i == numCs);
   	fileName.erase(0,14);
   	cout<<fileName <<" tested" << endl;
   	fp.close();
}

void testLine(string line){
	char* str = strdup(line.c_str());
    const char s[2] = " ";
    int lit;
    int numT=0;
    char* token = strtok(str, s);
    while(token != NULL){
		if(*token== '-'){
			lit = atoi(token);
			if(assign[-lit] == false) numT++;
			token = strtok(NULL, s);
			continue;
		}
		if(*token == '0'){
			if(numT == 0){
				cout<<line<<endl;
				perror("TEST FAILURE");
				exit(EXIT_FAILURE);
			}
		    return;
		}
		lit = atoi(token);
		if(assign[lit] == true) numT++;
		token = strtok(NULL, s);
    }
    cout<< line;
	perror("a clause line does not terminates");
	exit(EXIT_FAILURE);
}
void printClauses(){
	assert(clauses.size() == numCs);
	for(int i =0; i < numC1+ ics; i++){
		printVector(clauses[i],0);

	}
	for(int i =ics+numC1; i < numCs; i++){
		printVector(clauses[i],numV1-1);

	}

}
void printVector(vector<int>& vec, int off){
	for (std::vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i){
		if((*i) > 0){
			outFP << (*i)+off << ' ';
			continue;
		}
		if((*i) < 0){
			outFP << (*i)-off << ' ';
			continue;
		}
		assert(false);
	}
	outFP<<'0'<< endl;
}



