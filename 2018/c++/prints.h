#pragma once

#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	string delim = "";
	os<<"[";
    for(auto& val: v){
		os<<delim<<val;
		delim = ", ";
	}os<<"]";
    return os;
}


template <class T>
ostream& operator<<(ostream& os, const set<T>& s){
	string delim = "";
	os<<"{";
    for(auto& val: s){
		os<<delim<<val;
		delim = ", ";
	}os<<"}";
    return os;
}