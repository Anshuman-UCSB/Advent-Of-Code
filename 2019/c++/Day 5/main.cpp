#include "../intcode.h"

int main(){
	intCode comp(readInts(5));
	// comp.debug = true;
	comp.input.push(1);
	comp.run();
	cout<<"Part 1: "<<comp.output<<endl;
}