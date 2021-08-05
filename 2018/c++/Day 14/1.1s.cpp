#include "../aoc.h"
#include <algorithm>
#define small int8_t

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


int p2(0);
vector<short> match;

bool isMatch(int pos){
	for(int i = 0;i<match.size();i++){
		if(regs[i+pos] != match[i]){
			return false;
		}
	}
	return true;
}

void p1(){
	regs.reserve(100000000);
	cache[make_pair(0,0)] = vector<short>(1);
	for(int copy = inp;copy;copy/=10){
		match.push_back(copy%10);
	}
	reverse(match.begin(), match.end());
		
	while(regs.size()<inp+10){
		step();
		if(p2==0 && regs.size()>match.size()){
			if(isMatch(regs.size()-match.size()))
				p2 = regs.size()-match.size();
			if(isMatch(regs.size()-match.size()-1))
				p2 = regs.size()-match.size();
		}
	}
	cout<<"[P1] ";
	for(int i = inp;i<inp+10;i++){
		cout<<regs[i];
	}cout<<endl;
	while(p2==0){
		step();
		if(p2==0 && regs.size()>match.size()){
			if(isMatch(regs.size()-match.size()))
				p2 = regs.size()-match.size();
			if(isMatch(regs.size()-match.size()-1))
				p2 = regs.size()-match.size();
		}		
	}
	cout<<"[P2] "<<p2<<endl;
}

int main(){
	fstream file("Day 14/input");
	file>>inp;
	regs.reserve(inp);
	// inp = 2018;
	p1();
}