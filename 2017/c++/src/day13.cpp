#include "AOC.h"

map<int, int> m;
int p1Solve(){
	const int t = 0;
	int out = 0;
	for(auto& [depth, period]: m){
		if((t+depth)%period == 0){
			out+=depth*(period/2 + 1);
		}
	}
	return out;
}

bool p2Help(int& t){
	for(auto& [depth, period]: m){
		if((t+depth)%period == 0){
			return false;
		}
	}
	return true;
}

int p2Solve(){
	for(int i = 0;;i++){
		if(p2Help(i)) return i;
	}
}

static inline int gcd(int x, int y){
	int t; 
	while(x){
		t = x;
		x=y%x; y = t;
	}
	return y;
}

chrono::time_point<std::chrono::steady_clock> day13(input_t& inp){
	for(auto& l: inp){
		stringstream ss(l);
		string tr;
		pii t;
		ss>>t.first>>tr>>t.second;
		t.second--;
		t.second*=2;
		m.insert(t);
	}
	int p1 = p1Solve();
	int p2 = p2Solve();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}