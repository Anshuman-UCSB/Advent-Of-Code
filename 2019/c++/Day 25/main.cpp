#include "../intcode.h"
#include <bitset>

IntCode c(25);

void printOutput(){
	for(char ch: c.out)cout<<ch;
	string inp;
	c.out.clear();
}

void takeInput(){
	string inp;
	getline(cin, inp);
	for(int ch: inp) {
		c.push(ch);
	}
	c.push(10);
}

void runUntilInput(){
	while(!c.done){
		if(c.regs[c.ind] % 100 == 3 && c.inp.empty()){
			return;
		}
		c.step();
	}
}

void p1(){
	fstream file("Day 25/pickup.txt");
	string line;
	while(getline(file, line)){
		for(char ch: line)
			c.push(ch);
		c.push(10);
	}
	
	runUntilInput();

	bitset<8> perms;
	map<int, string> items = {
		{0,"polygon"},
		{1,"fixed point"},
		{2,"astronaut ice cream"},
		{3,"easter egg"},
		{4,"dark matter"},
		{5,"food ration"},
		{6,"asterisk"},
		{7,"weather machine"}
	};
	int num = 0;
	
	string instr;
	while(!perms.all()){
		perms = bitset<8>(num++);
		for(int i = 0;i<8;i++){
			if(perms[i])
				instr = "take "+items[i]+"\n";
			else
				instr = "drop "+items[i]+"\n";
			for(auto& ch: instr) c.push(ch);
		}
		instr="north\n";
		for(auto& ch: instr) c.push(ch);
		c.out.clear();
		runUntilInput();
		if(c.done){
			break;
		}
	}
	int startPos = 648;
	cout<<"[P1] ";
	for(int i =startPos;i<startPos+9;i++){
		cout<<char(c.out[i]);
	}cout<<endl;
	exit(1);
}

int main(){
	p1();
	// while(!c.done){
	// 	if(c.regs[c.ind] % 100 == 3 && c.inp.empty()){
	// 		for(char ch: c.out)cout<<ch;
	// 		string inp;
	// 		getline(cin, inp);
	// 		for(int ch: inp) {
	// 			// cout<<"["<<ch<<"]";
	// 			c.push(ch);
	// 		}
	// 		c.push(10);
	// 		c.out.clear();
	// 	}
	// 	c.step();
	// }
}