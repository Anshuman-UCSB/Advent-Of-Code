#include <iostream>
#include <fstream>
#include <vector>
#include "../prints.h"
#include <sstream>
#define DECKSIZE 10007
using namespace std;

enum instr{reverse, cut, deal, err};
struct command{
	instr instruction;
	int param;
	command():instruction(err), param(-1){};
	command(string& line){
		stringstream ss(line);
		string temp;
		ss>>temp;
		if(temp == "cut"){
			instruction = cut;
			ss>>param;
		}else if(temp == "deal"){
			ss>>temp;
			if(temp == "into"){
				instruction = reverse;
			}else{
				instruction = deal;
				ss>>temp>>param;
			}
		}
	}

	string str(){
		switch(instruction){
			case reverse:
				return "Reverse deck";
			case cut:
				return "Cut deck with size "+to_string(param); 
			case deal:
				return "Deal with step "+to_string(param);
			default:
				return "ERR";
		}
	}
};
vector<command> instructions;

void p1(){
	int pos = 2019;
	for(auto& ins: instructions){
		switch(ins.instruction){
			case reverse:
				pos = DECKSIZE-1-pos;break;
			case cut:
				pos -= ins.param;
				if(pos<0){
					pos+=DECKSIZE;
				}
				pos%=DECKSIZE;
				break;
			case deal:
				pos = (pos*ins.param)%DECKSIZE;
				break;
		}
	}
	cout<<"[P1] "<<pos<<endl;
}

int main(){
	fstream file("Day 22/input");
	string line;
	while(getline(file, line)){
		instructions.emplace_back(line);
	}
	// for(auto& v: instructions)cout<<v.str()<<endl;
	p1();
}