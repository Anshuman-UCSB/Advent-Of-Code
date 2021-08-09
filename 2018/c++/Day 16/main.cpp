#include "../aoc.h"
#include <sstream>
#include <functional>

struct testCase{
	vector<int> before, after, instr;
	testCase(){
		before = vector<int>(4);
		instr = vector<int>(4);
		after = vector<int>(4);
	}
};

ostream& operator<<(ostream& os, const testCase& tc){
	cout<<"\nBefore:	"<<tc.before<<endl;
	cout<<"Instr:	"<<tc.instr<<endl;
	cout<<"After:	"<<tc.after<<endl;
	return os;
}

vector<set<int>> possible(16, {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
set<int> solved = {};
vector<function<vector<int>(vector<int>, vector<int>&)>> funcs(16);

void initFunctions(){
	//addr
	funcs[0] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[2]]+regs[instr[1]];
		return regs;
	};

	//addi
	funcs[1] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] + instr[2];
		return regs;
	};

	//mulr
	funcs[2] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[2]]*regs[instr[1]];
		return regs;
	};

	//muli
	funcs[3] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = instr[2]*regs[instr[1]];
		return regs;
	};

	//banr
	funcs[4] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] & regs[instr[2]];
		return regs;
	};

	//bani
	funcs[5] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] & instr[2];
		return regs;
	};

	//borr
	funcs[6] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] | regs[instr[2]];
		return regs;
	};

	//bori
	funcs[7] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]] | instr[2];
		return regs;
	};

	//setr
	funcs[8] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]];
		return regs;
	};

	//seti
	funcs[9] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = instr[1];
		return regs;
	};

	//gtir
	funcs[10] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = instr[1]>regs[instr[2]];
		return regs;
	};

	//gtri
	funcs[11] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]>instr[2];
		return regs;
	};

	//gtrr
	funcs[12] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]>regs[instr[2]];
		return regs;
	};

	//eqir
	funcs[13] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = instr[1]==regs[instr[2]];
		return regs;
	};

	//eqri
	funcs[14] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]==instr[2];
		return regs;
	};

	//eqrr
	funcs[15] = [](vector<int> regs, vector<int>& instr){
		regs[instr[3]] = regs[instr[1]]==regs[instr[2]];
		return regs;
	};

}

int p1c = 0;

void test(testCase& tcase){
	// cout<<tcase<<endl;
	auto& p = possible[tcase.instr[0]];
	int potential = 0;
	for(int id = 0;id<16;id++){
		if(tcase.after != funcs[id](tcase.before, tcase.instr)){
			p.erase(id);
		}else{
			potential++;
		}
	}
	if(potential>=3) p1c++;	
}

vector<testCase> tc;
void p1(){
	for(auto& tcase: tc){
		test(tcase);
	}
	cout<<"[P1] "<<p1c<<endl;
}

vector<int> mapping(16, -1);
//mapping[opc] = funcId
void p2(){
	while(solved.size()<16){
		for(int i = 0;i<16;i++){
			if(possible[i].size() == 1){
				solved.insert(*possible[i].begin());
				mapping[i] = *possible[i].begin();
				for(auto& s: possible){
					s.erase(mapping[i]);
				}
			}
		}
		// cout<<possible<<endl;
		// cout<<solved<<endl;
	}
	// cout<<mapping<<endl;
}

int main(){
	initFunctions();
	fstream file("Day 16/input");
	string line;
	char trash;
	while(getline(file, line)){
		if(line[0]!='B') break;
		tc.emplace_back();
		stringstream ss(line);
		ss>>line>>trash>>tc.back().before[0]>>trash>>tc.back().before[1]>>trash>>tc.back().before[2]>>trash>>tc.back().before[3];
		getline(file, line);
		ss = stringstream(line);
		ss>>tc.back().instr[0]>>tc.back().instr[1]>>tc.back().instr[2]>>tc.back().instr[3];
		getline(file, line);
		ss = stringstream(line);
		ss>>line>>trash>>tc.back().after[0]>>trash>>tc.back().after[1]>>trash>>tc.back().after[2]>>trash>>tc.back().after[3];
		getline(file, line);
	}

	p1();
	p2();
	getline(file, line);
	vector<int> regs(4);
	vector<int> instr(4);
	while(getline(file, line)){
		stringstream ss(line);
		ss>>instr[0]>>instr[1]>>instr[2]>>instr[3];
		regs = funcs[mapping[instr[0]]](regs, instr);
	}	
	cout<<"[P2] "<<regs[0]<<endl;
}