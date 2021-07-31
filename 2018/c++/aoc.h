#pragma once
#include "timing.h"
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <tuple>

#define ll long long
#define ull unsigned long long

vector<string> readInput(int day){
	fstream file("Day "+to_string(day)+"/input");
	string line;
	vector<string> out;
	while(getline(file, line))
		out.push_back(line);
	return out;
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& t)
{
    os<<"[";
	string delim = "";
	for(const auto& v: t){
		os<<delim<<v;
		delim = ", ";
	}
    os<<"]";
	return os;
}

template<class T, class M>
ostream& operator<<(ostream& os, const map<T, M>& m)
{
    os<<"{";
	string delim = "";
	for(auto p: m){
		// T k; M v;
		auto [k, v] = p;
		os<<delim<<k<<": "<<v;
		delim = ", ";
	}
    os<<"}";
	return os;
}
