#include "AOC.h"
#include "unionfind.h"

chrono::time_point<std::chrono::steady_clock> day12(input_t& inp){
	DisjointSet ds;
	vector<int> universe(2000);
	iota(universe.begin(), universe.end(), 0);
	ds.makeSet(universe);
	for(auto& l: inp){
		stringstream ss(l);
		int parent, child;
		string tr;
		ss>>parent>>tr;
		while(ss>>child){
			ds.Union(parent, child);
			ss>>tr;
		}
	}
	
	set<int> groups;
	int p1 =0;
	int g1 = ds.Find(0);
	for(auto& v: universe){
		if(ds.Find(v) == g1){
			p1++;
		}
		groups.insert(ds.Find(v));
	}
	int p2 = groups.size();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}