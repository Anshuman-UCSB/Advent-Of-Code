#include "../aoc.h"
#include <sstream>
#include <queue>
#define x first
#define y second
#define coord pair<int, int>

int lx(999), hx(0), ly(999), hy(0);
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
vector<coord> getNeighbors(const coord& c){
	vector<coord> out;
	auto& [x,y] = c;
	for(int i = 0;i<4;i++){
		coord t(x+dx[i], y+dy[i]);
		if(t.x>=lx && t.x<=hx && t.y>=ly && t.y<=hy){
			out.push_back(t);
		}
	}
	return out;
}

int main(){
	fstream file("Day 6/input");
	string line;
	map<coord, int> m;
	char c;
	int id = 1;
	int x, y;
	while(getline(file, line)){
		stringstream ss(line);
		ss>>x>>c>>y;
		m[coord(x,y)]=id++;
		lx = min(x, lx);
		ly = min(y, ly);
		hx = max(x, hx);
		hy = max(y, hy);
	}
	lx--; ly--;
	hx++; hy++;
	bool done = false;
	set<coord> q, next, check;
	for(auto& [crd, ignore]: m){
		q.insert(crd);
	}
	map<int, int> counter;
	while(!done){
		done = true;
		check.clear();
		for(auto& baseCoord: q){
			for(auto& crd: getNeighbors(baseCoord)){
				if(m.count(crd)==0){
					m[crd] = -(m[baseCoord]);
					check.insert(crd);
				}else if(m[crd]<0 && m[crd] != -(m[baseCoord])){
					m[crd]='.';
					check.erase(crd);
				}
			}
		}
		for(auto& crd: check){
			m[crd] = abs(m[crd]);
			counter[m[crd]]++;
		}
		q=check;
		done = q.size()==0;
	}
	for(int i = ly;i<=hy;i++){
		counter.erase(m[coord(0, i)]);
		counter.erase(m[coord(hx, i)]);
	}
	for(int i = lx;i<=hx;i++){
		counter.erase(m[coord(i, 0)]);
		counter.erase(m[coord(i, hy)]);
	}
	// for(int i = ly;i<=hy;i++){for(int j= lx;j<=hx;j++){if(m.count(coord(j,i)))cout<<m[coord(j,i)];else cout<<" ";}cout<<endl;}
	int p1 = 0;
	for(auto& [ignore, v]: counter){
		p1 = max(p1, v);
	}
	cout<<counter<<endl;
	cout<<"[P1] "<<p1<<endl;
}