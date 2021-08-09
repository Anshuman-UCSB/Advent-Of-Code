#include "../aoc.h"
#include "../point.h"
#include <cassert>

struct Cell{
	bool isElf;
	bool moved;
	bool attacked;
	int hp, atk;
	char id;
	Cell(char id='.', int hp=0, int atk=3):id(id), hp(hp), atk(atk), isElf(id=='E'), moved(false), attacked(false){}
};

vector<vector<Cell>> m;

/* util */
ostream& operator<<(ostream& os, const Cell& c){os<<c.id;return os;}
void print(){
	for(auto& r: m){
		for(auto& c: r)cout<<c;
		cout<<"	";
		string delim = "";
		for(auto& c: r){
			if(c.id == 'E' || c.id == 'G'){
				cout<<delim<<c.id<<"("<<c.hp<<")";
				delim = ", ";
			}
		}
		cout<<endl;
	}
}

Point getTarget(const Point& start){
	// bfs until find enemy
	char enemy = at(m,start).isElf?'G':'E';
	set<Point> visited = {start};
	vector<Point> q, temp;
	q.push_back(start);
	while(!q.empty()){
		for(auto& base: q){
			if(at(m, base).id == '#') continue;
			for(auto& n: base.getNeighbors()){
				if(at(m, n).id == enemy)
					return base;
				if(at(m, n).id == '.' && visited.insert(n).second)
					temp.push_back(n);
			}
		}

		q.swap(temp);
		sort(q.begin(), q.end());
		temp.clear();
	}
	return Point(-1,-1);
}

Point getStep(const Point& from, const Point& to){
	char enemy = at(m,from).isElf?'G':'E';
	set<Point> visited = {from};
	vector<Point> q, temp;
	q.push_back(from);
	while(!q.empty()){
		for(auto& base: q){
			if(at(m, base).id == '#') continue;
			for(auto& n: base.getNeighbors()){
				if(n == to)
					return base;
				if(at(m, n).id == '.' && visited.insert(n).second)
					temp.push_back(n);
			}
		}

		q.swap(temp);
		sort(q.begin(), q.end());
		temp.clear();
	}
	return Point(-1,-1);
}

int eCount(0), gCount(0);
int elves(0), goblins(0);
Point step(const Point& p){
	if(at(m, p).moved) return p;
	if(elves == 0 || goblins == 0)
		return Point();

	if(at(m, p).id != 'G' && at(m, p).id != 'E') return p; 
	for(auto& n: p.getNeighbors()){
		if(at(m, n).id == (at(m, p).isElf?'G':'E')) return p;
	}
	at(m, p).moved = true;
	auto target = getTarget(p);
	// cout<<p<<" targeting "<<target<<endl;
	if(target.x!=-1){
		// cout<<"moved from "<<p<<" to "<<getStep(target, p)<<endl;
		Point targetPos = getStep(target, p);
		swap(at(m, targetPos), at(m, p));
		return targetPos;
	}
	return p;
}


void attack(const Point& p){
	if(at(m, p).id != 'G' && at(m, p).id != 'E') return; 
	if(at(m, p).attacked) return;
	assert(at(m, p).hp>0);
	at(m, p).attacked = true;
	Point target(999,999);
	int minHp = 999;
	for(auto& d: p.getNeighbors()){
		if(at(m, d).id != (at(m, p).isElf?'G':'E')) continue;
		if(auto hp = at(m, d).hp;hp < minHp){
			target = d;
			minHp = hp;
		}
	}
	if(target.x != 999){
		auto& tCell = at(m, target);
		// cout<<at(m,p)<<p<<" attacked "<<at(m,target)<<target<<" for "<<at(m, p).atk<<endl;
		tCell.hp-=at(m, p).atk;
		if(tCell.hp <=0){
			if(tCell.id == 'E')
				elves--;
			else
				goblins--;
			tCell.id = '.';
		}
	}
}

bool iter(){
	for(int y = 1;y<m.size()-1;y++){
		for(int x = 1;x<m[0].size()-1;x++){
			m[y][x].moved = false;
			m[y][x].attacked = false;
		}
	}
	
	for(int y = 1;y<m.size()-1;y++){
		for(int x = 1;x<m[0].size()-1;x++){
			if(m[y][x].id != 'E' && m[y][x].id != 'G') continue;
			Point newPos = step(Point(x, y));
			if(newPos == Point())
				return false;
			attack(newPos);
		}
	}
	return true;
}

void p1(){
	goblins = gCount;
	elves = eCount;
	int round;
	for(round = 0;goblins>0 && elves>0;){
		if(iter()) round++;
	}
	int sum= 0;
	for(auto& r: m){
		for(auto& c: r){
			if(c.id == 'E' || c.id == 'G')
				sum+=c.hp;
		}
	}
	cout<<"[P1] "<<round*sum<<endl;
}

vector<Point> elfPos;
vector<vector<Cell>> initial;

int p2test(int atk){
	int round;

	m = initial;
	goblins = gCount;
	elves = 1;

	for(auto& p: elfPos){
		at(m, p).atk = atk;
	}
	
	for(round = 0;goblins>0 && elves>0;){
		if(iter()) round++;
	}
	if(elves==0) return 0;
	int sum= 0;
	for(auto& r: m){
		for(auto& c: r){
			if(c.id == 'E' || c.id == 'G')
				sum+=c.hp;
		}
	}
	return sum*round;
}

void p2(){
	int l, h, m;
	for(h=3;!p2test(h);h*=2){}
	l = h/2;
	while(l+1<h){
		m = (l+h)/2;
		if(p2test(m)){
			h = m;
		}else{
			l = m+1;
		}
		// cout<<l<<"->"<<h<<endl;
	}
	cout<<"[P2] "<<p2test(l)<<endl;
}

int main(){
	fstream file("Day 15/input");
	string line;
	while(getline(file, line)){
		m.emplace_back(line.size());
		for(int i=0;i<line.size();i++){
			m.back()[i] = Cell(line[i], 200, 3);
			if(line[i] == 'G') gCount++;
			else if(line[i] == 'E') {
				eCount++;
				elfPos.emplace_back(i, m.size()-1);
			}
		}
	}
	initial = m;

	p1();
	p2();
}