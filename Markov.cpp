#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <fstream>
using namespace std;


int main(int argc,char* argv[]){
	string txt;
	ifstream input("input.txt");
	if(!input.is_open()){printf("cannot load input.txt");return 0;}
	for(string line;getline(input,line);){
		txt+=line;
	}
	
	srand (time(NULL));
	
	int order=6;//order of grams
	
	map<string,vector<char>> ngram;
	for(int i=0;i<((int)txt.length() - order);i++){
		string gram =txt.substr(i,order);
		
		ngram[gram].push_back(txt.at(i+order));
	}
	
	string currentGram = txt.substr(rand()%txt.size()-order,order);//Take random for beggining
	string result = currentGram;
	for(int i=0;i< 100;i++){
		vector<char> possibilities=ngram[currentGram];
		char next= possibilities[(int)rand()%possibilities.size()];
		result+=next;
		currentGram=result.substr(result.length()-order,order);
	}
	cout<<result<<endl;
	return 0;
}