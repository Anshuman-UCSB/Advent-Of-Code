#include "AOC.h"

struct instr{
	bool write;
	bool dir;
	int nextState;
	instr() = default;
	instr(bool write1, bool goRight, int next):write(write1), dir(goRight), nextState(next){}

	int exec(int& cur, unordered_set<int>& regs){
		if(write)
			regs.insert(cur);
		else
			regs.erase(cur);

		if(dir) cur++;
		else	cur--;
		
		return nextState;
	}
};

struct State{
	instr on, off;
	State() = default;
};

struct Turing{
	unordered_set<int> tape;
	int state;
	int cur;
	vector<State> states;
	Turing(){
		state = 0;
		cur = 0;
	}

	void exec(){
		if(tape.count(cur)){
			state = states[state].on.exec(cur, tape);
		}else{
			state = states[state].off.exec(cur, tape);
		}
	}	
};

chrono::time_point<std::chrono::steady_clock> day25(input_t& inp){
	Turing cpu;
	cpu.state = inp[0][inp[0].size()-2]-'A';
	stringstream ss(inp[1]);
	int steps;
	string trsh;
	ss>>trsh>>trsh>>trsh>>trsh>>trsh>>steps;

	for(int i = 5;i<inp.size();i+=10){
		cpu.states.emplace_back();
		auto& s = cpu.states.back();
		s.off.write = inp[i][22]=='1';
		s.off.dir = (inp[i+1].size() == 33);
		s.off.nextState = inp[i+2][26]-'A';
		s.on.write = inp[i+4][22]=='1';
		s.on.dir = (inp[i+5].size() == 33);
		s.on.nextState = inp[i+6][26]-'A';
	}

	for(int i = 0;i<steps;i++){
		cpu.exec();
		// cout<<"("<<i<<","<<cpu.tape.size()<<")"<<endl;
		// cout<<*cpu.tape.begin()<<" -> "<<*cpu.tape.rbegin()<<endl;
	}
	
	auto done = chrono::steady_clock::now();
	return done;
}