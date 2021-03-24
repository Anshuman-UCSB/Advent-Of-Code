#ifndef INTCODE
#define INTCODE
#include "util.h"
#include <functional>

vector<int> readInts(int day){
	fstream file("Day "+to_string(day)+"/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	vector<int> out;
	int temp;
	char trash;
	while(ss>>temp>>trash){
		out.push_back(temp);
	}
	out.push_back(temp);
	return out;
}

class intCode{
	public:	
	vector<int> regs;
	int ind;
	bool done;

	map<int, function<void()>> m;

	intCode(vector<int> inp){
		regs = inp;
		ind = 0;
		done = false;

		m[1] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] + regs[regs[ind+1]]; ind+=4;}
		);
		m[2] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] * regs[regs[ind+1]]; ind+=4;}
		);
		m[99] = function<void()>(
			[this]()->void{done = true;}
		);
			
	}

	void step(){
		int& opcode = regs[ind];
		m[opcode]();	
	}

	void run(){
		while(!done){
			step();
		}
	}

	void print(){
		cout<<"    Regs:"<<endl;
		string delim = "";
		for(int i = 0;i<regs.size();i++){
			if(i == ind)
				cout<<delim<<"("<<regs[i]<<")";
			else
				cout<<delim<<regs[i];
			delim = ", ";
		}cout<<endl;
		if(done){
			cout<<"DONE"<<endl;
		}
	}
};


#endif