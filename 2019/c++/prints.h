#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v){
	cout<<"[";
	string delim = "";
	for(auto val: v){
		cout<<delim<<val;
		delim = ", ";
	}cout<<"]";
	return os;
}

template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p){
	cout<<"("<<p.first<<", "<<p.second<<")";
	return os;
}
template <class T>
ostream& operator<<(ostream& os, const set<T>& s){
	cout<<"{";
	string delim = "";
	for(auto& val: s){
		cout<<delim<<val;
		delim = ", ";
	}cout<<"}";
	return os;
}

// void cls(){
// 	cout<<"\033[2J";
// }

template <class T, class M>
std::ostream & operator <<(std::ostream &os, const std::map<T, M> &m)
{
    for (const auto &p : m)
    {
        os << p.first << ": ";
		os << p.second;
        os << std::endl;
    }

    return os;
}