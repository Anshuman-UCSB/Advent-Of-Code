#include "AOC.h"

vector<int> regs;

void iter(const string& inp){
	stringstream ss(inp);
	char t;
	int a, b;
	char c,d;

	while(ss>>t){
		switch(t){
			case 's': 
				ss>>a;
				for(auto& v: regs){
					v+=a;
					v&=0xf;
				}
				break;
			case 'x':
				ss>>a>>t>>b;
				for(auto& v: regs){
					if(v == a){
						v = b;
					}else if(v == b){
						v = a;
					}
				}
				break;
			case 'p':
				ss>>c>>t>>d;
				swap(regs[c-'a'], regs[d-'a']);
				break;
		}
		ss>>t;
	}
}

chrono::time_point<std::chrono::steady_clock> day16(input_t& inp){
	regs = vector<int>(16);
	iota(regs.begin(), regs.end(), 0);
	map<vector<int>, int> cache;
	iter(inp[0]);
	string p1(16,' ');
	for(int i =0;i<regs.size();i++){
		p1[regs[i]] = i+'a';
	}
	bool flag = false;
	for(int i = 1;i<1000000000;i++){
		iter(inp[0]);
		if(flag) continue;
		if(cache.count(regs)){
			int cycle = i-cache[regs];
			i = ((1000000000-i)/cycle)*cycle+i;
			flag = true;
		}else{
			cache[regs] = i;
		}
	}
	string p2(16,' ');
	for(int i =0;i<regs.size();i++){
		p2[regs[i]] = i+'a';
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}