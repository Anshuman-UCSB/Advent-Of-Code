#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
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

template <class T, class M>
ostream& operator<<(ostream& os, const pair<T, M>& p)
{
	os<<"("<<p.first<<", "<<p.second<<")";
    return os;
}

template <class T, class M>
ostream& operator<<(ostream& os, const map<T, M>& m)
{
	string delim = "";
	os<<"{";
    for(auto& [k, v]: m){
		os<<delim<<k<<": "<<v;
		delim = ", ";
	}os<<"}";
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