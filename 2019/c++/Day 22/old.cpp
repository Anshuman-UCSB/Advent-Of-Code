#include <iostream>
#include <utility>
#include <map>
#include <fstream>
#include <vector>
#include "../prints.h"
#include <sstream>
#include <unistd.h>
#define DECKSIZE 10007
#define DECKSIZE2 119315717514047
#define SHUFFLES 101741582076661
#define ull unsigned long long
#define ll long long
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

map<ull, pair<ull, ull>> cache; // {a -> {b, found at ind i}}
map<ull, ull> loops; //pos, period

void p2(){
	ull pos = 2019;
	const ull size = DECKSIZE;
	ll a(1), b(0); //ax+b % size
	for(auto& ins: instructions){
		switch(ins.instruction){
			case reverse:
				a*=-1; b=size-1-b; break;
			case deal:
				a*=ins.param; b*=ins.param; break;
			case cut:
				b-=ins.param; break;
		}
		b%=size;
	}
	cout<<a<<"x + "<<b<<endl;
	pos = (a*pos+b)%size;
	if(pos<0) pos+=size;
	cout<<"[P2] "<<pos<<endl;
}

int main(){
	fstream file("Day 22/input");
	string line;
	while(getline(file, line)){
		instructions.emplace_back(line);
	}
	// for(auto& v: instructions)cout<<v.str()<<endl;
	p1();
	p2();
} //9800 too low