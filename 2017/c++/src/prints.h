#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <type_traits>


#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

using namespace std;
template <size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
    print_tuple(std::ostream&, const std::tuple<T...>&)
{}

template <size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
    print_tuple(std::ostream& os, const std::tuple<T...>& tup)
{
    if (n != 0)
        os << ", ";
    os << std::get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tup)
{
    os << "(";
    print_tuple<0>(os, tup);
    return os << ")";
}


template <class T, class M>
ostream& operator<<(ostream& os, const pair<T, M>& p)
{
	os<<"("<<p.first<<", "<<p.second<<")";
    return os;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	string delim = "";
	os<<"[";
    for(const T& val: v){
		os<<delim<<val;
		delim = ", ";
	}os<<"]";
    return os;
}

template <class T, class M>
ostream& operator<<(ostream& os, const map<T, M>& m)
{
	string delim = "";
	os<<"{";
    for(const auto& [k, v]: m){
		os<<delim<<k<<": "<<v;
		delim = ", ";
	}os<<"}";
    return os;
}


template <class T>
ostream& operator<<(ostream& os, const set<T> s){
	string delim = "";
	os<<"{";
    for(const auto& val: s){
		os<<delim<<val;
		delim = ", ";
	}os<<"}";
    return os;
}