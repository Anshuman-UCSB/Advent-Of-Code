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

bool movingAway(int time, vector<light>& lights){
	eval(lights, time);
	int dist = low.distTo(high);
	eval(lights, time+1);
	return (low.distTo(high)>dist);
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
	int l, h, m;
	for(h = 2; !movingAway(h, lights); h*=2){}
	l = h/2;
	while(l+1<h){
		// cout<<l<<"->"<<h<<endl;
		m = (h+l)/2;
		if(movingAway(m, lights)){
			h = m-1;
		}else{
			l = m+1;
		}
	}
	cout<<"[P1] "<<endl;
	lights = eval(lights, m-1);
	print(lights);
	cout<<"[P2] "<<m-1<<endl;
}