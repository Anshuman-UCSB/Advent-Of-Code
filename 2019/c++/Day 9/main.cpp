#include "../intcode.h"

int main(){
	intCode c(readInts(9));
	c.input.push(0);
	c.run();
	c.print();
}