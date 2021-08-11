#include "../aoc.h"
#include <functional>
#include <sstream>
#include <unistd.h>


map<string, function<void(vector<int>&, vector<int>&)>> funcs;

void initFunctions(){
	funcs["addr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[2]]+regs[instr[1]];
	};

	funcs["addi"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] + instr[2];
	};

	funcs["mulr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[2]]*regs[instr[1]];
	};

	funcs["muli"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = instr[2]*regs[instr[1]];
	};

	funcs["banr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] & regs[instr[2]];
	};

	funcs["bani"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] & instr[2];
	};

	funcs["borr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] | regs[instr[2]];
	};

	funcs["bori"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] | instr[2];
	};

	funcs["setr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]];
	};

	funcs["seti"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = instr[1];
	};

	funcs["gtir"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = instr[1]>regs[instr[2]];
	};

	funcs["gtri"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]>instr[2];
	};

	funcs["gtrr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]>regs[instr[2]];
	};

	funcs["eqir"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = instr[1]==regs[instr[2]];
	};

	funcs["eqri"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]==instr[2];
	};

	funcs["eqrr"] = [](vector<int>& regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]==regs[instr[2]];
	};
}

struct instr{
	string opc;
	vector<int> instruction;
	instr(){}
	instr(string line){
		instruction = vector<int>(4);
		stringstream ss(line);
		ss>>opc>>instruction[1]>>instruction[2]>>instruction[3];
	}
};

ostream& operator<<(ostream& os, const instr& i){
	os<<i.opc<<"	"<<i.instruction[1]<<"  	"<<i.instruction[2]<<"  	"<<i.instruction[3];
	return os;
}

vector<instr> instructions;

set<pair<int, int>> possibles;

void debugger(int ip){
	vector<int> regs(6);
	int& ind = regs[ip];
	int& watch = regs[2];
	int old = watch;
	string t;
	int step = 0;
	while(ind>=0 && ind<instructions.size()){
		cout<<ind+2<<": 	";
		cout<<instructions[ind];
		if(ind == 24){
			regs[3]/=256;
			ind = 27;
			continue;
		}
		funcs[instructions[ind].opc](regs, instructions[ind].instruction);
		cout<<"	"<<regs<<endl;
		if(ind == 29){
			step++;
			cin>>t;
		}
		ind++;
		old = watch;
	}
}

int eval(vector<int>& regs, int ip){
	int& ind = regs[ip];
	bool p1Done = false;
	string t;
	int& watch = regs[2];
	int old = watch;
	ind =0;
	int p2;
	while(ind>=0 && ind<instructions.size()){
		// cout<<ind+2<<" -	";
		// cout<<instructions[ind]<<"	";
		if(ind == 24){
			regs[3]/=256;
			ind = 27;
			continue;
		}
		funcs[instructions[ind].opc](regs, instructions[ind].instruction);
		if(ind == 28){
			if(!p1Done){
				cout<<"[P1] "<<regs[4]<<endl;
				p1Done = true;
			}
			if(possibles.insert(make_pair(regs[4], regs[3])).second == false){
				cout<<"[P2] "<<p2<<endl;
				//16776181 too high???
				//4855969 too high
				return 0;
			}
			p2 = regs[4];
			// if(rand() % 100 == 1)
			// 	cout<<*possibles.rbegin()<<"	"<<possibles.size()<<endl;
		}
		ind++;
		old = watch;
	}
	return regs[0];	
}

void iterLoop(int& B, int& C){
	for(B=2; (B+1)*256 < C; B++){}
	C = B;
}

void p1(){
	int A, B, C, D, E;
	A=B=C=D=E=0;
	C = D | 65536;
	D = 12670166;
	for(;;){
		B = C & 255;
		D += B;
		D &= 16777215;
		D *= 65899;
		D &= 16777215;
		if (C<256){
			cout<<"[P1] "<<D<<endl;
			return;
		}
		iterLoop(B, C);
	}	
}

int main(){
	initFunctions();
	fstream file("Day 21/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	int ip;
	ss>>line>>ip;
	
	while(getline(file, line))
		instructions.emplace_back(line);

	//  [0, 19, 61290, 15690445, 13069857, 15690496]
	// int B, C(15690445);
	// iterLoop(B,C);
	// cout<<B<<"	"<<C;
	// p1();
	// exit(0);
	// debugger(1);
	vector<int> regs(6);
	eval(regs, ip);
}
