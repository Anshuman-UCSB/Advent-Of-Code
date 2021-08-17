#pragma once

#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

template <class T>
class DisjointSet{
	unordered_map<T, T> parent;
	unordered_map<T, int> rank;
	public:
		void makeSet(const vector<T>& universe);
		T Find(const T& k);
		void Union(const T& a, const T& b);
};

#include "disjointset.cpp"
