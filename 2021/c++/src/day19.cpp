#include "AOC.h"
#include <cmath>
#include <cassert>
#define coord tuple<int, int, int>
#define fp tuple<int, int, int>
struct Scanner{
	int id;
	bool solved;
	coord pos;
	vector<coord> beacons;
	vector<fp> fingerprints;
	map<fp, pair<coord, coord>> fpmap;
	Scanner():solved(false){}
	Scanner(string& inp):Scanner(){
		stringstream ss(inp);
		string t;
		ss>>t>>t>>id;
	}
};

coord operator+(const coord& a, const coord& b){
	auto [x1,y1,z1] = a;
	auto [x2,y2,z2] = b;
	return coord(x2+x1, y2+y1, z2+z1);
}


coord operator-(const coord& a, const coord& b){
	auto [x1,y1,z1] = a;
	auto [x2,y2,z2] = b;
	return coord(x2-x1, y2-y1, z2-z1);
}

int dist(const coord& a, const coord& b){
	auto [x1,y1,z1] = a;
	auto [x2,y2,z2] = b;
	return (pow(x2-x1, 2)+pow(y2-y1, 2)+pow(z2-z1, 2));
}

int manhattan(const coord& a, const coord& b){
	auto [x1,y1,z1] = a;
	auto [x2,y2,z2] = b;
	return (abs(x2-x1)+abs(y2-y1)+abs(z2-z1));
}
int offmin(const coord& a, const coord& b){
	int ans = 1000;
	auto [x1, y1, z1] = a;
	auto [x2, y2, z2] = b;
	ans = min(ans, abs(x2-x1));
	ans = min(ans, abs(y2-y1));
	ans = min(ans, abs(z2-z1));
	return ans;
}
int offmax(const coord& a, const coord& b){
	int ans = 0;
	auto [x1, y1, z1] = a;
	auto [x2, y2, z2] = b;
	ans = max(ans, abs(x2-x1));
	ans = max(ans, abs(y2-y1));
	ans = max(ans, abs(z2-z1));
	return ans;
}
vector<vector<coord>> permute(vector<coord>& base){
	vector<vector<coord>> out(24, vector<coord>(base.size()));
	for(int j = 0;j<base.size();j++){
		auto [x,y,z] = base[j];
		out[0][j] = coord(+x, +y, +z);
		out[1][j] = coord(+y, +z, +x);
		out[2][j] = coord(+z, +x, +y);
		out[3][j] = coord(+z, +y, -x);
		out[4][j] = coord(+y, +x, -z);
		out[5][j] = coord(+x, +z, -y);
		out[6][j] = coord(+x, -y, -z);
		out[7][j] = coord(+y, -z, -x);
		out[8][j] = coord(+z, -x, -y);
		out[9][j] = coord(+z, -y, +x);
		out[10][j] = coord(+y, -x, +z);
		out[11][j] = coord(+x, -z, +y);
		out[12][j] = coord(-x, +y, -z);
		out[13][j] = coord(-y, +z, -x);
		out[14][j] = coord(-z, +x, -y);
		out[15][j] = coord(-z, +y, +x);
		out[16][j] = coord(-y, +x, +z);
		out[17][j] = coord(-x, +z, +y);
		out[18][j] = coord(-x, -y, +z);
		out[19][j] = coord(-y, -z, +x);
		out[20][j] = coord(-z, -x, +y);
		out[21][j] = coord(-z, -y, -x);
		out[22][j] = coord(-y, -x, -z);
		out[23][j] = coord(-x, -z, -y);
	}

	
	return out;
}

vector<fp> sharedFingerprints(const Scanner& a, const Scanner& b){
	vector<fp> fps;
	set_intersection(begin(a.fingerprints), end(a.fingerprints), begin(b.fingerprints), end(b.fingerprints), back_inserter(fps));
	return fps;
}

chrono::time_point<std::chrono::steady_clock> day19(input_t& inp){
	int p1(0), p2(0);
	vector<Scanner> scanners;
	for(auto& l: inp){
		if(l.empty()) continue;
		if(l[1] == '-'){
			scanners.emplace_back(l);
		}else{
			int x, y, z;
			char tr;
			stringstream ss(l);
			ss>>x>>tr>>y>>tr>>z;
			scanners.back().beacons.push_back(coord(x,y,z));
		}
	}
	scanners[0].solved = true;
	scanners[0].pos = coord(0,0,0);
	for(auto& s: scanners){
		for(int i = 0;i<s.beacons.size()-1;i++)
			for(int j = i+1;j<s.beacons.size();j++){
				s.fingerprints.emplace_back(
					dist(s.beacons[i], s.beacons[j]),
					offmin(s.beacons[i], s.beacons[j]),
					offmax(s.beacons[i], s.beacons[j])
				);
				s.fpmap[s.fingerprints.back()] = make_pair(s.beacons[i], s.beacons[j]);
			}
		sort(s.fingerprints.begin(), s.fingerprints.end());
	}
	for(auto& base: scanners){
		if(base.solved == false) continue;
		for(auto& s: scanners){
			if(s.id!=base.id && s.solved == false){
				vector<fp> fps = sharedFingerprints(s, base);
				if(fps.size() >= 66){
					set<coord> sPoints, bPoints;
					for(auto& f: fps){
						coord a, b;
						tie(a,b) = s.fpmap[f];
						sPoints.insert(a);
						sPoints.insert(b);
						tie(a,b) = base.fpmap[f];
						bPoints.insert(a);
						bPoints.insert(b);
					}
					vector<coord> sPointsV;
					for(auto& c: s.beacons){
						if(sPoints.count(c))
							sPointsV.push_back(c);
					}
					for(auto& perm: permute(sPointsV)){
						map<coord, int> tCount;
						for(auto& p1: perm)
							for(auto& p2: bPoints){
								tCount[p1-p2]++;
							}
						for(auto& [k,v]: tCount){
							if(v>=12){
								cout<<base.id<<"->"<<s.id<<"	"<<k<<endl;
								s.solved = true;
								s.pos = base.pos + k;
								s.beacons = perm;
								cout<<s.pos<<endl;
								cout<<s.beacons<<endl;
								exit(0);
								// goto solvedOne;
							}
						}
					}
					solvedOne:;
				}
			}
		}
	}
	for(auto& s1: scanners){
		cout<<s1.id<<"	"<<s1.pos<<endl;
		// for(auto& s2: scanners){
		// 	cout<<s1.pos<<"	"<<s2.pos<<"	"<<manhattan(s1.pos, s2.pos)<<endl;
		// 	p2 = max(p2, manhattan(s1.pos, s2.pos));
		// }
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}