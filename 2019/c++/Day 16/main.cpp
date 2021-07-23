#include <iostream>
#include <vector>
#include <fstream>
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

int main(){
	fstream file("Day 16/input");
	string line;
	getline(file,line);
	vector<int> regs(line.size());
	for(int i =0 ;i<line.size();i++){
		regs[i] = line[i]-'0';
	}
	for(int i =0 ;i<100;i++){
		phase(regs);
	}
	cout<<"[P1] ";
	for(int i =0;i<8;i++){
		cout<<regs[i];
	}cout<<endl;
}