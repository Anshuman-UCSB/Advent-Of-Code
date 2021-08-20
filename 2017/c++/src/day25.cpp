#include "AOC.h"

enum class State{A,B,C,D,E,F};

chrono::time_point<std::chrono::steady_clock> day25(input_t& inp){

	bool regs[100000] = {};
	int cur = 20;
	State s = State::A;
	for(int i = 0;i<12459852;i++){
		switch(s){
			case State::A:
				if(regs[cur]){
					cur--;
					s = State::E;
				}else{
					regs[cur++]=true;
					s = State::B;
				}
				break;
			case State::B:
				if(regs[cur]){
					cur++;
					s = State::F;
				}else{
					regs[cur++]=true;
					s = State::C;
				}
				break;
			case State::C:
				if(regs[cur]){
					regs[cur++] = false;
					s = State::B;
				}else{
					regs[cur--]=true;
					s = State::D;
				}
				break;
			case State::D:
				if(regs[cur]){
					regs[cur--] = false;
					s = State::C;
				}else{
					regs[cur++] = true;
					s = State::E;
				}
				break;
			case State::E:
				if(regs[cur]){
					regs[cur++] = false;
					s = State::D;
				}else{
					regs[cur--] = true;
					s = State::A;
				}
				break;
			case State::F:
				if(regs[cur]){
					cur++;
					s = State::C;
				}else{
					regs[cur++] = true;
					s = State::A;
				}
				break;
		}
	}
	int p1 = 0;
	for(int i = 0;i<100000;i++){
		if(regs[i])p1++;
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	return done;
}