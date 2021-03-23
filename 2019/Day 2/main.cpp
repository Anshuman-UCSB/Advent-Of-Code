#include "../intcode.h"

void part2(){
	vector<int> raw = readInts();
	for(int i = 0;i<100;i++){
		for(int j = 0;j<100;j++){
			raw[1] = i;
			raw[2] = j;
			intCode comp(raw);
			comp.run();
			if(comp.regs[0] == 19690720){
				cout<<"Part 2: "<<100*i+j<<endl;
			}
		}
	}
}

int main(){
	vector<int> raw = readInts();
	raw[1] = 12;
	raw[2] = 2;
	intCode comp(raw);
	comp.print();
	while(comp.done == false){
		comp.step();
		comp.print();
	}
	comp.print();
	part2();
}

