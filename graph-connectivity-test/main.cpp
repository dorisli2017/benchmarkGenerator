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
	string a = string(argv[1]);
	a.erase (0,23);
	string b = string(argv[2]);
	b.erase (0,23);
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
			numV = numV1+numV2;
			numC = numC1+numC2;
			ics = alpha3* numC;
			setIntersection();
			break;
		}
	  getline(fp2,buff);
	}
	/*outFP<< 's';
	for(int i =1; i < numV; i++){
		if(assign[i]) outFP <<' '<< i;
		else outFP <<' '<< -i;
	}*/

	getClauses(1);
	readIntersection();
	getClauses(2);
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
		inter.insert(c);
	}
	int is = is1+is2;
	while(inter.size() != is){
		inter.insert((rand()% numV2)+numV1);
	}
	outFP<<"p "<< numV-1 << ' '<<numV1-1<< ' ' << numC+ics<< ' '<< numC1<< ' '<< numC1+ics<<endl;
	outFP<<'i';
	 for (int const& iv : inter)
	    {
	        outFP <<' '<<iv;
	    }
	 outFP<< endl;
}
void readIntersection(){
	int is = is1+is2;
	 set<int> m;
	 vector<bool> sign;
	 int nump = 0;
	 int i = 0;
	 int change = 0;
	 int last = 0;
	 set<int>::iterator it;
	 while(i < ics){
		 while(m.size() < numI){
			it = inter.begin();
			advance(it,rand()%is);
			int c = *it;
			if(last == 0){
				if(c >= numV1) last = 2;
				else last = 1;
			}
			if(c >= numV1 && last == 1){
				last = 2;
				change++;
			}
			if(c < numV1 && last == 2){
				last = 1;
				change++;
			}
			m.insert(c);
		 }
		for (int const& v :m)
		{
			bool c = (rand()%2 == 1);
			sign.push_back(c);
			if(c == assign[v]) nump++;
		}
		 if(nump > 0 && change > 0){
			 assert(*m.rbegin()>= numV1);
			 assert(*m.begin()< numV1);
			 set<int>::iterator itm = m.begin();
			 for(int j =0; j < numI; j++){
				bool si = sign[j];
				if(si) outFP<< *itm<< ' ';
				else  outFP<< -*itm<< ' ';
				advance(itm,1);
			 }
			 outFP<<"0"<<endl;
			 i++;
		 }
		 sign.clear();
		 nump = 0;
		 change = 0;
		 last = 0;
		 m.clear();
	 }
	 assert(i == ics);
}

void getClauses(int i){
	if(i==1){
		int line = 0;
		while(!fp1.eof() && line < numC1){
			getline(fp1,buff);
			if(buff.empty()) break;
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
					outFP<<-(lit+numV1-1) << ' ';
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
				outFP<<lit+numV1-1 << ' ';
				token = strtok(NULL, s);
			 }
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
		if(head == 'i'){
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
   	assert(i == numC+ics);
   	cout<< "tested" << endl;
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




