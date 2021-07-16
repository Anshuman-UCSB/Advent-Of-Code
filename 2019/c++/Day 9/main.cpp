#include "../intcode.h"

void tests(){
	// IntCode t("109, -1, 4, 1, 99");
	// t.run();
	// cout<<t.out<<endl;
	// assert(t.out == vector<ll>{-1});
	assert(testOutput("109, -1, 4, 1, 99", vector<ll>{-1}));
	assert(testOutput("109, -1, 104, 1, 99", vector<ll>{1}));
	assert(testOutput("109, -1, 204, 1, 99", vector<ll>{109}));
	assert(testOutput("109, 1, 9, 2, 204, -6, 99", vector<ll>{204}));
	assert(testOutput("109, 1, 109, 9, 204, -6, 99", vector<ll>{204}));
	assert(testOutput("109, 1, 209, -1, 204, -106, 99", vector<ll>{204}));
	assert(testOutput("109, 1, 3, 3, 204, 2, 99", vector<ll>{-4289}, vector<ll>{-4289}));
	assert(testOutput("109, 1, 203, 2, 204, 2, 99", vector<ll>{-4289}, vector<ll>{-4289}));
	cout<<GREEN<<BOLD<<"All tests passed."<<RESET<<endl;
}

int main(){
	// tests();
	IntCode c(9);
	c.push(2);
	c.run();
	c.print();
}