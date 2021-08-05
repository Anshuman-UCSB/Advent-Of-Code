#include "../aoc.h"
#include <numeric>

#define ITERS 50000000000

vector<vector<bool>> rules;
set<int> pots;
static bool checkMatch(int pos,const vector<bool>& rule){
	for(int i = pos-2;i<=pos+2;i++){
		if(rule[2+i-pos] != pots.count(i))
			return false;
	}
	return true;
}

static void print(set<int>& pots){
	for(int i = -5; i<=40; i++){
		cout<<(pots.count(i)?'#':'.');
	}cout<<endl;
}

void gen(){
	set<int> out;
	set<int> checks;
	for(auto v: pots){
		for(int i = -2; i<=2;i++){
			checks.insert(v+i);
		}
	}
	for(const auto& ind: checks){
		for(const auto& r: rules)
			if(checkMatch(ind, r)){
				out.insert(ind);
			}
	}
	pots.swap(out);
}

static inline long eval(){
	return accumulate(pots.begin(), pots.end(), 0);
}

void p12(){
	for(int i = 0;i<20;i++){
		// cout<<i<<":	";
		// print(pots);
		gen();
	}
	cout<<"[P1] "<<eval()<<endl;
	long old(0), t(0);
	map<int, int> deltas;
	for(unsigned i = 20;i<ITERS; i++){
		gen();
		t = eval();
		if(long delt = deltas[t - old]++; delt>3){
			cout<<"[P2] "<<(t+((long)(ITERS-i-1))*(t-old))<<endl;
			return;
		}
		
		old = t;
	}
	cout<<"[P2] "<<eval()<<endl;
}

int main(){
	fstream file("Day 12/input");
	string line;
	getline(file, line);
	line = line.substr(15);
	for(int i = 0;i<line.size();i++){
		if(line[i] & 1){ //# true; . false
			pots.insert(i);
		}
	}
	getline(file, line); //blank line
	while(getline(file, line)){
		if(!(line[9]&1)) continue; //only store alive
		rules.emplace_back(5);
		for(int i = 0;i<5;i++){
			rules.back()[i] = line[i]&1;
		}
	}
	p12();	
}
