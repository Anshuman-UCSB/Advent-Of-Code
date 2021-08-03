#include "../aoc.h"

vector<int> freqs;

int main(){
	fstream file("Day 1/input");
	set<int> cache;
	string line;
	int fq(0);
	while(getline(file, line)){
		freqs.push_back(stoi(line));
		fq+=freqs.back();
		cache.insert(fq);
	}
	cout<<"[P1] "<<fq<<endl;
	while(1){
		for(auto& v: freqs){
			fq+=v;
			if(cache.insert(fq).second==false){
				cout<<"[P2] "<<fq<<endl;
				return 0;
			}
		}
	}
}