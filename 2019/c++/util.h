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

#define ll long long
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
using namespace std;

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

template <class T>
ostream& operator<<(ostream& os, const pair<T, T>& p){
	os<<"("<<p.first<<", "<<p.second<<")";
	return os;
}



#endif