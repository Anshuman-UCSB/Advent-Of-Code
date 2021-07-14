#ifndef INTCODE
#define INTCODE
#include "util.h"
#include <functional>

vector<int> readInts(int day){
	fstream file("Day "+to_string(day)+"/input");
	string line;
	vector<int> out;
	int temp;
	char trash;
	string build;
	while(getline(file, line)){
		build+=line;
	}
	stringstream ss(build);
	while(ss>>temp>>trash){
		out.push_back(temp);
	}
	out.push_back(temp);
	
	return out;
}

struct NoInputError : public exception{
	const char* what() const throw(){
		return "Tried to get input, but none in queue.";
	}
};

class intCode{
	public:	
	vector<int> regs;
	vector<int> output;
	queue<int> input;
	int ind;
	bool done;
	bool debug;

	intCode(vector<int> inp){
		debug = false;
		regs = inp;
		ind = 0;
		done = false;		
	}

	void step(){
		int& instr = regs[ind];
		int opc = instr%100;
		if(debug)
			cout<<"Running command "<<opc<<" from position "<<ind<<"."<<endl;
		if(opc == 99){
			done = true;
			return;
		}
		if(opc == 1 ||opc == 2){
			int a, b;
			a = getParam(instr, 1);
			b = getParam(instr, 2);
			
			if(debug)
				cout<<"has arguments "<<a<<" and "<<b<<endl;
			switch(opc){
				case 1:
					regs[regs[ind+3]] = a+b;
					break;
				case 2:
					regs[regs[ind+3]] = a*b;
					break;
			}
			ind+=4;
		}
		else if(opc == 3){
			if(input.empty()){
				throw NoInputError();
				return;
			}
			if(debug){
				cout<<"[DEBUG] reading input "<<input.front()<<" to "<<regs[ind+1]<<endl;
			}
			regs[regs[ind+1]] = input.front();
			input.pop();
			ind+=2;
		} else if(opc == 4){
			int out = getParam(instr, 1);
			output.push_back(out);
			if(debug){
				cout<<"Output: "<<out<<endl;
			}
			ind+=2;
		} else if(opc == 5 || opc == 6){
			int a, b;
			a = getParam(instr, 1);
			b = getParam(instr, 2);
			switch(opc){
				case 5:
					if(a)
						ind = b;
					else
						ind+=3;
					break;
				case 6:
					if(!a)
						ind = b;
					else
						ind+=3;
					break;
			}
		} else if(opc == 7 || opc == 8){
			int a, b, c;
			a = getParam(instr, 1);
			b = getParam(instr, 2);
			c = regs[ind+3];
			if(debug){
				cout<<"OPCODE "<<opc<<" with args "<<a<<" "<<b<<" "<<c<<endl;
			}
			switch(opc){
				case 7:
					regs[c] = a<b;
					break;
				case 8:
					// cout<<"testing: "<<regs[c]<<endl;
					regs[c] = a==b;
					// cout<<"testing: "<<regs[c]<<endl;
					break;
			}
			ind+=4;
		} else{
			throw("Unknown opcode");
		}
	}

	void run(){
		while(!done){
			if(debug)
				print();
			step();
		}
	}

	void print(){
		cout<<"    Regs:"<<endl;
		string delim = "";
		for(int i = max(0, ind-1);i<min(int(regs.size()), ind+5);i++){
			if(i == ind)
				cout<<delim<<"("<<regs[i]<<")";
			else
				cout<<delim<<regs[i];
			delim = ", ";
		}cout<<endl;
		if(!input.empty()){
			cout<<"    Inputs:"<<endl;
			cout<<"Queue of size "<<input.size()<<" (front: "<<input.front()<<")"<<endl;
		}
		if(done){
			cout<<"DONE"<<endl;
		}		
	}

	private:
	int getParam(int instr, int pos){
		instr/=10;
		for(int i = 0;i<pos;i++){
			instr/=10;
		}
		
		if(instr%10==1) //immediate mode
			return regs[ind+pos];
		else //relative mode
			return regs[regs[ind+pos]];
	}

};


#endif