#include "../util.h"

int main(){
	auto raw = readInput(3);

	map<pair<int, int>, pair<int, int>> visited;
	int x(0), y(0), step(0);
	visited[make_pair(x,y)] = make_pair(step++,-1);
	map<char, pair<int, int>> m={
		{'R', make_pair(1,0)},	
		{'L', make_pair(-1,0)},	
		{'U', make_pair(0,1)},	
		{'D', make_pair(0,-1)}
	};
	for(string token: tokenize(raw[0], ", ")){
		for(int i = 0;i<stoi(token.substr(1));i++){
			x += m[token[0]].first;
			y += m[token[0]].second;
			visited[make_pair(x,y)] = make_pair(step++,-1);
		}
	}
	x = y = step = 0;
	step++;
	for(string token: tokenize(raw[1], ", ")){
		for(int i = 0;i<stoi(token.substr(1));i++){
			x += m[token[0]].first;
			y += m[token[0]].second;
			visited[make_pair(x,y)].second = step++;
		}
	}
	// for(auto& p: visited){
	// 	cout<<"("<<p.first.first<<", "<<p.first.second<<") - "<<p.second.first<<" - "<<p.second.second<<endl;
	// }
	vector<vector<int>> crosses;
	for(auto& p: visited){
		if(p.second.first>0 && p.second.second > 0){
			crosses.emplace_back(vector<int>{p.first.first, p.first.second, p.second.first+p.second.second});
		}
	}
	int p1(9999999), p2(9999999);
	for(auto& v: crosses){
		p1 = min(p1, abs(v[0])+abs(v[1]));
		p2 = min(p2, v[2]);
	}

	cout<<"Part 1: "<<p1<<endl;
	cout<<"Part 2: "<<p2<<endl;
}
