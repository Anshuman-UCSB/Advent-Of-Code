#pragma once

#include <iostream>
#include <vector>
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
