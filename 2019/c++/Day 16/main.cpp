#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include "../prints.h"
#include "../timing.h"
#include <chrono>

using namespace std;
vector<int> basePattern = {0,1,0,-1};
// Timer t;

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
unsigned int r2Size =0;
void phase2(vector<int>& regs, int& loc){
	if(r2Size == 0){
		r2Size = regs.size();
	}
	for(int i = r2Size-2;i>=loc;i--){
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
	regs2.reserve(regs.size()*10000);
	for(int i =0;i<10000;i++){
		regs2.insert(regs2.end(), regs.begin(), regs.end());
	}
	for(int i =0 ;i<100;i++){
		phase(regs);
		phase2(regs2, loc);
	}
	cout<<"[P1] ";
	for(int i =0;i<8;i++){
		cout<<regs[i];
	}cout<<endl;
	cout<<"[P2] ";
	for(int i =loc;i<loc+8;i++){
		cout<<regs2[i];
	}cout<<endl;
	// t.total();
}