#include "../intcode.h"

void p1(){
	IntCode cpu(21);
	string code;
	code += "OR A J\n";
	code += "AND B J\n";
	code += "AND C J\n";
	code += "NOT J J\n";
	code += "AND D J\n";
	code += "WALK\n";
	
	for(auto c: code){
		cpu.push(c);
	}
	cpu.run();
	cout<<"[P1] "<<cpu.out.back()<<endl;
}

void p2(){
	IntCode cpu(21);
	string code;
	fstream file("Day 21/code");
	string line;
	while(getline(file, line)){
		for(int c: line){
			cpu.push(c);
		}
		cpu.push(10);
	}
	cpu.run();
	// for(auto c: cpu.out)cout<<char(c);
	cout<<"[P2] "<<cpu.out.back()<<endl;
}

int main(){
	p1();
	p2();
}