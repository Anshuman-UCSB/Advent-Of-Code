<<<<<<< HEAD
#include "../aoc.h"

vector<int> freqs;

int main(){
	Timer t;
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
				goto out;
			}
		}
	}
	out:;
	t.end();
=======
#include "../aoc.h"

int p1(){

}
int p2(){

}

int main(){
	Timer t;t.start();
	
	t.end();
	cout<<"[P1] "<<p1()<<endl;
	cout<<"[P2] "<<p2()<<endl;
>>>>>>> 9b5cc1ba6d3640016b215cfd288c2393f829fce7
}