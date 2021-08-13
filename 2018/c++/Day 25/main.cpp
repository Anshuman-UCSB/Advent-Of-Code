#include "../aoc.h"
#include <sstream>

struct Point{
	int x, y, z, w;
	Point(int x = 0, int y = 0, int z = 0, int w = 0):x(x), y(y), z(z), w(w){}
	int distTo(const Point& p){
		return abs(x-p.x)+abs(y-p.y)+abs(z-p.z)+abs(w-p.w);
	}
};

ostream& operator<<(ostream& os, const Point& p){
	os<<"("<<p.x<<", "<<p.y<<", "<<p.z<<", "<<p.w<<")";
	return os;
}

int main(){
	fstream file("Day 25/input");
	string line;
	vector<Point> points;
	int x, y, z, w;
	char t;
	while(getline(file, line)){
		stringstream ss(line);
		ss>>x>>t>>y>>t>>z>>t>>w;
		points.emplace_back(x,y,z,w);
	}
	vector<vector<Point>> constellations;
	
	set<int> possible;
	for(auto& p : points){
		for(int i = 0;i<constellations.size();i++){
			for(auto& tp: constellations[i]){
				if(p.distTo(tp)<=3){
					possible.insert(i);
				}
			}
		}
		if(possible.size() == 0){
			constellations.push_back(vector<Point>(1, p));
		} else if(possible.size() == 1){
			constellations[*(possible.begin())].push_back(p);
		} else{
			int mergeHost = -1;
			for(auto& i: possible){
				if(mergeHost == -1){
					mergeHost = i;
					continue;
				}
				auto& host = constellations[mergeHost];
				host.insert(host.end(), constellations[i].begin(), constellations[i].end());
				host.push_back(p);
				constellations[i].clear();
			}
		}
		possible.clear();
	}

	int p1 = 0;
	for(auto& c: constellations){
		if(!c.empty()) p1++;
	}
	cout<<"[P1] "<<p1<<endl;

	//353 too high

}