#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day05(input_t& inp){
	int instr[inp.size()];
	int instr2[inp.size()];
	for(int i = 0;i<inp.size();i++){
		instr[i] = stoi(inp[i]);
		instr2[i] = stoi(inp[i]);
	}
	int p1 = 0;
	int ptr;
	for(ptr = 0;ptr>=0 && ptr<inp.size(); p1++){
		ptr+=instr[ptr]++;
	}
	int p2 = 0;
	for(ptr = 0;ptr>=0 && ptr<inp.size(); p2++){
		ptr+=(instr2[ptr]>=3?instr2[ptr]--:instr2[ptr]++);
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}