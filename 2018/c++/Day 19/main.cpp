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
	string t;
	while(ind>=0 && ind<instructions.size()){
		funcs[instructions[ind].opc](regs, instructions[ind].instruction);
		ind++;
	}
	return regs[0];	
}

int main(){
	// fstream file("Day 19/modinp");
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

	cout<<"[P1] "<<eval(regs, ip)<<endl;
	int p2 = 0;
	const int target = 10551403;
	for(int i = 1; i*i<=target;i++){
		if(target%i==0){
			p2+=i;
			p2+=target/i;
		}
	}
	cout<<"[P2] "<<p2<<endl;
}