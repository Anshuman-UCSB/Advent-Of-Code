#include "../intcode.h"

int main(){
	intCode comp(readInts(5));
	comp.debug = true;
	comp.input.push(8);
	comp.run();
}