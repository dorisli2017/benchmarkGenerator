/*
 *file1 file2 <n1P> <n2P> <mP> seed timeLimit(for intersection)
 *---------------------------------------
 *c <command>
 *c
 *c
 *c <seed>
 *c intersection
 *c <numP> <numVs> <numV1> ... <numCs> <numC1>.... <numCn>
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
	fileName = "result";
	/*fileName = ("../../combine/"+a+ l + b +l + string(argv[3])+
			l + string(argv[4])+l + string(argv[5])+l + string(argv[6])).c_str();
	*/
	outFP.open(fileName,std:: ios::out);
	if(!outFP.is_open()){
		perror("write file fails!!!");
				exit(EXIT_FAILURE);
	}
	combineFile();
	outFP.close();
	fp1.close();
	fp2.close();
	//test();
}
// append
void combineFile(){
	readFile_1();
	readFile_2();
	printSeed();
	printInter();
	outFP<<"c " << 2<<" " << numVs-1 <<" "<< numV1-1<< " "<< numV2<< " "<< numCs<< " "<< numC1 << " "<< numC2<<endl;
	outFP<< "p" <<" "<< numVs-1<<" "<< numCs<<endl;
	printClauses();
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
			numV1 = atoi(strtok(NULL, s));
			is1 = numV1* alpha1;
			numV1++;
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
}
void readIntersection(){
	clock_t tStart = clock();
	int is = is1+is2;
	 set<int> m;
	 vector<bool> sign;
	 int nump = 0;
	 int i = 0;
	 int change = 0;
	 int last = 0;
	 set<int>::iterator it;
	 while(i < ics){
		 if(((double)(clock() - tStart)/CLOCKS_PER_SEC) > timeLimit) break;
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
		 if(change > 0){
			 assert(*m.rbegin()>= numV1);
			 assert(*m.begin()< numV1);
			 if(nump == 0){
				 int flip = rand()%numI;
				 for(int i =0 ; i < numI; i++){
					 if(i == flip) continue;
					 sign[i] =  (rand()%2 == 1);
				 }
				 if(sign[flip]) sign[flip]= false;
				 else sign[flip]= true;
			 }
			 set<int>::iterator itm = m.begin();
			 for(int j =0; j < numI; j++){
				 bool si = sign[j];
				 int v = *itm;
				 if(si){
					 clauseT.push_back(v);
					 realinter.insert(v);
				 }
				 else{
					 clauseT.push_back(-v);
					 realinter.insert(v);
				 }
				 advance(itm,1);
			 }
			// clauses.push_back(clauseT);
			 clauseT.clear();
			 i++;
		 }
		 sign.clear();
		 nump = 0;
		 change = 0;
		 last = 0;
		 m.clear();
	 }
	 ics = i;
	 numCs += ics;
	 assert(i == ics);
}
void parseLine(string line,int off){
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
			printVector(clauseT,off);
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
   //	assert(i == numCs);
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
void printSeed(){
	outFP<<"c ";
	for(int i = 0; i < numVs; i++){
		if(assign[i]) outFP<< i<<" ";
		else  outFP<< -i<<" ";
	}
	outFP<< endl;
}
void printInter(){
	outFP<<"c ";
	for(int const& i:inter){
		outFP<<i<<" ";
	}
	outFP<< endl;
}
void printClauses(){
	int line = 0;
	while(!fp1.eof()){
		getline(fp1,buff);
		if(buff.empty()) break;
		parseLine(buff, 0);
		line++;
	}
	assert(line == numC1);
	line = 0;
	while(!fp2.eof()){
		getline(fp2,buff);
		if(buff.empty()) break;
		parseLine(buff, numV1-1);
		line++;
	}
	assert(line == numC2);
}
