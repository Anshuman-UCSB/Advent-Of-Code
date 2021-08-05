#include "../aoc.h"
#include <algorithm>
#define small short

small regs[30000000]={3,7};
unsigned regsSize = 2;
int i1(0), i2(1);

int inp;

static void print(){
	for(int i = 0;i<regsSize;i++){
		if(i == i1)cout<<"(";
		else if(i == i2)cout<<"[";
		else cout<<" ";
		cout<<regs[i];
		if(i == i1)cout<<")";
		else if(i == i2)cout<<"]";
		else cout<<" ";
	}cout<<endl;
}

// static vector<small> combine(){
// 	if(regs[i1] == 0 && regs[i2] == 0){
// 		return vector<small>(1, 0);
// 	}
// 	vector<small> out;
// 	if(auto it = cache.find(make_pair(regs[i1], regs[i2])); it!=cache.end()){
// 		// cout<<"Caching"<<i1<<", "<<i2<<endl;
// 		return (*it).second;
// 	}
// 	for(small combined = regs[i1]+regs[i2];combined!=0;combined/=10){
// 		out.push_back(combined%10);
// 	}
// 	// cache[make_pair(regs[i1], regs[i2])] = out;
// 	return out;
// }
static vector<small> combine(){
	if(regs[i1] == 0 && regs[i2] == 0){
		return vector<small>(1, 0);
	}
	vector<small> out;
	for(small combined = regs[i1]+regs[i2];combined!=0;combined/=10){
		out.push_back(combined%10);
	}
	return out;
}

static void step(){
	auto output = combine();
	// regs.insert(regs.end(), output.rbegin(), output.rend());
	// cout<<"Here"<<endl;
	copy(output.rbegin(), output.rend(), &regs[regsSize]);
	regsSize+=output.size();
	// regs.insert(regs.end(), output.rbegin(), output.rend());
	i1 = (1+i1+regs[i1])%regsSize;
	i2 = (1+i2+regs[i2])%regsSize;
}


int p2(0);
vector<small> match;

static bool isMatch(int pos){
	for(int i = 0;i<match.size();i++){
		if(regs[i+pos] != match[i]){
			return false;
		}
	}
	return true;
}

void p1(){
	for(int copy = inp;copy;copy/=10){
		match.push_back(copy%10);
	}
	reverse(match.begin(), match.end());
		
	while(regsSize<inp+10){
		step();
		if(p2==0 && regsSize>match.size()){
			if(isMatch(regsSize-match.size()))
				p2 = regsSize-match.size();
			if(isMatch(regsSize-match.size()-1))
				p2 = regsSize-match.size();
		}
	}
	cout<<"[P1] ";
	for(int i = inp;i<inp+10;i++){
		cout<<(int)regs[i];
	}cout<<endl;
	while(p2==0){
		step();
		if(p2==0 && regsSize>match.size()){
			if(isMatch(regsSize-match.size()))
				p2 = regsSize-match.size();
			if(isMatch(regsSize-match.size()-1))
				p2 = regsSize-match.size();
		}		
	}
	cout<<"[P2] "<<p2<<endl;
}

int main(){
	fstream file("Day 14/input");
	file>>inp;
	// inp = 2018;
	p1();
}