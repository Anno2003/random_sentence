#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>

using namespace std;

int main(){
	srand (time(NULL));
	int order=5;//order of grams
	
	//sample strings
	//string txt="the theremin is theirs, ok? yes, it is. this is a theremin.";
	string txt="soon afterward, out of fear of the suited figures he believed to be following him, davis left town and began driving hundreds of miles south with no destination. after becoming convinced that his car radio was communicating with him, he dismantled his vehicle (apparently in a search for tracking devices he believed were hidden on it) and threw his keys into the desert. he began to walk aimlessly along the side of the highway, where he was then picked up by an officer. davis escaped from the patrol vehicle, broke his collarbone, and was then taken to a hospital. distressed about a conversation over artifacts found on his X-ray scans, interpreted by him as alien artifacts, he ran from the hospital and attempted to carjack a nearby truck before being arrested. In jail, he stripped himself, broke his glasses and jammed the frames into a nearby electrical outlet, trying to open his cell door by switching the breaker. This failed, as he had been wearing non-conductive frames. He was then admitted to a mental hospital for two weeks.";
	
	map<string,vector<char>> ngram;
	for(int i=0;i<((int)txt.length() - order);i++){
		string gram =txt.substr(i,order);
		
		ngram[gram].push_back(txt.at(i+order));
	}
	
	string currentGram = txt.substr(rand()%txt.size()-order,order);//ambil random buat plng pertama 
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