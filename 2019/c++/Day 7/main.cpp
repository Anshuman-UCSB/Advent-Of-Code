#include "../intcode.h"
#include <bits/stdc++.h>

using namespace std;

int tryConfig(string instr, vector<int>& inps){
	vector<IntCode> amps;
	for(int i =0 ;i<5;i++){
		amps.emplace_back(instr, false);
		amps.back().push(inps[i]);
	}
	int lastOutput = 0;
	for(int i =0 ;i<5;i++){
		amps[i].push(lastOutput);
		while(amps[i].out.empty()){
			amps[i].step();
		}
		lastOutput = amps[i].pop();
	}
	return lastOutput;
}

int tryConfig2(string instr, vector<int>& inps){
	vector<IntCode> amps;
	for(int i =0 ;i<5;i++){
		amps.emplace_back(instr, false);
		amps.back().push(inps[i]);
	}
	int lastOutput = 0;
	int ampEOut;
	while(true){
		for(int i =0 ;i<5;i++){
			amps[i].push(lastOutput);
			while(amps[i].out.empty()){
				amps[i].step();
				if(amps[i].done)
					return ampEOut;
			}
			lastOutput = amps[i].pop();
			if(i == 4){
				ampEOut = lastOutput;
			}
		}
	}
}


int main(){
	fstream file("Day 7/input");
	string line;
	getline(file, line);
	vector<int> phases = {0,1,2,3,4};
	int p1 = 0;
	do {
		p1 = max(p1, tryConfig(line, phases));
	} while(next_permutation(phases.begin(), phases.end()));
	cout<<"[P1] "<<p1<<endl;
	phases = {5,6,7,8,9};
	int p2 = 0;
	do {
		p2 = max(p2, tryConfig2(line, phases));
	} while(next_permutation(phases.begin(), phases.end()));
	cout<<"[P2] "<<p2<<endl;

	
}