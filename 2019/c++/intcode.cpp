#include "intcode.h"

	
IntCode::IntCode(const vector<ll>& inputRegs, bool debug){
	regs = vector<ll>(regs);
	ind = 0;
	rel = 0;
	done = false;
	this->debug = debug;
}

IntCode::IntCode(){
	ind = 0;
	rel = 0;
	done = false;
	debug = false;
}

int IntCode::getType(int pos){
	ll opc = regs[ind];
	opc/=10;
	for(int i = 0;i<pos;i++){
		opc/=10;
	}
	return opc%10;
}

ll IntCode::getParam(int pos){
	int type = getType(pos);

	switch(type){
		case 0: return regs[regs[ind+pos]];
		case 1: return regs[ind+pos];
		case 2: return regs[rel + regs[ind+pos]];
	}
}

void IntCode::setParam(int pos, ll val){
	int type = getType(pos);

	switch(type){
		case 0: regs[regs[ind+pos]] = val; break;
		case 1: regs[ind+pos] = val; break;
		case 2: regs[rel + regs[ind+pos]] = val; break;
	}
}