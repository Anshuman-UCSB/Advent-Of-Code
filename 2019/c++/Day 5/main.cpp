#include "../intcode.h"

int main(){
	intCode comp(readInts(5));
	// comp.debug = true;
	comp.input.push(5);
	comp.run();
	cout<<"Part 2: "<<comp.output[0]<<endl;
}