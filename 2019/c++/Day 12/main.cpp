#include <iostream>
#include <fstream>
#include "../util.h"
#include "../prints.h"
#define ll long long

using namespace std;

struct Moon{
	int x, y, z;
	int dx, dy, dz;
	Moon(){
		x = y = z = dx = dy = dz = 0;
	}
	Moon(string inp){
		dx = dy = dz = 0;
		// <x=-1, y=0, z=2>
		inp = inp.substr(3);
		x = stoi(inp.substr(0, inp.find(",")));
		inp = inp.substr(1+inp.find("="));
		y = stoi(inp.substr(0, inp.find(",")));
		inp = inp.substr(1+inp.find("="));
		z = stoi(inp.substr(0, inp.find(">")));
	}

	ll getEnergy(){
		return (abs(x)+abs(y)+abs(z))*(abs(dx)+abs(dy)+abs(dz));
	}

	void updateGravity(const Moon& m){
		if(m.x>x){dx++;}
		else if(m.x<x){dx--;}
		if(m.y>y){dy++;}
		else if(m.y<y){dy--;}
		if(m.z>z){dz++;}
		else if(m.z<z){dz--;}
	}

	void updatePos(){
		x+=dx;
		y+=dy;
		z+=dz;
	}
};
ostream& operator<<(ostream& os, const Moon& m)
{
    os<<"("<<m.x<<", "<<m.y<<", "<<m.z<<")	<"<<m.dx<<", "<<m.dy<<", "<<m.dz<<">";
    return os;
}

string hashState(vector<Moon>& moons, int var){
	string out = "";
	for(auto& m: moons){
		switch(var){
			case 0:out+=m.x+"_"+m.dx+",";break;
			case 1:out+=m.y+"_"+m.dy+",";break;
			case 2:out+=m.z+"_"+m.dz+",";break;
		}
	}
	return out;
}

int main(){
	fstream file("Day 12/input");
	string line;
	vector<Moon> moons;
	while(getline(file, line))
		moons.emplace_back(line);
	
	for(int it = 1;it<=1000;it++){
		// cout<<BOLD<<RED<<"Step "<<it<<RESET<<endl;
		for(auto& m: moons){
			for(auto& n: moons){
				m.updateGravity(n);
			}
		}
		for(auto& m: moons){
			m.updatePos();
			// cout<<"	"<<m<<endl;
		}
	}
	ll p1 = 0;
	for(auto& m : moons){
		p1+=m.getEnergy();
	}
	cout<<"[P1] "<<p1<<endl;

	ll xCycle;
	for()
}