#include "AOC.h"
#define num long

vector<tuple<int, int, int>> instr;

/**

	1	snd X
	2	set X Y
	3	add X Y
	4	mul X Y
	5	mod X Y
	6	rcv X r
	7	jgz X Y 

 **/

int p1(){
	int p = 0;
	num r[26] = {};
	int res = 0;
	while(p>=0 && p<instr.size()){
		auto& [opc, a, b] = instr[p];
		switch(opc){
			case 101: 	res  = r[a]; 	break;
			case 102: 	r[a] =   b;		break;
			case 1102:	r[a] = r[b];	break;
			case 103: 	r[a]+=   b;		break;
			case 1103:	r[a]+= r[b];	break;
			case 104:	r[a]*=   b; 	break;
			case 105:	r[a]%=   b; 	break;
			case 1105:	r[a]%= r[b]; 	break;
			case 106:	if(r[a]) return res; break;
			case 107:	if(r[a]) p+=b-1;	break;
			case 1107:	if(r[a]) p+=r[b]-1;	break;
		}
		p++;
	}
	return -1;
}

int p2(){
	queue<num> inps[2] = {};
	num regs[2][26] = {};
	regs[1]['p'-'a'] = 1;
	int pos[2] = {};
	int old = -1;
	int res = 0;
	while(old != res){
		old = res;

		for(int turn = 0;turn<2;turn++){
			int& p = pos[turn];
			auto& r = regs[turn];
			auto& out = inps[!turn];
			auto& inp = inps[turn];
			while(p>=0 && p<instr.size()){
				auto& [opc, a, b] = instr[p];
				
				switch(opc){
					case 101: 	out.push(r[a]); 
						// cout<<char('a'+turn)<<" pushed "<<r[a]<<endl;
						if(turn) res++;	break;
					case 102: 	r[a] =   b;		break;
					case 1102:	r[a] = r[b];	break;
					case 103: 	r[a]+=   b;		break;
					case 1103:	r[a]+= r[b];	break;
					case 104:	r[a]*=   b; 	break;
					case 105:	r[a]%=   b; 	break;
					case 1105:	r[a]%= r[b]; 	break;
					case 106:	
						if(inp.empty()) {goto next;}
						r[a] = inp.front(); inp.pop();
						// cout<<char('a'+turn)<<" popped "<<r[a]<<endl;
						break;
					case 7:	if(a>0) p+=b-1;	break;
					case 107:	if(r[a]>0) p+=b-1;	break;
					case 1107:	if(r[a]>0) p+=r[b]-1;	break;
					default: cout<<opc<<endl;;
				}
				p++;
			}
			next:;
			// cout<<char('a'+turn)<<" finished at "<<pos[turn]<<endl;
			// cout<<res<<endl;
		}
	}
	return res;
	
}

chrono::time_point<std::chrono::steady_clock> day18(input_t& inp){
	for(auto& l: inp){
		instr.emplace_back();

		stringstream ss(l);
		string t;
		ss>>t;
		int& opc = get<0>(instr.back());
		string tmp;
		ss>>tmp;
		if('a'<=tmp[0] || tmp[0]>='z'){
			opc+=100;
			get<1>(instr.back()) = tmp[0]-'a';
		}else{
			get<1>(instr.back()) = stoi(tmp);
		}

		if(t[1] != 'c' && t[1] != 'n'){
			ss>>tmp;
			if('a'<=tmp[0] || tmp[0]>='z'){
				opc+=1000;
				get<2>(instr.back()) = tmp[0]-'a';
			}else{
				get<2>(instr.back()) = stoi(tmp);
			}
		}
		switch(t[1]){
			case 'n': opc+=1; break;
			case 'e': opc+=2; break;
			case 'd': opc+=3; break;
			case 'u': opc+=4; break;
			case 'o': opc+=5; break;
			case 'c': opc+=6; break;
			case 'g': opc+=7; break;
		}
	}

	
	int p1res = p1();
	int p2res = p2();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1res<<endl;
	cout<<"[P2] "<<p2res<<endl;
	//254 too low
	return done;
}