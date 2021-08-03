#include "../aoc.h"
#include <sstream>
#include "../point.h"

struct light{
	Point pos, vel;
	light(int x = 0, int y = 0, int dx = 0, int dy = 0){
		pos = Point(x,y);
		vel = Point(dx, dy);
	}

	void iter(){
		pos+=vel;
	}
};

Point low, high;


static inline void iter(vector<light>& lights){
	for(auto& l: lights)
		l.iter();
}


int main(){
	fstream file("Day 10/input");
	string line;
	int x, y, dx, dy;
	vector<light> lights;

	while(getline(file, line)){
		stringstream ss(line);
		ss>>line>>x>>line>>y>>line>>line>>dx>>line>>dy;
		lights.emplace_back(x, y, dx, dy);
	}
}