	#include "../aoc.h"
#include <sstream>

struct claim{
	int x, y, w, h;
	claim(int x = -1, int y = -1, int w = -1, int h = -1):x(x),y(y),w(w),h(h){}

	bool inline contains(int x1, int y1){
		return (x1>=x && x1<x+w && y<=y1 && y1<y+h);
	}	
};

int main(){
	Timer t;
	vector<claim> v;
	fstream file("Day 3/input");
	string line;
	char ch;
	string s;
	int x, y, w, h;
	int lx, hx, ly, hy;
	lx=ly=999999;
	hx = hy =0;
	while(getline(file, line)){
		stringstream ss(line);
		ss>>s>>s>>x>>ch>>y>>ch>>w>>ch>>h;
		lx = min(lx, x);
		ly = min(ly, y);
		hx = max(hx, x);
		hy = max(hy, y);
		// cout<<x<<", "<<y<<", "<<w<<", "<<h<<endl;
		v.emplace_back(x,y,w,h);
	}
	bool flag;
	int p1 = 0;
	for(x = lx; x<=hx;x++){
		for(y = ly;y<=hy;y++){
			flag = false;
			for(auto& clm: v){
				if(clm.contains(x,y)){
					if(flag){
						// cout<<x<<", "<<y<<endl;
						p1++;
						break;
					}
					flag = true;
				}
			}
		}
	}
	cout<<"[P1] "<<p1<<endl;
	t.end();
}