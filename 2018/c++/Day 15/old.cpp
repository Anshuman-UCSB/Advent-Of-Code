#include "../aoc.h"
#include "../point.h"
#include <algorithm>
#include <queue>
vector<vector<bool>> m;


struct Unit{
	bool isElf;
	Point pos;
	int atk, hp;
	Unit(int x = 0, int y = 0, int atk = 3, int hp = 200, bool isElf = true):pos(x, y), atk(atk), hp(hp), isElf(isElf){}
	bool operator<(const Unit& u) const {
		return pos<u.pos;
	}
	void move();
};

ostream& operator<<(ostream& os, const Unit& u){
	os<<(u.isElf?'E':'G')<<u.pos<<" ["<<u.atk<<", "<<u.hp<<"]";
	return os;
}

vector<Unit> goblins, elfs;

void Unit::move(){
	vector<Unit>& enemy = (isElf?goblins:elfs);
	vector<Unit>& ally = (isElf?elfs:goblins);
	vector<Point> targets, allies;
	// cout<<"ENEMY: "<<enemy<<endl;
	// cout<<"ALLY: "<<ally<<endl;
	targets.resize(enemy.size());
	allies.resize(ally.size());
	transform(enemy.begin(), enemy.end(), targets.begin(), [](const Unit& u){return u.pos;});
	transform(ally.begin(), ally.end(), allies.begin(), [](const Unit& u){return u.pos;});
	for(auto& p: pos.getNeighbors()){
		if(find(targets.begin(), targets.end(), p)!=targets.end())
			return;
	}
	
	vector<Point> q, temp;
	q = pos.getNeighbors();
	Point targetPos(-1,-1);
	while(!q.empty()){
		for(auto& top: q){
			if(m[top.y][top.x] || (find(allies.begin(), allies.end(), top) != allies.end())) {
				// cout<<pos<<"-/->"<<top<<" is invalid"<<endl;
				continue;
			} //if wall
			// cout<<"Adding :"<<top<<endl;
			if(auto temp = find(targets.begin(), targets.end(), top); temp!=targets.end()){
				targetPos = *temp;
				goto foundTarget;
			}
			auto neighbors = top.getNeighbors();
			temp.insert(temp.end(), neighbors.begin(), neighbors.end());
		}
		q.swap(temp);
		temp.clear();
		sort(q.begin(), q.end());
	}
	cout<<"Didn't find target for "<<*this<<endl;
	return;

	foundTarget:;
	q.clear();
	q.push_back(targetPos);
	temp.clear();
	while(!q.empty()){
		for(auto& top: q){
			for(auto &p: top.getNeighbors()){
				if(m[top.y][top.x] || (targetPos != top && find(allies.begin(), allies.end(), top) != allies.end())) break; //if wall
				if(p == pos){
					pos = top;
					return;
				}
				temp.push_back(p);
			}
		}
		q.swap(temp);
		temp.clear();
		sort(q.begin(), q.end());
	}
}

void print(){
	vector<vector<char>> printMap(m.size(), vector<char>(m[0].size(), '.'));
	for(auto& goblin: goblins)
		printMap[goblin.pos.y][goblin.pos.x] = 'G';
	for(auto& elf: elfs)
		printMap[elf.pos.y][elf.pos.x] = 'E';
	for(int y = 0;y<m.size();y++){
		for(int x = 0;x<m[0].size();x++){
			if(m[y][x]) printMap[y][x] = '#';
		}
	}
	
	for(auto& v: printMap){for(auto& c: v)cout<<c;cout<<endl;}
	cout<<goblins<<endl;
	cout<<elfs<<endl;
}

void iter(){
	int g = 0;
	int e = 0;
	for(;g<goblins.size() || e<elfs.size();){
		if(g == goblins.size()){
			elfs[e++].move();
			continue;
		}
		if(e == elfs.size()){
			goblins[g++].move();
			continue;
		}
		if(goblins[g].pos < elfs[e].pos){
			goblins[g++].move();
		}
		else{
			elfs[e++].move();
		}
	}
}

int main(){
	fstream file("Day 15/input");
	string line;
	while(getline(file, line)){
		m.emplace_back(line.size());
		for(int x = 0;x<line.size();x++){
			switch(line[x]){
				case '#': m.back()[x] = true; break;
				case 'G': goblins.emplace_back(x, m.size()-1, 3, 200, false); break;
				case 'E': elfs.emplace_back(x, m.size()-1, 3, 200, true); break;
			}
		}
	}
	print();
	for(int i = 0;i<3;i++){
		iter();
		print();
	}
}