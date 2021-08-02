#include "../aoc.h"
#include <boost/algorithm/string.hpp>
#include <cassert>

using namespace boost::algorithm;

static inline bool reactants(const char& a, const char& b){
	return abs(a-b)==32;
}

int main(){
	// tests();
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	for(int i = 0; i<line.size()-1;i++){
		if(line[i]==' ') continue;
		for(int j = i+1;j<line.size();j++){
			if(line[j]!=' '){
				if(reactants(line[i], line[j])){
					line[i] = ' ';
					line[j] = ' ';
					i=0;
				}
				break;
			}
		}
	}
	erase_all(line, " ");
	cout<<"[P1] "<<line.size()<<endl;
}