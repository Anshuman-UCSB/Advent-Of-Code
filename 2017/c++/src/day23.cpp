#include "AOC.h"
#define instruction tuple<int, int, int>
#include <cmath>

struct CPU{
	vector<int> r;
	int p;
	int p1;
	CPU():r(8), p(0), p1(0){}
	
	inline void set(int& a, const int& b){a = b;}
	inline void sub(int& a, const int& b){a-= b;}
	inline void mul(int& a, const int& b){a*= b; p1++;}
	inline void jnz(const int& a, const int& b){
		if(a)
			p+=b-1;
	}

	static inline bool isReg(const int& a){
		return a<=-100 && a>=-130;
	}

	void run(const vector<instruction>& instr){
		for(;p>=0 && p<instr.size();p++){
			auto& [opc, a, b] = instr[p];
			switch(opc){
				case 0:
					if(isReg(b)) set(r[-100-a],r[-100-b]);
					else 		 set(r[-100-a],b);
					break;
				case 1:
					if(isReg(b)) sub(r[-100-a],r[-100-b]);
					else 		 sub(r[-100-a],b);
					break;
				case 2:
					if(isReg(b)) mul(r[-100-a],r[-100-b]);
					else 		 mul(r[-100-a],b);
					break;
				case 3:
					if(isReg(a)){
						if(isReg(b)) jnz(r[-100-a],r[-100-b]);
						else 		 jnz(r[-100-a],b);
					}else{
						if(isReg(b)) jnz(a,r[-100-b]);
						else 		 jnz(a,b);
					}
					break;
			}
		}
	}

};

bool isPrime(const int& n){
	for(int i =2;i<=sqrt(n);i++){
		if(n%i==0) return false;
	}return true;
}

int p2solve(){
	int h = 0;
	for(int b = 106700;;b+=17){
		if (!isPrime(b)){
			h++;
		}
		if (b==123700)
			return h;
	}
	return -1;
}

chrono::time_point<std::chrono::steady_clock> day23(input_t& inp){
	vector<instruction> instr;
	for(auto& l: inp){
		stringstream ss(l);
		string t;
		ss>>t;
		instr.emplace_back();
		switch(t[2]){
			case 't': get<0>(instr.back()) = 0; break;
			case 'b': get<0>(instr.back()) = 1; break;
			case 'l': get<0>(instr.back()) = 2; break;
			case 'z': get<0>(instr.back()) = 3; break;
		}
		ss>>t;
		if(t[0]>='a' && t[0]<='z')
			get<1>(instr.back()) = -100-(t[0]-'a');
		else
			get<1>(instr.back()) = stoi(t);
		ss>>t;
		if(t[0]>='a' && t[0]<='z')
			get<2>(instr.back()) = -100-(t[0]-'a');
		else
			get<2>(instr.back()) = stoi(t);

	}
	
	CPU c;
	c.run(instr);

	int p2 = p2solve();


	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<c.p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	//4330240 too high
	//96 wrong 
	//97 wrong 
	return done;
}