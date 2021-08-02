#include "../aoc.h"
#include <boost/algorithm/string.hpp>
#include <cassert>

using namespace boost::algorithm;

static inline bool reactants(const char& a, const char& b){
	return abs(a-b)==32;
}

string recursiveP1(string inp){
	if(inp == "")return inp;
	bool done = true;
	for(int i = 0;i<inp.size()-1;i++){
		if(reactants(inp[i],inp[i+1])){
			done = false;
			inp[i] = ' ';
			inp[i+1] = ' ';
		}
	}
	erase_all(inp, " ");
	return done?inp:recursiveP1(inp);
}

void tests(){
	assert(recursiveP1("dabAcCaCBAcCcaDA")=="dabCBAcaDA");
	assert(recursiveP1("aA")=="");
	assert(recursiveP1("abBA")=="");
}

int main(){
	// tests();
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	cout<<"[P1] "<<recursiveP1(line).size()<<endl;
}