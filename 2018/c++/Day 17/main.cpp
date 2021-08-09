#include "../aoc.h"
#include "../point.h"
#include <sstream>
#include <queue>
int minX(500), maxX(500), minY(999), maxY(0);

struct clay{
	int xl, xh, yl, yh;
	clay(){}
	clay(string line){
		stringstream ss(line);
		char t;
		ss>>t;
		if(t == 'x'){
			ss>>t;
			ss>>xl;
			xh=xl;
			ss>>t>>t>>t>>yl>>t>>t>>yh;
		}else{
			ss>>t;
			ss>>yl;
			yh=yl;
			ss>>t>>t>>t;
			ss>>xl>>t>>t>>xh;
		}
		minX = min(minX, xl-1);
		maxX = max(maxX, xh+1);
		minY = min(minY, yl);
		maxY = max(maxY, yh+1);
	}
};

ostream& operator<<(ostream& os, const clay& c){
	os<<c.xl<<".."<<c.xh<<", "<<c.yl<<".."<<c.yh<<endl;
	return os;
}

vector<vector<char>> m;

void print(){
	for(auto& r: m){for(auto& c: r)cout<<c;cout<<endl;}
}

bool isStable(const Point& p){
	for(int i = 1;;i++){
		auto tp = p+Point(i,0);
		if(at(m, tp)=='#' || at(m, tp) == '~')break;
		if(at(m, tp)=='.') return false;
	}
	for(int i = 1;;i++){
		auto tp = p+Point(-i,0);
		if(at(m, tp)=='#' || at(m, tp) == '~')break;
		if(at(m, tp)=='.') return false;
	}
	return true;
}

void flow(){
	queue<Point> q;
	q.push(Point(500-minX, 0));
	at(m, q.front()) = '|';
	while(!q.empty()){
		Point p = q.front();
		q.pop();
		if(p.y>=maxY-1) continue;
		if(at(m, p) != '|') continue;
		// print();
		// cout<<p<<", "<<q.size()<<endl;
		if(Point tp = p+Point(0,1); at(m, tp)=='.'){
			at(m, tp)='|';
			for(auto& n: tp.getNeighbors())q.push(n);q.push(tp);
		}else{
			if(at(m, p+Point(0,1)) == '|') continue;
			if(Point tp = p+Point(1,0); at(m, tp) == '.'){
				at(m, tp)='|';
				for(auto& n: tp.getNeighbors())q.push(n);q.push(tp);
			}
			if(Point tp = p+Point(-1,0); at(m, tp) == '.'){
				at(m, tp)='|';
				for(auto& n: tp.getNeighbors())q.push(n);q.push(tp);
			}
			if(isStable(p)){
				at(m, p) = '~';
				q.push(p+Point(0,-1));
				for(int i = 1;;i++){
					auto tp = p+Point(i, 0);
					if(at(m,tp)=='|'){
						at(m,tp) = '~';
						q.push(tp+Point(0,-1));
					}else break;
				}
				for(int i = 1;;i++){
					auto tp = p+Point(-i, 0);
					if(at(m,tp)=='|'){
						at(m,tp) = '~';
						q.push(tp+Point(0,-1));
					}else break;
				}
			}
		}
	}
}

int main(){
	fstream file("Day 17/input");
	string line;
	vector<clay> inp;
	while(getline(file, line)){
		inp.emplace_back(line);
	}
	m = vector<vector<char>>(maxY, vector<char>(maxX-minX+1,'.'));
	m[0][500-minX]='+';
	for(auto& c: inp){
		for(int y = c.yl;y<=c.yh;y++){
			for(int x = c.xl;x<=c.xh;x++){
				m[y][x-minX] = '#';
			}
		}
	}
	flow();
	int flowing(0), still(0);
	for(int y = minY; y<m.size();y++){
		for(auto& c: m[y]){
			if(c == '|') flowing++;
			if(c == '~') still++;
		}
	}
	// print();
	cout<<"[P1] "<<flowing+still<<endl;
	cout<<"[P2] "<<still<<endl;
	// print();
}