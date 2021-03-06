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

static inline int getPos(const int& x, const int& y) {
	return (y-low.y)*width + (x-low.x);
}


vector<Point> getNeighbors(const Point& p){
	vector<Point> out;
	if(p.x != low.x)
		out.emplace_back(p.x-1, p.y);
	if(p.x < high.x)
		out.emplace_back(p.x+1, p.y);
	if(p.y != low.y)
		out.emplace_back(p.x, p.y-1);
	if(p.y < high.y)
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

static bool withinRange(const Point& p, int threshold){
	int dists = 0;
	for(auto& c: coords){
		dists+=p.distTo(c);
		if(dists>threshold) return false;
	}
	return true;
}

void p1(){
	width=high.x-low.x;
	height=high.y-low.y;
	vector<Cell> m((width+1)*(height+1));
	int id = 0;
	set<Point> q, temp;
	map<int, int> idCounter;
	for(auto& c: coords){
		q.insert(c);
		m[getPos(c.x, c.y)].id=++id;
	}
	for(int dist = 0; !q.empty();dist++){
		// cout<<q<<endl;
		for(const auto& point: q){
			// cout<<point<<endl;
			for(const auto& p: getNeighbors(point)){
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
		temp = set<Point>();
	}
	// print(m);
	for(int i = low.x;i<=high.x;i++){
		idCounter[m[getPos(i, low.y)].id]=0;
		idCounter[m[getPos(i, high.y)].id]=0;
		// cout<<i<<", "<<0<<endl;
		// cout<<i<<", "<<height-1<<endl;
	}
	for(int i = low.y;i<=high.y;i++){
		// cout<<0<<", "<<i<<endl;
		// cout<<width-1<<", "<<i<<endl;
		idCounter[m[getPos(low.x, i)].id]=0;
		idCounter[m[getPos(high.x, i)].id]=0;
	}
	int p1 = 0;
	for(auto& [k, v] : idCounter){
		p1 = max(v+1, p1);
	}
	cout<<"[P1] "<<p1<<endl;
}

void p2(){
	int p2 = 0;
	for(int x = low.x;x<=high.x;x++){
		for(int y = low.y;y<=high.y;y++){
			p2+=withinRange(Point(x,y), 10000);
		}
	}
	cout<<"[P2] "<<p2<<endl;
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
	p2();
}