#include "../intcode.h"
#include <fstream>
#include <cassert>

void assertions(){
	IntCode comp("1,1,1,4,99,5,6,0,99", false);
	comp.run();
	assert(comp.regs[0] == 30);

	cout<<"[ASSERTIONS] all cases passed!"<<endl;	
}

int main(){
	// assertions();
	fstream file("Day 2/input");
	string line;
	getline(file, line);
	IntCode comp(line, false);
	comp.regs[1] = 12;
	comp.regs[2] = 2;
	comp.push(4);
	comp.run();
	cout<<"[P1] "<<comp.regs[0]<<endl;

	for(int n = 0;;n++){
		for(int v = 0;v<100;v++){
			comp = IntCode(line, false);
			comp.regs[1] = n;
			comp.regs[2] = v;
			comp.run();
			if(comp.regs[0] == 19690720){
				cout<<"[P2] "<<n*100+v<<endl;
				return 1;
			}
		}
	}

}

