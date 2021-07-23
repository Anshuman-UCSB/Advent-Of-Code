#include <iostream>
#include <vector>
using namespace std;

struct Coord{
	int x, y;
	Coord():x(0), y(0){};
	Coord(int x, int y):x(x), y(y){};
	Coord operator+(const Coord& c){
		return Coord(x+c.x, y+c.y);
	}
	Coord operator-(const Coord& c){
		return Coord(x-c.x, y-c.y);
	}
	bool operator==(const Coord& c) const{
		return x==c.x && y==c.y;
	}
	bool operator<(const Coord& c) const{
		return x<c.x || (x==c.x && y<c.y);
	}
	Coord operator+=(const Coord& c){
		x+=c.x;
		y+=c.y;
	}
	Coord operator-=(const Coord& c){
		x-=c.x;
		y-=c.y;
	}
};

template <class T>
void printGrid(const map<Coord, T>& m, map<T, string>& mapping){
	int lx, ly, hx, hy;
	lx = ly = hx = hy = 0;
	for(auto& p: m){
		lx = min(lx, p.first.x);
		ly = min(ly, p.first.y);
		hx = max(hx, p.first.x);
		hy = max(hy, p.first.y);
	}
	vector<vector<string>> out(hy-ly+1, vector<string>(hx-lx+1, " "));
	for(auto& p: m){
		if(mapping.count(p.second)){
			out[p.first.y-ly][p.first.x-lx] = mapping[p.second];
		}else{
			out[p.first.y-ly][p.first.x-lx] = " ";
		}
	}
	string pstring = "";
	for(int i = out.size()-1;i>=0;i--){
		for(auto& v: out[i]){
			pstring+=v;
		}pstring+="\n";
	}
	cout<<pstring<<endl;
}

ostream& operator<<(ostream& os, const Coord& c){
	os<<"("<<c.x<<", "<<c.y<<")";
	return os;
}