#include "AOC.h"
#include <cassert>
#include <cmath>

struct point{
	int x, y, z;
	point():x(0),y(0),z(0){}
	point(int x, int y, int z):x(x), y(y),z(z){}
};
point abs(const point& a){
	return point(abs(a.x), abs(a.y), abs(a.z));
}
int sum(const point& a){
	return a.x+a.y+a.z;
}
point operator+(const point& a, const point& b){
	return point(a.x+b.x, a.y+b.y, a.z+b.z);
}
point operator-(const point& a, const point& b){
	return point(a.x-b.x, a.y-b.y, a.z-b.z);
}
bool operator<(const point& a, const point& b){
	return (a.x<b.x || 
			(a.x==b.x && a.y<b.y) ||
			(a.x==b.x && a.y==b.y && a.z<b.z));
}
bool operator==(const point& a, const point& b){
	return (a.x==b.x && a.y==b.y && a.z==b.z);
}
int manhattan(const point& a, const point& b){
	point t = a-b;
	return abs(t.x)+abs(t.y)+abs(t.z);
}
int dist(const point& a, const point& b){
	point t = a-b;
	return pow(t.x,2)+pow(t.y,2)+pow(t.z,2);
}

ostream& operator<<(ostream& os, const point& p){
	os<<"("<<p.x<<", "<<p.y<<", "<<p.z<<")";
	return os;
}

void valsort(int& a, int& b){
	if(abs(a)>abs(b)){
		int oa(a), ob(b);
		if(b<=0){
			b =  oa;
			a = -ob;
		}else{
			b = -oa;
			a =  ob;
		}
	}
}
void normalizeVec(point& vec){
	valsort(vec.x, vec.z);
	valsort(vec.x, vec.y);
	valsort(vec.y, vec.z);
	if(vec.x<0){
		vec.x*=-1;
		vec.y*=-1;
	}
	if(vec.y<0){
		vec.y*=-1;
		vec.z*=-1;
	}
}

struct Scanner{
	point pos;
	int id;
	bool solved, done;
	vector<point> points;
	map<int, vector<point>> fpmap;
	set<int> fps;
	Scanner():solved(false), done(false){}
	Scanner(string inp):Scanner(){
		stringstream ss(inp);
		ss>>inp>>inp>>id;
		if(id == 0)
			solved = true;
	}
};

vector<point> permutePoints(vector<point>& points, function<point(point&)>& permutation){
	vector<point> t;
	for(auto& p: points){
		t.push_back(permutation(p));
	}
	return t;
}

void genFingerprints(vector<Scanner>& scns){
	for(auto& s: scns){
		for(int i = 0;i<s.points.size()-1;i++){
			for(int j = i+1;j<s.points.size();j++){
				int fp = dist(s.points[j],s.points[i]);
				s.fpmap[fp].push_back(s.points[j]);
				s.fpmap[fp].push_back(s.points[i]);
				s.fps.insert(fp);
			}
		}
	}
}

vector<int> sharedPoints(set<int>& a, set<int>& b){
	vector<int> out;
	set_intersection(begin(a), end(a), begin(b), end(b), back_insert_iterator(out));
	return out;
}

pair<point, int> maxValue(map<point, int>& m){
	pair<point, int> p;
	for(auto& [k,v]: m)
		if(v>p.second)
			p = pair<point, int>(k,v);
	return p;
}

chrono::time_point<std::chrono::steady_clock> day19(input_t& inp){
	int p1(0), p2(0);

	vector<function<point(point&)>> perms{
		[](const point& p) { return point(p.x, p.y, p.z); },
		[](const point& p) { return point(p.x, -p.z, p.y); },
		[](const point& p) { return point(p.x, -p.y, -p.z); },
		[](const point& p) { return point(p.x, p.z, -p.y); },
		[](const point& p) { return point(-p.y, p.x, p.z); },
		[](const point& p) { return point(p.z, p.x, p.y); },
		[](const point& p) { return point(p.y, p.x, -p.z); },
		[](const point& p) { return point(-p.z, p.x, -p.y); },
		[](const point& p) { return point(-p.x, -p.y, p.z); },
		[](const point& p) { return point(-p.x, -p.z, -p.y); },
		[](const point& p) { return point(-p.x, p.y, -p.z); },
		[](const point& p) { return point(-p.x, p.z, p.y); },
		[](const point& p) { return point(p.y, -p.x, p.z); },
		[](const point& p) { return point(p.z, -p.x, -p.y); },
		[](const point& p) { return point(-p.y, -p.x, -p.z); },
		[](const point& p) { return point(-p.z, -p.x, p.y); },
		[](const point& p) { return point(-p.z, p.y, p.x); },
		[](const point& p) { return point(p.y, p.z, p.x); },
		[](const point& p) { return point(p.z, -p.y, p.x); },
		[](const point& p) { return point(-p.y,-p.z, p.x); },
		[](const point& p) { return point(-p.z, -p.y, -p.x); },
		[](const point& p) { return point(-p.y, p.z, -p.x); },
		[](const point& p) { return point(p.z, p.y, -p.x); },
		[](const point& p) { return point(p.y, -p.z, -p.x); }
	};	
	vector<Scanner> scns;
	for(auto& l: inp){
		if(l.empty()) continue;
		if(l[1] == '-')
			scns.emplace_back(l);
		else{
			int x, y, z;
			char tr;
			stringstream ss(l);
			ss>>x>>tr>>y>>tr>>z;
			scns.back().points.emplace_back(x,y,z);
		}
	}
	genFingerprints(scns);
	bool finished = false;
	while(!finished){
		finished = true;
		for(auto& b: scns){
			if(b.solved == false || b.done) continue;
			finished = false;
			b.done = true;
			for(auto& s: scns){
				if(s.id != b.id && !s.solved){
					auto shared = sharedPoints(b.fps, s.fps);
					if(shared.size()>=66){
						// assert(shared.size() == 66);
						for(auto& perm: perms){
							vector<point> tempPerm = permutePoints(s.points, perm);
							map<point, int> counter;
							for(auto& en: b.points)
								for(auto& st: tempPerm)
									counter[en-st]++;
							auto [k, v] = maxValue(counter);
							if(v>=12){
								assert(v==12);
								s.solved = true;
								s.pos = b.pos+k;
								s.points = tempPerm;
								break;
							}
						}
					}
				}
			}
		}
	}
	set<point> beacons;
	for(auto& s: scns){
		for(auto& b: s.points)
			beacons.insert(b+s.pos);
		for(auto& s2: scns)
			p2 = max(p2, manhattan(s2.pos, s.pos));
	}
	p1 = beacons.size();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}