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

int eval(vector<int>& regs, int ip){
	int& ind = regs[ip];
	string t;
	int& watch = regs[ip];
	int old = watch;
	ind =0;
	while(ind>=0 && ind<instructions.size()){
		cout<<ind+2<<" -	";
		cout<<instructions[ind]<<"	";
		funcs[instructions[ind].opc](regs, instructions[ind].instruction);
		cout<<regs<<endl;
		if(old != watch){
			// cin>>t;
		}
		ind++;
		old = watch;
	}
	return regs[0];	
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

	vector<int> regs(6);
	regs[0] = 9999;
	eval(regs, ip);
}