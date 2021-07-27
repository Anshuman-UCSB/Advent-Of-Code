#include <iostream>
#include <regex>
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
	comp.run();
	cout<<"[P2] "<<comp.out.back()<<endl;
	exit(1);
}

map<string, int> genCounts(vector<string>& tok, int size){
	map<string, int> out;
	if(size > tok.size()){
		return out;
	}
	for(int i = 0;i<tok.size()-size;i++){
		string build;
		string delim = "";
		for(int j = i;j<i+size;j++){
			build+=delim;
			build+=tok[j];
			delim = ",";
		}
		out[build]++;
	}

	return out;
}

vector<string> tokenize(string inp){
	const string comma = ",";
	stringstream ss(inp);
	char trash, dir;
	int dist;
	vector<string> tok;
	while(ss>>dir>>trash>>dist){
		ss>>trash;
		tok.emplace_back(dir+comma+to_string(dist));
	}
	return tok;
}

void replace(string& str, string fstring, string repl){
	std::string::size_type n = 0;
	while ( ( n = str.find( fstring, n ) ) != std::string::npos )
	{
		str.replace( n, fstring.size(), repl );
		n += repl.size();
	}
}

void p2Algorithmic(string inp, int level){
	for(int _ = 0;_<level;_++){
		// cout<<" ";
	}
	// cout<<level<<": "<<inp<<endl;
	vector<string> tok = tokenize(inp);
	if(level == 3){
		if(inp.size() < 20){
			// cout<<"SOLUTION FOUND"<<endl;
			cout<<inp<<endl;
		}
		return;
	}
	char temp = 'A'+level;
	string build;
	build+=temp;
	// const string t = build;
	const string t = "";
	auto cnt = genCounts(tok, 4-level);
	// cout<<cnt<<endl;
	for(auto& p :cnt){
		if(p.first.size() <= 19){
			// cout<<" > "<<p.first<<", "<<p.second<<endl;
			string copy = inp;
			replace(copy, p.first, "");
			replace(copy, ",,", ",");
			replace(copy, ",,", ",");
			replace(copy, ",,", ","); //don't look at me
			
			if(copy.back() == ','){
				copy.pop_back();
			}			
			if(copy.front() == ','){
				copy.erase(copy.begin());
			}

			p2Algorithmic(copy, level+1);
		}else{
			// cout<<p<<" wasn't enough"<<endl;
		}
	}
	
}

int main(){
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
	

	// for(auto& r: m){
	// 	cout<<r<<endl;
	// }
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
	hand();
	string totalInstr = solvePath(m, start)+",";
	// p2Algorithmic(totalInstr,0);
	// exit(1);
	smatch match;
	regex r("^(.{1,21})\1*(.{1,21})(?:\1|\2)*(.{1,21})(?:\1|\2|\3)*$");
	if(regex_search(totalInstr, match, r)) {
		for(int i = 1;i<match.size();i++){
			cout<<match[i]<<endl;
		}
    }
	cout<<"[P2] "<<totalInstr<<endl;
	//L,12,L,8,R,12,L,10,L,8,L,12,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,12,L,8,R,12,L,12,L,8,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12,R,12,L,8,L,10,L,10,L,8,L,12,R,12
	
}