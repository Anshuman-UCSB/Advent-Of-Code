	#include "AOC.h"

	int flood(vector<vector<char>>& m, int x, int y){
		set<pii> visited;
		queue<pii> q;
		q.push(pii(x,y));
		while(!q.empty()){
			pii top = q.front();
			auto [i, j] = top;
			q.pop();
			if(visited.count(top) || m[j][i] == '9')
				continue;
			visited.insert(pii(i,j));
			m[j][i] = '9';
			if(i>0)
				q.push(pii(i-1, j));
			if(i<m[0].size()-1)
				q.push(pii(i+1, j));
			if(j>0)
				q.push(pii(i, j-1));
			if(j<m.size()-1)
				q.push(pii(i, j+1));
		}
		return visited.size();
	}

	chrono::time_point<std::chrono::steady_clock> day09(input_t& inp){
		int p1(0), p2(0);

		vector<vector<char>> m;
		for(auto& l: inp){
			m.emplace_back();
			for(char c: l){
				m.back().push_back(c);
			}
		}
		
		for(int y = 0;y<m.size();y++){
			for(int x = 0;x<m[0].size();x++){
				char c = m[y][x];
				if(x>0)
					if(m[y][x-1]<=c) continue;
				if(x<m[0].size()-1)
					if(m[y][x+1]<=c) continue;
				if(y>0)
					if(m[y-1][x]<=c) continue;
				if(y<m.size()-1)
					if(m[y+1][x]<=c) continue;
				p1+=c-'0'+1;
			}
		}
		vector<int> floods;
		for(int y = 0;y<inp.size();y++){
			for(int x = 0;x<m[0].size();x++){
				if(m[y][x] != '9'){
					floods.push_back(flood(m, x, y));
				}
			}
		}
		sort(floods.begin(), floods.end(), greater<int>());
		p2 = floods[0]*floods[1]*floods[2];
		auto done = chrono::steady_clock::now();
		cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
		m.clear();
		return done;
	}