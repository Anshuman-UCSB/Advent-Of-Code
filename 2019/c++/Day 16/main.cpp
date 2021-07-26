#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include "../prints.h"

using namespace std;
vector<int> basePattern = {0,1,0,-1};

int calcPattern(vector<int>& regs, int ind){
	int remaining=ind;
	int pind = 0; //pattern ind
	int out=0;
	for(int i = 0;i<regs.size();i++){
		if(remaining-- == 0){
			remaining=ind;
			pind++;
			pind%=basePattern.size();
		}
		// cout<<"out+="<<regs[i]<<"*"<<basePattern[pind]<<endl;
		out+=regs[i]*basePattern[pind];
	}
	// cout<<endl;
	return abs(out%10);
}

void phase(vector<int>& regs){
	vector<int> out(regs.size());
	for(int i = 0;i<regs.size();i++){
		out[i] = calcPattern(regs, i);
	}
	regs = out;
}

void phase2(vector<int>& regs){
	for(int i = regs.size()-2;i>regs.size()/2;i--){
		regs[i] = (regs[i]+regs[i+1])%10;
	}
}

int main(){
	fstream file("Day 16/input");
	string line;
	getline(file,line);
	int loc = stoi(line.substr(0,7));
	vector<int> regs(line.size());
	for(int i =0 ;i<line.size();i++){
		regs[i] = line[i]-'0';
	}
	assert(loc > regs.size()*5000);
	vector<int> regs2;
	// for(int i =0;i<1;i++){
	for(int i =0;i<10000;i++){
		regs2.insert(regs2.end(), regs.begin(), regs.end());
	}
	for(int i =0 ;i<100;i++){
		phase(regs);
		phase2(regs2);
		// cout<<i+1<<": ";
		// for(auto& c: regs2){
		// 	cout<<c;
		// }cout<<endl;
	}
	cout<<"[P1] ";
	for(int i =0;i<8;i++){
		cout<<regs[i];
	}cout<<endl;
	cout<<"[P2] ";
	// cout<<regs2.size()<<endl;
	// cout<<loc<<endl;
	for(int i =loc;i<loc+8;i++){
		cout<<regs2[i];
	}cout<<endl;
}