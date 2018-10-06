#include "pa.h"
int main(int argc, char *argv[]){
}

void printVector(vector<int>& vec){
	for (std::vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i){
		cout << *i << ' ';
	}
	cout << endl;
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
			memAllocate(buff);
			break;
		}
	  getline(fp,buff);
	}
   	cout<< "numVs" << numVs<<endl;
   	cout<< "numCs" << numCs<<endl;
}
void memAllocate(string buff){
	char* str = strdup(buff.c_str());
    const char s[2] = " ";
	strtok(str, s);
	strtok(NULL, s);
	numVs = atoi(strtok(NULL, s));
	numCs = atoi(strtok(NULL, s));
	for(int i =0; i < pa; i++){
		clauses.push_back(vector<vector<int>>());
		for(int i = 0; i < numCs; i++){
			clauses[i].push_back(vector<int>());
		}
	}
}












/*
 * 	for(int i =0; i < pa; i++){
		clauses[i][0].push_back(0);
	}
	for(int i =0; i < pa; i++){
		printVector(clauses[i][0]);
	}
 */
