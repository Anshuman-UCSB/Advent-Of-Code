#include "AOC.h"

map<string, string> transforms;

void iter(map<string, ull> &counts){
	map<string, ull> t;
	for(auto& [k, v]: counts){
		auto it = transforms.find(k);
		if(it != transforms.end()){
			t[k[0]+it->second]+=v;
			t[it->second+k[1]]+=v;
		}else
			t[k]+=v;
		
	}
	counts = t;
}

ull score(map<string, ull>& c, string& base){
	vector<ull> chr(26);
	for(auto& [k, v]: c){
		chr[k[0]-'A']+=v;
		chr[k[1]-'A']+=v;
	}
	chr[base[0]-'A']+=1;
	chr[base.back()-'A']+=1;
	ull mx(0), mn(-1);
	for(auto& v: chr){
		mx = max(mx, v);
		if(v)
			mn = min(mn, v);
	}
	return (mx-mn)>>1;
}

chrono::time_point<std::chrono::steady_clock> day14(input_t& inp){
	ull p1, p2;
	map<string, ull> counts;
	string base = inp[0];
	for(int i = 0;i<base.size()-1;i++)
		counts[base.substr(i,2)]++;
	for(int i = 2;i<inp.size();i++)
		transforms[inp[i].substr(0,2)] = inp[i].substr(6);

	for(int i = 0;i<40;i++){
		if(i == 10)
			p1 = score(counts, base);
		iter(counts);
	}
	p2 = score(counts, base);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}