/*
 * main.cpp
 *
 *  Created on: Aug 1, 2018
 *      Author: ping

ifs.push_back(&f);
 */
#include "main.h"
int main(int argc, char *argv[])
{
	fileName = "result";
	outFP.open(fileName,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	seed = atof(argv[argc-1]);
	srand (seed);
	int numFs = atoi(argv[1]);
	alpha3 = atof(argv[argc-2]);
	assert(argc == (numFs +4));
	for(int i = 0; i < numFs; i++){
		numV.push_back(0);
		numC.push_back(0);
		offsetV.push_back(0);
		offsetC.push_back(0);
	}
	offsetV.push_back(0);
	offsetC.push_back(0);
	offsetC.push_back(0);
	assign.push_back(false);
	for(int i = 0; i < numFs; i++){
		ifstream fp(argv[i+2], std::ios::in);
		if(!(fp.is_open())){
			perror("read file1 fails");
			exit(EXIT_FAILURE);
		}
		char head;
		getline(fp,buff);
		while(!(fp.eof())){
					if(buff.empty()) break;
					head =buff.at(0);
					if(head == 's'){
						setAssignment(buff);
						break;
					}
					getline(fp,buff);
		}
		while(!(fp.eof())){
				//cout<<buff<<endl;
				//todo:parseLine
				if(buff.empty()) break;
				head =buff.at(0);
				if(head == 'p'){
					char* str = strdup(buff.c_str());
			    	strtok(str, s);
					strtok(NULL, s);
					numV[i] = atoi(strtok(NULL, s));
					numC[i] = atoi(strtok(NULL, s));
					for(int j = i+1; j < numFs+1; j++ ){
						offsetV[j]+= numV[i];
						offsetC[j]+= numC[i];
					}
					offsetC[numFs+1]+= numC[i];
					break;
				}
				getline(fp,buff);
			}
			int line = 0;
			while(!(fp.eof()) && line < numC[i]){
				getline(fp,buff);
				if(buff.empty()) break;
				parseLine(buff, line, i);
				line++;
			}
		fp.close();
	}
	//add intersection
	int numVs = offsetV[numFs];
	int criIndex;
	int criV;
	int temp;
	int inter = alpha3* offsetC[numFs];
	for(int i = 0; i < inter; i++){
		clauseT.clear();
		for(int i = 0; i < 5; i++){
			clauseT.push_back(rand()%numVs+1);
		}
		criIndex = rand()%5;
		for(int j =0 ; j <criIndex; j++){
			temp = clauseT[j];
			if(rand()%2 == 0) clauseT[j] = -temp;
		}
		criV = clauseT[criIndex];
		if(assign[criV]== false) clauseT[criIndex] = -criV;
		for(int j =criIndex+1 ; j <5; j++){
			temp = clauseT[j];
			if(rand()%2 == 0) clauseT[j] = -temp;
		}
		printVector(clauseT, 0);
	}
	outFP.close();
	test();
	ifstream fp;
	fp.open(fileName,std::ios::in);
	string outfile = "final";
	outFP.open(outfile,std:: ios::out);
	outFP<< "c"<< " ";
	for(int i = 1; i < assign.size(); i++){
		if(assign[i])  outFP<< i<< " ";
		else outFP<< -i<< " ";
	}
	outFP<<endl;
	outFP<< "c"<< " "<<numFs<< " ";
	outFP<< offsetV[numFs]<< " ";
	for(int i = 0; i < numV.size(); i++){
		outFP<< numV[i]<<" ";
	}
	outFP<< offsetC[numFs]+inter<<" ";
	for(int i = 0; i < numC.size(); i++){
		outFP<< numC[i]<<" ";
	}
	outFP<<endl;
	outFP<< "p "<< offsetV[numFs]<< " "<<  offsetC[numFs]+inter<< endl;
	while(!(fp.eof())){
		getline(fp,buff);
		outFP<< buff<<endl;
	}
	outFP.close();
/*	string a = string(argv[2]);
	a.erase (0,32);
	fileName = ("../../combine/"+a+l + string(argv[1])+ l + string(argv[argc-1])).c_str();
	//

*/
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
   	//fileName.erase(0,14);
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
void parseLine(string line,int indexC,int index){
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
			printVector(clauseT, offsetV[index]);
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

