#ifndef INTCODE
#define INTCODE
#include "util.h"
#include <functional>

vector<long long> readInts(int day){
	fstream file("Day "+to_string(day)+"/input");
	string line;
	vector<long long> out;
	long long temp;
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
	vector<long long> regs;
	vector<long long> output;
	queue<long long> input;
	int ind;
	int rel;
	bool done;
	bool debug;

	intCode(vector<long long> inp){
		debug = false;
		regs = inp;
		ind = rel = 0;
		done = false;		
	}

	void step(){
		long long& instr = regs[ind];
		long long opc = instr%100;
		if(debug)
			cout<<"Running command "<<opc<<" from position "<<ind<<"."<<endl;
		if(opc == 99){
			done = true;
			return;
		}
		if(opc == 1 ||opc == 2){
			long long a, b;
			a = getParam(instr, 1);
			b = getParam(instr, 2);
			
			if(debug)
				cout<<"has arguments "<<a<<" and "<<b<<endl;
			switch(opc){
				case 1:
					setParam(instr, 3, a+b);
					break;
				case 2:
					setParam(instr, 3, a*b);
					break;
			}
			ind+=4;
		}
		else if(opc == 3){
			// int a = getAddr(instr, 1);
			if(input.empty()){
				throw NoInputError();
				return;
			}
			if(debug){
				cout<<"[DEBUG] reading input "<<input.front()<<endl;
				// print();
				
			}
			setParam(instr, 1, input.front());
			// regs[a] = input.front();
			input.pop();
			ind+=2;
		} else if(opc == 4){
			long long out = getParam(instr, 1);
			output.push_back(out);
			if(debug ||  1){
				cout<<"Output: "<<out<<endl;
				print();
			}
			ind+=2;
		} else if(opc == 5 || opc == 6){
			long long a, b;
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
			long long a, b;
			a = getParam(instr, 1);
			b = getParam(instr, 2);
			if(debug || 1){
				cout<<"OPCODE "<<opc<<" with args "<<a<<" "<<b<<" "<<endl;
				print();
			}
			switch(opc){
				case 7:
					setParam(instr, 3, a<b);
					break;
				case 8:
					// cout<<"testing: "<<regs[c]<<endl;
					setParam(instr, 3, a==b);
					// cout<<"testing: "<<regs[c]<<endl;
					break;
			}
			ind+=4;
		}else if(opc == 9){
			// print();
			long long a = getParam(instr, 1);
			if(debug ){
				cout<<"Changing rel base by "<<a<<" ("<<rel<<"+"<<a<<"="<<rel+a<<")"<<endl;
			}
			rel+=a;
			ind+=2;
		}else{
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
		cout<<endl;
		cout<<"+     Pointers: ("<<ind<<", "<<rel<<")"<<endl;
		cout<<"+     Regs:"<<endl;
		string delim = "";
		cout<<"+ ";
		for(int i = max(0, ind-4);i<min(int(regs.size()), ind+5);i++){
			if(i == ind)
				cout<<delim<<"("<<regs[i]<<")";
			else
				cout<<delim<<regs[i];
			delim = ", ";
		}cout<<endl;
		if(!input.empty()){
			cout<<"+ ";
			cout<<"    Inputs:"<<endl;
			cout<<"+ ";
			cout<<"Queue of size "<<input.size()<<" (front: "<<input.front()<<")"<<endl;
		}
		if(!output.empty()){
			cout<<"+ ";
			cout<<"    Outputs:"<<endl;
			cout<<"+ ";
			cout<<output<<endl;
		}
		if(done){
			cout<<"+ ";
			cout<<"    DONE"<<endl;
		}
	}

	private:

	int getParamType(long long instr, const int& pos){
		instr/=10;
		for(int i = 0;i<pos;i++){
			instr/=10;
		}
		return instr%10;
	}

	void setParam(long long instr, int pos, const long long& val){
		int type = getParamType(instr, pos);
		
		if(type==1) //immediate mode
			throw("write to immediate???");
		else if(type == 2)
			regs[rel+regs[ind+pos]] = val;
		else //relative mode
			regs[regs[ind+pos]] = val;
	}

	long long getParam(long long instr, int pos){
		int val = getParamType(instr, pos);
		
		if(val==1) //immediate mode
			return regs[ind+pos];
		else if(val == 2)
			return regs[rel+regs[ind+pos]];
		else //relative mode
			return regs[regs[ind+pos]];
	}

};


#endif