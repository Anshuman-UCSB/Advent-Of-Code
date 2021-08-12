#include "../aoc.h"
#include <sstream>

struct bot{
	int x, y, z;
	int r;
	bot(){}
	bot(const string& line){
		stringstream ss(line);
		char t;
		ss>>t>>t>>t>>t>>t>>x;
		ss>>t>>y>>t>>z>>t>>t>>t>>t>>r;
	}	

	bool inRange(const bot& b){
		int dist = 0;
		dist+=abs(x-b.x);
		if(dist>r) return false;
		dist+=abs(y-b.y);
		if(dist>r) return false;
		dist+=abs(z-b.z);
		if(dist>r) return false;
		return true;
	}
	
	int distTo(const bot& b){
		return abs(x-b.x) + abs(y-b.y) + abs(z-b.z);
	}
};

ostream& operator<<(ostream& os, const bot& b){
	os<<"("<<b.x<<", "<<b.y<<", "<<b.z<<")	r="<<b.r;
	return os;
}

int main(){
	fstream file("Day 23/input");
	string line;
	vector<bot> bots;
	int strongest = 0;
	while(getline(file, line)){
		bots.emplace_back(line);
		if(bots.back().r > bots[strongest].r){
			strongest = bots.size()-1;
		}
	}
	// for(auto& b: bots)cout<<b<<endl;

	int p1 = 0;
	for(auto& b: bots){
		if(bots[strongest].inRange(b)) p1++;
	}
	cout<<"[P1] "<<p1<<endl;
	set<pair<int, int>> s;
	int d;
	for(auto& b: bots){
		d = abs(b.x)+abs(b.y)+abs(b.z);
		s.insert(make_pair(max(0,d-b.r), 1));
		s.insert(make_pair(d+b.r+1, -1));
	}
	int count(0), maxCount(0), result(0);
	for(auto& [dist, e] : s){
		count+=e;
		if(count>maxCount){
			result = dist;
			maxCount = count;
		}
	}
	cout<<"[P2] "<<result<<endl;
}