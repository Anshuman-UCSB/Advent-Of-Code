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
	vector<int> output;
	queue<int> input;
	int ind;
	bool done;
	bool debug;

	map<int, function<void()>> m;

	intCode(vector<int> inp){
		debug = false;
		regs = inp;
		ind = 0;
		done = false;

		//ADD A+B -> C
		m[1] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] + regs[regs[ind+1]]; ind+=4;}
		);
		m[101] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] + regs[ind+1]; ind+=4;}
		);
		m[1001] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[ind+2] + regs[regs[ind+1]]; ind+=4;}
		);
		m[1101] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[ind+2] + regs[ind+1]; ind+=4;}
		);
		//MULTIPLY A*B -> C
		m[2] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] * regs[regs[ind+1]]; ind+=4;}
		);
		m[102] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[regs[ind+2]] * regs[ind+1]; ind+=4;}
		);
		m[1002] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[ind+2] * regs[regs[ind+1]]; ind+=4;}
		);
		m[1102] = function<void()>(
			[this]()->void{regs[regs[ind+3]] = regs[ind+2] * regs[ind+1]; ind+=4;}
		);
		//READ INPUT -> A
		m[3] = function<void()>(
			[this]()->void{
				if(input.empty()){
					if(debug)
						cout<<"ERROR EMPTY INPUT QUEUE"<<endl;
					throw("empty input queue");
				}
				regs[regs[ind+1]] = input.front(); input.pop(); ind+=2;
			}
		);
		//PUT A -> OUTPUT
		m[4] = function<void()>(
			[this]()->void{
					output.push_back(regs[regs[ind+1]]); ind+=2;
					if(debug){
						cout<<"OUTPUT: "<<output.back()<<endl;
					}
				}
		);
		m[104] = function<void()>(
			[this]()->void{output.push_back(regs[ind+1]); ind+=2;}
		);
		//IF A != 0 ind = B
		m[05] = function<void()>(
			[this]()->void{
				if(regs[regs[ind+1]]){
					ind = regs[regs[ind+2]];
				}else{
					ind+=3;
				}
			}
		);
		m[105] = function<void()>(
			[this]()->void{
				if(regs[ind+1]){
					ind = regs[regs[ind+2]];
				}else{
					ind+=3;
				}
			}
		);
		m[1005] = function<void()>(
			[this]()->void{
				if(regs[regs[ind+1]]){
					ind = regs[ind+2];
				}else{
					ind+=3;
				}
			}
		);
		m[1105] = function<void()>(
			[this]()->void{
				if(regs[ind+1]){
					ind = regs[ind+2];
				}else{
					ind+=3;
				}
			}
		);
		//IF A == 0 ind = B
		m[06] = function<void()>(
			[this]()->void{
				if(regs[regs[ind+1]]==0){
					ind = regs[regs[ind+2]];
				}else{
					ind+=3;
				}
			}
		);
		m[106] = function<void()>(
			[this]()->void{
				if(regs[ind+1]==0){
					ind = regs[regs[ind+2]];
				}else{
					ind+=3;
				}
			}
		);
		m[1006] = function<void()>(
			[this]()->void{
				if(regs[regs[ind+1]]==0){
					ind = regs[ind+2];
				}else{
					ind+=3;
				}
			}
		);
		m[1106] = function<void()>(
			[this]()->void{
				if(regs[ind+1]==0){
					ind = regs[ind+2];
				}else{
					ind+=3;
				}
			}
		);
		//IF A < B 1 -> C
		m[7] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[regs[ind+1]] < regs[regs[ind+2]]; ind+=4;
			}
		);
		m[107] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[ind+1] < regs[regs[ind+2]]; ind+=4;
			}
		);
		m[1007] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[regs[ind+1]] < regs[ind+2]; ind+=4;
			}
		);
		m[1107] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[ind+1] < regs[ind+2]; ind+=4;
			}
		);
		//IF A == B 1 -> C
		m[8] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[regs[ind+1]] == regs[regs[ind+2]]; ind+=4;
			}
		);
		m[108] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[ind+1] == regs[regs[ind+2]]; ind+=4;
			}
		);
		m[1008] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[regs[ind+1]] == regs[ind+2]; ind+=4;
			}
		);
		m[1108] = function<void()>(
			[this]()->void{
					regs[regs[ind+3]] = regs[ind+1] == regs[ind+2]; ind+=4;
			}
		);
		//EXIT
		m[99] = function<void()>(
			[this]()->void{done = true;}
		);

		/*
		//TEMPLATE
		m[CODE] = function<void()>(
			[this]()->void{
				
			}
		);
		*/
			
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