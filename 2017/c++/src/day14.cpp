#include "AOC.h"
#include "knothash.h"

chrono::time_point<std::chrono::steady_clock> day14(input_t& inp){
	string& base = inp[0];
	base.append("-");
	map<pii, int> groups;
	int id = 0;
	for(int y = 0;y<128;y++){
		string h = knothash(base+to_string(y));
		for(int x = 0;x<32;x++){
			switch(h[x]){
				case '0': break;
				case '1': 
					groups[pii(x*4+3, y)] = id++;
					break;
				case '2': 
					groups[pii(x*4+2, y)] = id++;
					break;
				case '3': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+2, y)] = id++;
					break;
				case '4': 
					groups[pii(x*4+1, y)] = id++;
					break;
				case '5': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					break;
				case '6': 
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					break;
				case '7': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					break;
				case '8': 
					groups[pii(x*4+0, y)] = id++;
					break;
				case '9': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'a': 
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'b': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'c': 
					groups[pii(x*4+1, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'd': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'e': 
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
				case 'f': 
					groups[pii(x*4+3, y)] = id++;
					groups[pii(x*4+2, y)] = id++;
					groups[pii(x*4+1, y)] = id++;
					groups[pii(x*4+0, y)] = id++;
					break;
			}
		}
	}

	// for(int y = 0;y<8;y++){
	// 	for(int x = 0;x<8;x++){
	// 		cout<<(groups.count(pii(x,y))?'#':'.');
	// 	}cout<<endl;
	// }
	DisjointSet<int> ds;
	vector<int> universe(id);
	iota(universe.begin(), universe.end(), 0);
	ds.makeSet(universe);
	for(int y = 0;y<128;y++){
		for(int x = 0;x<128;x++){
			if(!groups.count(pii(x,y))) continue;
			if(x){
				if(groups.count(pii(x-1,y)))
					ds.Union(groups[pii(x-1, y)], groups[pii(x,y)]);
			}
			if(y){
				if(groups.count(pii(x,y-1)))
					ds.Union(groups[pii(x, y-1)], groups[pii(x,y)]);
			}
		}
	}
	
	set<int> unq;
	for(auto& [ignore, id]: groups)
		unq.insert(ds.Find(id));
	int p2 = unq.size();
	
	int p1 = groups.size();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}