#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day08(input_t& inp){
	map<string, int> regs;
	map<string, function<bool(string& reg, int amnt)>> comp;
	comp[">"] = [&](const string& reg, const int& amnt){ return regs[reg]>amnt;};
	comp[">="] = [&](const string& reg, const int& amnt){ return regs[reg]>=amnt;};
	comp["<"] = [&](const string& reg, const int& amnt){ return regs[reg]<amnt;};
	comp["<="] = [&](const string& reg, const int& amnt){ return regs[reg]<=amnt;};
	comp["=="] = [&](const string& reg, const int& amnt){ return regs[reg]==amnt;};
	comp["!="] = [&](const string& reg, const int& amnt){ return regs[reg]!=amnt;};
	int p2 = 0;
	for(auto& l: inp){
		stringstream ss(l);
		string regA, regB, instr, compType, trash;
		int amt, amt2;
		ss>>regA>>instr>>amt>>trash>>regB>>compType>>amt2;
		if(comp[compType](regB, amt2)){
			if(instr == "inc")
				regs[regA]+=amt;
			else
				regs[regA]-=amt;
			p2 = max(p2, regs[regA]);
		}
	}
	int p1 = 0;
	for(auto& [ignore, v] : regs){
		p1 = max(p1, v); 
	}

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}