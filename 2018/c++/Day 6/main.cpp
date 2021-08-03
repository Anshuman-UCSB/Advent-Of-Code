#include "../aoc.h"
#include "../point.h"
#include <set>
#include <sstream>
#include <map>

Point low(99,99), high;

struct Cell{
	int dist;
	int id;
	Cell(int dist = 9999, int id=0):dist(dist), id(id){};
};

int width, height;

static inline int getPos(int x, int y){
	return (y-low.y)*width + (x-low.x);
}

vector<Point> getNeighbors(const Point& p){
	vector<Point> out;
	if(p.x != 0)
		out.emplace_back(p.x-1, p.y);
	if(p.x < width-1)
		out.emplace_back(p.x+1, p.y);
	if(p.y != 0)
		out.emplace_back(p.x, p.y-1);
	if(p.y < height-1)
		out.emplace_back(p.x, p.y+1);
	return out;
}

vector<Point> coords;
static void print(vector<Cell>& m){
	int ind = 0;
	for(auto& v: m){
		if(v.id == -1)cout<<".";
		else cout<<(v.id?to_string(v.id):".");
		if(++ind%width == 0) cout<<endl;
	}
}

void p1(){
	width=high.x-low.x;
	height=high.y-low.y;
	vector<Cell> m(width*height);
	int id = 0;
	set<Point> q, temp;
	map<int, int> idCounter;
	for(auto& c: coords){
		q.insert(c);
		m[getPos(c.x, c.y)].id=++id;
	}
	for(int dist = 0; !q.empty();dist++){
		for(auto& point: q){
			for(auto& p: getNeighbors(point)){
				auto& t = m[getPos(p.x, p.y)];
				auto& thisCell = m[getPos(point.x, point.y)];
				if(t.id == 0){
					t.id = thisCell.id;
					idCounter[t.id]++;
					t.dist = dist;
					temp.insert(p);
				}else if(t.dist == dist && t.id != thisCell.id){
					idCounter[t.id]--;
					t.id = -1; t.dist = dist;
				}
			}
		}
		q.swap(temp);
		temp.clear();
	}
	// print(m);
	for(int i = 0;i<width;i++){
		idCounter[m[getPos(i, 0)].id]=0;
		idCounter[m[getPos(i, height-1)].id]=0;
		// cout<<i<<", "<<0<<endl;
		// cout<<i<<", "<<height-1<<endl;
	}
	for(int i = 0;i<height;i++){
		// cout<<0<<", "<<i<<endl;
		// cout<<width-1<<", "<<i<<endl;
		idCounter[m[getPos(0, i)].id]=0;
		idCounter[m[getPos(width-1, i)].id]=0;
	}
	int p1 = 0;
	for(auto& [k, v] : idCounter){
		p1 = max(v+1, p1);
	}
	cout<<"[P1] "<<p1<<endl;
}

int main(){
	fstream file("Day 6/input");
	string line;
	char trash;
	while(getline(file, line)){
		coords.emplace_back();
		stringstream ss(line);
		ss>>coords.back().x>>trash>>coords.back().y;
		low.min(coords.back());
		high.max(coords.back());
	}
	low--;high++;
	p1();
}