#include "pa.h"
int main(int argc, char *argv[]){
	fileName = argv[1];
	pa = atoi(argv[2]);
	readFile(fileName);
	string a = string(argv[1]);
	outFile = (a+l+string(argv[2])+".cnfP").c_str();
	outFP.open(outFile,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	printClauses();
}

void printVector(vector<int>& vec){
	for (std::vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i){
		outFP << *i << ' ';
	}
	outFP << endl;
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
   	// Get the clauses
   	int line = 0;
   	while(!fp.eof() && line < numCs){
		getline(fp,buff);
		if(buff.empty()) break;
		parseLine(buff);
		line++;
   	}
}
void memAllocate(string buff){
	char* str = strdup(buff.c_str());
    const char s[2] = " ";
	strtok(str, s);
	strtok(NULL, s);
	numVs = atoi(strtok(NULL, s))+1;
	numCs = atoi(strtok(NULL, s));
	step = numVs/pa;
	for(int i =0; i < pa+1; i++){
		numC.push_back(0);
		numV.push_back((i+1)*step);
		clauses.push_back(vector<vector<int>>());
		/*for(int j = 0; j < numCs; j++){
			clauses[i].push_back(vector<int>());
		}*/
	}
	numV[pa-1] = numVs-1;
	numC.push_back(0);
}

void parseLine(string line){
	clauseT.clear();
	char* str = strdup(line.c_str());
    const char s[2] = " ";
    int lit;
    int part = -1;
    int mp;
    char* token = strtok(str, s);
    while(token != NULL){
		if(*token== '-'){
			lit = atoi(token);
			for(int i = 0; i < pa; i++){
				if(abs(lit) <= numV[i]){
					mp = i;
					break;
				}
			}
			assert(mp >= 0);
			assert(mp < pa);
			if(part == -1) part = mp;
			else{
				if(part != mp) part = pa;

			}
			assert(part >= 0);
			assert(part <= pa);



			clauseT.push_back(lit);
			token = strtok(NULL, s);
			continue;
		}
		if(*token == '0'){
			clauses[part].push_back(clauseT);
			numC[part]++;
			clauseT.clear();
		    return;
		}
		lit = atoi(token);
		for(int i = 0; i < pa; i++){
			if(abs(lit) <= numV[i]){
				mp = i;
				break;
			}
		}
		assert(mp >= 0);
		assert(mp < pa);
		if(part == -1) part = mp;
		else{
			if(part != mp) part = pa;

		}
		assert(part >= 0);
		assert(part <= pa);

		clauseT.push_back(lit);
		token = strtok(NULL, s);
    }
	perror("a clause line does not terminates");
	exit(EXIT_FAILURE);
}

void printClauses(){
	outFP<<"c "<< pa<<" ";
	outFP<< numVs-1<<" ";
	int start = 0;
	for(int i = 0; i < pa; i++){
		outFP<< numV[i]-start<<" ";
		start = numV[i];
	}
	outFP<< numCs<<" ";
	for(int i = 0; i < pa; i++){
		outFP<< numC[i]<<" ";
	}
	outFP<<endl;
	outFP<<"p "<< numVs-1<<" "<< numCs<<endl;
	for(int i =0; i < pa+1; i++){
		for(int j = 0; j < clauses[i].size();j++){
			printVector(clauses[i][j]);
		}
	}

}
