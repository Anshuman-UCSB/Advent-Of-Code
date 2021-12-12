	#include "AOC.h"
	#include <bitset>
	#include <tuple>

	chrono::time_point<std::chrono::steady_clock> day12(input_t& inp){
		int p1(0), p2(0);
		map<string, int> index;
		int s(2), b(10);
		vector<vector<int>> adj(20, vector<int>());
		for(auto& l: inp){
			size_t p = l.find('-');
			vector<string> edge = {l.substr(0, p), l.substr(p+1)};
			for(auto& v: edge){
				if(!index.count(v)){
					if(v == "start")
						index[v] = 0;
					else if(v == "end")
						index[v] = 1;
					else if(islower(v[0]))
						index[v] = s++;
					else
						index[v] = b++;
				}
			}
			if(edge[1]!="start")
				adj[index[edge[0]]].push_back(index[edge[1]]);
			if(edge[0]!="start")
				adj[index[edge[1]]].push_back(index[edge[0]]);
		}
		bitset<10> visited;
		int pos;
		bool dvisit;
		stack<tuple<int, bitset<10>, bool>> st({make_tuple(0, visited, false)});
		while(!st.empty()){
			tie(pos, visited, dvisit) = st.top();
			st.pop();
			if(pos == 1){ //end
				if(!dvisit)
					p1++;
				p2++;
				continue;
			}
			for(auto& v: adj[pos]){
				if(v<10){ //small cave
					if(visited[v]){
						if(dvisit == false)
							st.push(make_tuple(v, visited, true)); //if already visited cave, but hasn't revisited, continue p2
					}else{
						bitset<10> t = visited;
						t[v]=1;
						st.push(make_tuple(v, t, dvisit));
					}
				}else
					st.push(make_tuple(v, visited, dvisit));
			}	
		}
		auto done = chrono::steady_clock::now();
		cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
		return done;
	}