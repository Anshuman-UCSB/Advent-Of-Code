#ifndef UTIL
#define UTIL

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

vector<string> readInput(){
	vector<string> out;
	fstream file("input");
	string line;
	while(getline(file, line)){
		out.emplace_back(line);
	}
	return out;
}

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v){
	cout<<"[";
	string delim = "";
	for(auto& val: v){
		cout<<delim<<val;
		delim = ", ";
	}cout<<"]";
	return os;
}

#endif