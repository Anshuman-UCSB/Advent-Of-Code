#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "../prints.h"
#include "../intcode.h"
#include <utility>
#include "../coord.h"
using namespace std;

void feedInput(string& inp, IntCode& c){
	for(auto& v: inp){
		c.push(int(v));
	}
}

string solvePath(vector<string>& m, Coord& start){
	string out = "";
	
	vector<Coord> dirMod;
	int dir = 0;
	dirMod.emplace_back(0,-1);
	dirMod.emplace_back(1,0);
	dirMod.emplace_back(0,1);
	dirMod.emplace_back(-1,0);
	//   0
	// 3 + 1	if new > old, turn right; vice versa.
	//   2
	Coord t;
	// for(int i = 0;i<dirMod.size();i++){
	// 	t = start+dirMod[i];
	// 	if(m[t.y][t.x] == '#'){
	// 		if((dir+1)%4==i){
	// 			out+="R,";
	// 			dir = i;
	// 		}else if(i!=dir){
	// 			out+="L,";
	// 			dir = i;
	// 		}
	// 	}
	// }

	// //write straight until cant
	// int dist = -1;
	// Coord pos = start;
	// while(m[pos.y][pos.x]!='.'){
	// 	dist++;
	// 	pos+=dirMod[dir];
	// 	cout<<pos<<endl;
	// }
	// pos-=dirMod[dir];
	// out+=to_string(dist);
	// out+=",";
	int dist;
	Coord pos = start;
	//find next dir
	int d1, d2;
	bool done = false;
	while(!done){
		done = true;
		d1 = (dir+3)%4;
		d2 = (dir+1)%4;
		try{
			t = pos+dirMod[d1];
			if(m.at(t.y).at(t.x) == '#'){
				out+="L,";
				dir = d1;
				done = false;
			}
		}catch(const std::out_of_range &e){}
		try{
			t = pos+dirMod[d2];
			if(m.at(t.y).at(t.x) == '#'){
				out+="R,";
				dir = d2;
				done = false;
			}
		}catch(const std::out_of_range &e){}
		if(done){
			break;
		}
		dist = -1;
		try{
			while(m.at(pos.y).at(pos.x)!='.'){
				dist++;
				pos+=dirMod[dir];
			}
		}catch(const std::out_of_range &e){}
		pos-=dirMod[dir];
		out+=to_string(dist);
		out+=",";
	}
	
	out.pop_back();
	return out;
}

void hand(){
	IntCode comp(17);
	comp.regs[0] = 2;
	string temp = "A,B,A,C,A,A,C,B,C,B\n";
	for(auto c: temp){
		comp.push(int(c));
	}
	temp = "L,12,L,8,R,12\n";
	for(auto c: temp){
		comp.push(int(c));
	}
	temp = "L,10,L,8,L,12,R,12\n";
	for(auto c: temp){
		comp.push(int(c));
	}
	temp = "R,12,L,8,L,10\n";
	for(auto c: temp){
		comp.push(int(c));
	}
	comp.push(int('n'));
	comp.push(int('\n'));
	cout<<comp.inp<<endl;
	comp.run();
	cout<<"[P2] "<<comp.out.back()<<endl;
	exit(1);
}

int main(){
	hand();
	IntCode c(17);
	vector<string> m;
	// c.regs[0] = 2;
	c.run();
	m.emplace_back();
	Coord start;
	for(auto v: c.out){
		switch(v){
			case 10:
				m.emplace_back(); break;
			default:
				if(v != 35 && v!=46){
					start = Coord(m.back().size(), m.size()-1);
				}
				m.back().push_back(v);break;
		}
	}
	c.out.empty();
	// cout<<start<<endl;
	

	for(auto& r: m){
		cout<<r<<endl;
	}
	long long p1=0;
	
	for(int y=1;y<m.size()-1;y++){
		for(int x=1;x<m[0].size()-1;x++){
			if(m[y][x]  == '#' &&
			   m[y+1][x]== '#' &&
			   m[y-1][x]== '#' &&
			   m[y][x+1]== '#' &&
			   m[y][x-1]== '#'
			){
				p1+=y*x;
			}
		}
	}

	cout<<"[P1] "<<p1<<endl;
	string totalInstr = solvePath(m, start);
	cout<<"[P2] "<<totalInstr<<endl;
	//L,12,L,8,R,12,L,10,L,8,L,12,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,12,L,8,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12
	stringstream ss(totalInstr);
	char dir, trash;
	int dist;
	vector<string> tokens;
	while(ss>>dir>>trash>>dist){
		tokens.emplace_back(dir+to_string(dist));
		ss>>trash;
	}

	map<string, int> counter;
	for(int i =0;i<tokens.size()-1;i++){
		counter[tokens[i]+tokens[i+1]]++;
	}
	
}