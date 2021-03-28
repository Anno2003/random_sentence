#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <fstream>
#include <algorithm>
using namespace std;

string get_last_word(const string& s) {
  auto index = s.find_last_of(' ');
  return s.substr(++index);
}
int main(int argc,char* argv[]){
	srand (time(NULL));
	ifstream input("input.txt");
	if(!input.is_open()){printf("cannot load input.txt");return 0;}
	
	map<string,vector<string>> ngram;
	vector<string> words;
	for(string line;getline(input,line,' ');){
		line.erase(remove(line.begin(),line.end(),'\n'),line.end());//remove newline from word
		words.push_back(line);
	}
	for(int i=0;i<(int)words.size();i++){
		ngram[words[i]].push_back(words[i+1]);
	}
	
	string currentGram = words[(int)rand()%words.size()];//Take random word for beggining
	string result = currentGram;
	while(result.substr(result.length()-1)!="."){
		vector<string> possibilities=ngram[currentGram];
		string next= possibilities[(int)rand()%possibilities.size()];
		result+=" "+next;
		currentGram=get_last_word(result);
	}
	cout<<result<<endl;
	
	return 0;
}