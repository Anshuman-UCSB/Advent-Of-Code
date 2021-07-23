#include <iostream>
#include "../intcode.h"
#include "../prints.h"
#include "../coord.h"
#include <stack>
#include <queue>
#include <cassert>

struct maze{
	Coord p;
	Coord oxy;
	stack<int> path;
	map<Coord, int> m;
	IntCode c;
	map<int, Coord> dirMap;
	map<int, string> mapping;

	maze(){
		mapping['D'] = "D";
		mapping['#'] = "█";
		mapping['.'] = ".";
		mapping['O'] = "O";
		mapping['?'] = "?";
		mapping[' '] = " ";
		dirMap[1] = Coord(0,1);
		dirMap[2] = Coord(0,-1);
		dirMap[3] = Coord(-1, 0);
		c = IntCode(15);
		dirMap[4] = Coord(1, 0);

		run();
	}

	pair<bool, int> hasNeighbor(){
		for(int i = 1;i<=4;i++){
			if(m.count(p+dirMap[i])==0){
				return make_pair(true, i);
			}
		}
		// string trash;
		// cin>>trash;
		return make_pair(false, 0);
	}

	void cls(){
		cout<< "\033[2J";
	}

	void reverseBFS(){
		queue<Coord> q;
		Coord t;
		q.push(oxy);
		while(!q.empty()){
			t = q.front();
			q.pop();
			for(auto& mod: dirMap){
				if(m[t+mod.second]=='.'){
					m[t+mod.second] = m[t] != 'O'?m[t]+1:1000;
					q.push(t+mod.second);
				}
			}
		}
	}

	int run(){
		m[p] = '.';
		
		bool done = false;
		int dir;
		
		bool exploring;
		while(!done){
			if(c.regs[c.ind]%100 == 3){
				if(c.inp.empty()){
					auto instr = hasNeighbor();
					if(instr.first){
						dir = instr.second;
						exploring = true;
					}
					else{
						exploring = false;
						int t = path.top();
						dir = (t==1 || t == 3)?t+1:t-1; //get opposite dir
						path.pop();
					}
					c.push(dir);
				}
			}
			if(!c.out.empty()){
				assert(c.out.size() == 1);
				int resp = c.pop();
				switch(resp){
					case 0: m[p+dirMap[dir]] = '#'; break;
					case 1: p+=dirMap[dir]; m[p] = '.';
							if(exploring) path.push(dir);break;
					case 2: p+=dirMap[dir]; m[p] = 'O';path.push(dir);
							oxy = p;
							string found;
				}
				// cls();
				// printGrid(m, mapping);
			}
			c.step();
			if(path.size() == 0 && m.size() > 5){
				done = true;
			}
		}

		reverseBFS();
		cout<<"[P1] "<<m[Coord(0,0)]-999<<endl;
		int p2 = 0;
		for(auto& p: m){
			p2 = max(p2, p.second);
		}
		cout<<"[P2] "<<p2-999<<endl;
	}
};

int main(){
	maze();
}