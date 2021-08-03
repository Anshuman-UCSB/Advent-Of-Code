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

vector<light> eval(vector<light>& lights, int time){
	low = high = Point();
	vector<light> out(lights.size());
	for(int i = 0;i<lights.size();i++){
		out[i] = lights[i];
		out[i].pos+= time*out[i].vel;
		
		updateRanges(low, high, out[i].pos);
	}
	return out;
}

void print(vector<light>& lights){
	set<Point> points;
	for(auto& v: lights){
		points.insert(v.pos);
	}
	cout<<" 	";
	for(int x = low.x;x<=high.x;x++){
		cout<<abs(x%10);
	}cout<<endl;
	for(int y = low.y; y<=high.y; y++){
		cout<<" "<<y<<"	";
		for(int x = low.x;x<=high.x;x++){
			if(points.count(Point(x,y))){
				cout<<"#";
			}else cout<<" ";
		}cout<<endl;
	}
}

int main(){
	fstream file("Day 10/input");
	string line;
	int x, y, dx, dy;
	vector<light> lights;

	while(getline(file, line)){
		stringstream ss(line.substr(10));
		ss>>x>>line>>y;
		ss.seekg(12, ios_base::cur);
		ss>>dx>>line>>dy;
		lights.emplace_back(x, y, dx, dy);
	}
	int oldDist = 9999999;
	int dist = oldDist-1;
	int p2;
	for(p2 = 1;dist<oldDist;p2++){
		oldDist = dist;
		lights = eval(lights, 1);
		dist = low.distTo(high);
	}
	lights = eval(lights, -1);
	print(lights);
	cout<<p2<<endl;
}