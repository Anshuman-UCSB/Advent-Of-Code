#include "AOC.h"
#define getReg(x) regs[x[0]-'a']

vector<tuple<char, string, string>> instr;
long long p1Val;

struct CPU{
	vector<long long> regs;
	queue<long long> inp;
	long long ind;
	bool deadlocked;
	queue<long long> output;
	bool p1;
	int p2;

	CPU(queue<long long>& out, bool p1): p1(p1), output(out){
		ind = 0;
		deadlocked = false;
		regs = vector<long long>(26);
		p2 = 0;
	}

	void snd(const long long& a){
		p2++;
		if(p1) p1Val = a;
		output.push(a);
	}

	void set(long long& a, const long long& b){
		a = b;
	}

	void add(long long& a, const long long& b){
		a += b;
	}

	void mul(long long& a, const long long& b){
		a *= b;
	}

	void mod(long long& a, const long long& b){
		a %= b;
	}

	bool rcv(long long& a){
		if(p1)
			return a;
		if(inp.empty()){
			deadlocked = true;
			return false;
		}
		a = inp.front();
		inp.pop();
		return true;
	}

	void jgz(const long long& a, const long long& b){
		if(a) ind+=b-1;
	}

	static inline bool isReg(const string& ins){
		return 'a'<=ins[0] && ins[0]<='z';
	}

	bool run(){ //ret false if waiting
		bool resp;
		for(;;){
			auto& [opc, par1, p2] = instr[ind];
			switch(opc){
				case 'n': //snd
					cout<<"Running command "<<opc<<" "<<par1<<" "<<p2<<endl;
					snd(getReg(par1));
					break;
				case 'e':
					if(isReg(p2)) set(getReg(par1), getReg(p2));
					else set(getReg(par1), stoi(p2));
					break;
				case 'd':
					if(isReg(p2)) add(getReg(par1), getReg(p2));
					else add(getReg(par1), stoi(p2));
					break;
				case 'u':
					if(isReg(p2)) mul(getReg(par1), getReg(p2));
					else mul(getReg(par1), stoi(p2));
					break;
				case 'o':
					if(isReg(p2)) mod(getReg(par1), getReg(p2));
					else mod(getReg(par1), stoi(p2));
					break;
				case 'c':
					resp = rcv(getReg(par1));
					if(p1 && resp) return true;
					if(resp == false){
						return false;
					}
					break;
				case 'g':
					if(isReg(par1)){
						if(isReg(p2))
							jgz(getReg(par1),getReg(p2));
						else
							jgz(getReg(par1),stoi(p2));
					}else{
						if(isReg(p2))
							jgz(stoi(par1),getReg(p2));
						else
							jgz(stoi(par1),stoi(p2));
					}
					break;
			}
			// cout<<regs<<endl;
			ind++;
		}

		return true;
	}
};

chrono::time_point<std::chrono::steady_clock> day18(input_t& inp){
	for(auto& l: inp){
		stringstream ss(l);
		string t;
		string reg;
		string param;
		ss>>t>>reg>>param;
		instr.emplace_back(t[1], reg, param);
	}
	
	queue<long long> p1q;
	CPU a(p1q, true);
	a.run();
	a = CPU(p1q, false);
	CPU b = CPU(a.inp, false);
	a.output = &b.inp;
	b.regs['p'-'a'] = 1;
	int old = -1;
	while(old != b.output.size()){
		old = b.output.size();
		// if(a.run()) break;
		// if(b.run()) break;
		a.run();
		b.run();
	}

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1Val<<endl;
	cout<<"[P2] "<<b.p2<<endl;
	return done;
}
//127 too low