#ifndef UTIL
#define UTIL

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <utility>

using namespace std;

vector<string> readInput(int day){
	vector<string> out;
	fstream file("Day "+to_string(day)+"/input");
	string line;
	while(getline(file, line)){
		if(line.back() == '\r'){
			line.pop_back();
		}
		out.emplace_back(line);
	}
	return out;
}

bool isIn(const char &a,const string &b){
	for(auto c: b){
		if(a == c){
			return true;
		}
	}
	return false;
}

template <class T>
bool isIn(const T &a,const vector<T> &b){
	for(auto c: b){
		if(a == c){
			return true;
		}
	}
	return false;
}

vector<string> tokenize(string& inp, string delims){
	vector<string> out;
	out.emplace_back();
	for(auto& c: inp){
		if (isIn(c, delims)){
			out.emplace_back();
		}else{
			out.back().push_back(c);
		}
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