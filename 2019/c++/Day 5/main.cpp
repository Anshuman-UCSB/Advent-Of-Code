#include "../intcode.h"

int main(){
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	IntCode comp(line);
	comp.push(1);
	// comp.debug = true;
	comp.run();
	cout<<"[P1] "<<comp.out.back()<<endl;
	comp = IntCode(line);
	comp.push(5);
	comp.run();
	cout<<"[P2] "<<comp.out.back()<<endl;
}