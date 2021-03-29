#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

string get_last_word(const string& s) {
  auto index = s.find_last_of(' ');
  return s.substr(++index);
}
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
	int order=0;
	map<string,vector<string>> ngram;
	vector<string> words;
	bool withOrder=false;
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
	//handle order&map ngram/////////////
	if(!argExists(argv,argv+argc,"-n")){
		//TODO:remove newline before adding into the word vector
		stringstream iss(txt);
		for(string word;getline(iss,word,' ');){//take each word 
			words.push_back(word);
		}
		for(int i=0;i<(int)words.size();i++){//map word with all possibilities of adjacent word[default]
			ngram[words[i]].push_back(words[i+1]);
		}			
	}else{
		withOrder=true;
		order=stoi(getArg(argv,argv+argc,"-n"),nullptr,0);
		for(int i=0;i<((int)txt.length() - order);i++){//mapping[order]
			string gram =txt.substr(i,order);
			ngram[gram].push_back(txt.substr(i+order,1));
		}
	}
	//create sentence///////////////////
	string currentGram =(withOrder)? txt.substr(rand()%txt.size()-order,order) : words[(int)rand()%words.size()];//Take random for beggining

	string result = currentGram;
	while((result.substr(result.length()-1)!=".")||(result.length()<100)){
		vector<string> possibilities=ngram[currentGram];
		string next= possibilities[(int)rand()%possibilities.size()];
		result+=(withOrder)?next:" "+next;
		currentGram=(withOrder)?result.substr(result.length()-order,order):get_last_word(result);
	}
	//print result//////////////////////
	cout<<result<<endl;
	
	return 0;
}