#include "../intcode.h"
#include <bits/stdc++.h>

using namespace std;

int tryConfig(vector<int>& instr, vector<int>& inps){
	vector<intCode> amps;
	for(int i =0 ;i<5;i++){
		amps.emplace_back(instr);
		amps.back().input.push(inps[i]);
		// amps.back().print(); // for debugging
	}
	int lastOutput = 0;
	for(int i =0 ;i<5;i++){
		// amps[i].debug = true;
		amps[i].input.push(lastOutput);
		
		// amps[i].print();
		while(amps[i].output.empty()){
			amps[i].step();
			// amps[i].print();
		}
		lastOutput = amps[i].output.back();
		// cout<<"output "<<lastOutput<<endl<<endl;
	}
	return lastOutput;
}

int tryConfig2(vector<int>& instr, vector<int>& inps){
	vector<intCode> amps;
	for(int i =0 ;i<5;i++){
		amps.emplace_back(instr);
		amps.back().input.push(inps[i]);
		// amps.back().print(); // for debugging
	}
	int lastOutput = 0;
	int p2 = 0;
	while(true){
		for(int i =0 ;i<5;i++){
			// amps[i].debug = true;
			amps[i].input.push(lastOutput);
			
			// amps[i].print();
			while(amps[i].output.empty()){
				amps[i].step();
				// amps[i].print();
				if(amps[i].done){
					//if done cycle
					return p2;
				}
			}
			lastOutput = amps[i].output.back();
			if(i == 4){
				p2 = lastOutput;
			}
			amps[i].output.pop_back();
			// cout<<"output "<<lastOutput<<endl<<endl;
		}
	}
}
int main(){
	vector<int> instr = readInts(7);
	vector<int> phases = {0,1,2,3,4};
	int p1 = 0;
	do {
		p1 = max(p1, tryConfig(instr, phases));
	} while(next_permutation(phases.begin(), phases.end()));
	cout<<"P1: "<<p1<<endl;

	instr = readInts(7);
	phases = {5,6,7,8,9};
	int p2 = 0;
	do {
		p2 = max(p2, tryConfig2(instr, phases));
	} while(next_permutation(phases.begin(), phases.end()));
	cout<<"P2: "<<p2<<endl;

	
}