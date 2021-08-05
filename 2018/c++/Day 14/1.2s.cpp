#include "../aoc.h"
#include <algorithm>

vector<short> regs={3,7};
int i1(0), i2(1);

map<pair<int, int>, vector<short>> cache;
int inp;

static void print(){
	for(int i = 0;i<regs.size();i++){
		if(i == i1)cout<<"(";
		else if(i == i2)cout<<"[";
		else cout<<" ";
		cout<<regs[i];
		if(i == i1)cout<<")";
		else if(i == i2)cout<<"]";
		else cout<<" ";
	}cout<<endl;
}

static vector<short> combine(){
	vector<short> out;
	if(auto it = cache.find(make_pair(regs[i1], regs[i2])); it!=cache.end()){
		// cout<<"Caching"<<i1<<", "<<i2<<endl;
		return (*it).second;
	}
	for(short combined = regs[i1]+regs[i2];combined!=0;combined/=10){
		out.push_back(combined%10);
	}
	cache[make_pair(regs[i1], regs[i2])] = out;
	return out;
}

static void step(){
	auto output = combine();
	regs.insert(regs.end(), output.rbegin(), output.rend());
	i1 = (1+i1+regs[i1])%regs.size();
	i2 = (1+i2+regs[i2])%regs.size();
}


void p1(){
	cache[make_pair(0,0)] = vector<short>(1);
	while(regs.size()<inp+10){
		step();
		// cout<<regs.size()<<endl;
		// print();
	}
	cout<<"[P1] ";
	for(int i = inp;i<inp+10;i++){
		cout<<regs[i];
	}cout<<endl;
}

void p2(){
	int i(0);
	vector<int> match;
	while(inp){
		match.push_back(inp%10);
		inp/=10;
	}
	reverse(match.begin(), match.end());

	while(1){
		for(;i+match.size()<regs.size();i++){
			for(int j = i;j<i+match.size();j++){
				if(regs[j] != match[j-i]){
					goto next;
				}
			}
			cout<<"[P2] "<<i<<endl;
			return;
			next:;
		}
		step();
	}
}

int main(){
	fstream file("Day 14/input");
	file>>inp;
	regs.reserve(inp);
	// inp = 2018;
	p1();
	p2();
}