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
	os<<i.opc<<"	"<<i.instruction[1]<<" "<<i.instruction[2]<<" "<<i.instruction[3];
	return os;
}

vector<instr> instructions;

int eval(vector<int>& regs, int ip){
	initFunctions();
	int& ind = regs[ip];
	int old = ind;
	string t;
	while(ind>=0 && ind<instructions.size()){
		// cout<<"("<<instructions[ind].opc<<")"<<endl;
		// cout<<"ip="<<ind<<"	";
		// cout<<instructions[ind].opc<<"	"<<instructions[ind].instruction<<"->	";
		cout<<ind+2<<":	"<<instructions[ind];
		funcs[instructions[ind].opc](regs, instructions[ind].instruction);
		cout<<"	";
		for(auto& v: regs){
			cout<<v<<"	";
		}
		
		cout<<endl;
		// if(ind != old)
			// cin>>t;
		ind++;
		old = ind;
		// sleep(1);
	}
	// cout<<regs<<endl;
	return regs[0];	
}

int main(){
	fstream file("Day 19/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	int ip;
	ss>>line>>ip;
	
	vector<int> regs(6);
	while(getline(file, line))
		instructions.emplace_back(line);
	// for(auto& i: instructions){
	// 	cout<<i.opc<<"	"<<i.instruction<<endl;
	// }

	// cout<<"[P1] "<<eval(regs, ip)<<endl;
	regs = vector<int>(6);
	regs[0] = 1;
	// cout<<regs<<endl;
	cout<<"[P2] "<<eval(regs, ip)<<endl;
}