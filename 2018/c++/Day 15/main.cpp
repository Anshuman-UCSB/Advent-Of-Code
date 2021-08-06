#include "../aoc.h"
#include "../point.h"

struct Cell{
	char type;
	int atk, hp;
	Cell(char type='.', int atk = 3, int hp = 200):type(type), atk(atk), hp(hp){}
};

vector<vector<Cell>> m;

Point move(int x, int y){
	if(m[y][x].type == '.' || m[y][x].type == '#') return Point(-1, -1);
	char target = (m[y][x].type=='E'?'G':'E');
	set<Point> visited = {Point(x, y)};
	set<Point> q, temp;
	for(auto& v: Point(x, y).getNeighbors()){
		if(m[v.y][v.x].type == target) return Point(x,y);
	}
	q.insert(Point(x,y));
	Point nearestEnemy(999,999);
	while(!q.empty()){
		for(auto& p: q){
			for(auto& v: p.getNeighbors()){
				if(m[v.y][v.x].type==target){
					cout<<p<<", "<<nearestEnemy<<endl;
					if(p<nearestEnemy){
						nearestEnemy = p;
						cout<<"here"<<endl;
					}
				}
				if(m[v.y][v.x].type == '.'){
					if(visited.insert(v).second)
						temp.insert(v);
				}
			}
		}
		q.swap(temp);
		temp.clear();
	}
	if(nearestEnemy == Point(999,999)){
		// cout<<"Didn't find target"<<endl;
		return Point(x,y);
	}
	q.clear();
	temp.clear();
	q.insert(nearestEnemy);
	visited.clear();
	while(!q.empty()){
		for(auto& p: q){
			for(auto& n: p.getNeighbors()){
				if(n == Point(x, y)){
					// cout<<"Moving from "<<m[y][x].type<<" to "<<m[p.y][p.x].type<<endl;
					swap(m[y][x], m[p.y][p.x]);
					return Point(p.x, p.y);
				}
				if(m[n.y][n.x].type == '.'){
					if(visited.insert(n).second)
						temp.insert(n);
				}
			}
		}
		q.swap(temp);
		temp.clear();
	}
	return Point(-2, -2);
}

int elfs(0), goblins(0);
void attack(Point& p){
	if(m[p.y][p.x].hp<=0) return;
	Point target;
	int minHp = 201;
	char enemy = (m[p.y][p.x].type=='E'?'G':'E');
	for(auto& n: p.getNeighbors()){
		if(m[n.y][n.x].type!=enemy) continue;
		if(m[n.y][n.x].hp<minHp){
			target = n;
			minHp = m[n.y][n.x].hp;
		}
	}
	if(target != Point()){
		if((m[target.y][target.x].hp-=m[p.y][p.x].atk)<=0){
			m[target.y][target.x].type = '.';
			if(enemy == 'E')elfs--;
			else goblins--;
		}		
		// cout<<m[p.y][p.x].type<<" hit "<<m[target.y][target.x].type<<" for "<<m[p.y][p.x].atk <<\
		// 	" to "<<m[target.y][target.x].hp<<" hp."<<endl;
	}
}

void print(){
	for(auto& r: m){
		for(auto& c: r) cout<<c.type;
		cout<<endl;
	}
}

bool iter(){
	vector<Point> checks;
	for(int y = 0;y<m.size();y++){
		for(int x = 0;x<m[0].size();x++){
			if(m[y][x].type == 'E' || m[y][x].type == 'G')
				checks.push_back(Point(x, y));
		}
	}
	for(auto& p: checks){
		if(elfs == 0 || goblins == 0) return false;
		cout<<p<<" moved to ";
		auto n = move(p.x, p.y);
		cout<<n<<endl;
		// cout<<n<<"'s turn"<<endl;
		if(n.x>0)
			attack(n);
	}
	return true;
}

void p1(){
	print();
	int rounds = 0;
	// string line;
	while(elfs>0&&goblins>0){
		cout<<"Round: "<<rounds<<"	Elves: "<<elfs<<"	"<<"Goblins: "<<goblins<<endl;
		if(iter())
			rounds++;
		else
			break;
		print();
		// cin>>line;
	}
	print();
	int out = 0;
	for(auto& r: m){
		for(auto& c: r){
			if(c.type == 'G' || c.type =='E'){
				cout<<c.type<<">"<<c.hp<<endl;
				out+=c.hp;
			}
		}
	}
	cout<<out<<"*"<<rounds<<endl;
	cout<<"[P1] "<<out*rounds<<endl;
}

int main(){
	fstream file("Day 15/input");
	string line;
	while(getline(file, line)){
		m.emplace_back(line.size());
		for(int i = 0;i<line.size();i++){
			m.back()[i] = Cell(line[i]);
			if(line[i] == 'E')elfs++;
			else if(line[i] == 'G') goblins++;
		}
	}
	// p1();
	iter();
	print();
}