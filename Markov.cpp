#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <fstream>
#include <algorithm>
using namespace std;

string getArg(char** begin,char** end,const string& opt){
	char** itr=find(begin,end,opt);
	if(itr!=end && ++itr != end){return *itr;}
	return 0;
}
bool argExists(char** begin,char** end,const string& opt){
	return find(begin,end,opt) != end;
}

int main(int argc,char* argv[]){
	string txt;
	ifstream input;
	int order;
	srand (time(NULL));
	//handle file loading////////////////
	if(!argExists(argv,argv+argc,"-f")){
		input.open("input.txt");
		if(!input.is_open()){printf("cannot load input.txt");return 0;}
	}else{
		input.open(getArg(argv,argv+argc,"-f"));
		if(!input.is_open()){printf("cannot load file");return 0;}
	}
	for(string line;getline(input,line);){txt+=line;}
	input.close();
	//handle order///////////////////////
	if(!argExists(argv,argv+argc,"-n")){
		order=6;//order of grams
	}else{
		order=stoi(getArg(argv,argv+argc,"-n"),nullptr,0);
	}
	//map ngram/////////////////////////
	map<string,vector<char>> ngram;
	for(int i=0;i<((int)txt.length() - order);i++){
		string gram =txt.substr(i,order);
		
		ngram[gram].push_back(txt.at(i+order));
	}
	//create sentence///////////////////
	string currentGram = txt.substr(rand()%txt.size()-order,order);//Take random for beggining
	string result = currentGram;
	for(int i=0;i< 100;i++){
		vector<char> possibilities=ngram[currentGram];
		char next= possibilities[(int)rand()%possibilities.size()];
		result+=next;
		currentGram=result.substr(result.length()-order,order);
	}
	//print result//////////////////////
	cout<<result<<endl;
	return 0;
}