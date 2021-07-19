#include <iostream>
#include <fstream>
#include "../util.h"
#include "../prints.h"
#define ll long long

using namespace std;

unsigned long long gcd(unsigned long long int a, unsigned long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers
unsigned long long lcm(unsigned long long a, unsigned long long b)
{
    return (a / gcd(a, b)) * b;
}

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
			case 0:out+=to_string(m.x)+"_"+to_string(m.dx)+",";break;
			case 1:out+=to_string(m.y)+"_"+to_string(m.dy)+",";break;
			case 2:out+=to_string(m.z)+"_"+to_string(m.dz)+",";break;
		}
	}
	return out;
}

void updateMoons(vector<Moon>& moons){
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

int main(){
	fstream file("Day 12/input");
	string line;
	vector<Moon> moons;
	while(getline(file, line))
		moons.emplace_back(line);
	
	for(int it = 1;it<=1000;it++){
		// cout<<BOLD<<RED<<"Step "<<it<<RESET<<endl;
		updateMoons(moons);
	}
	ll p1 = 0;
	for(auto& m : moons){
		p1+=m.getEnergy();
	}
	cout<<"[P1] "<<p1<<endl;

	vector<ll> cycles(3);
	// cout<<hashState(moons,0)<<endl;
	
	map<string, int> seen[3];
	string hash;
	for(int i = 0;;i++){
		for(int state = 0;state<3;state++){
			hash = hashState(moons, state);
			if(cycles[i] == 0 && seen[state].insert(make_pair(hash, i)).second == false){
				cycles[state] = i-seen[state][hash];
				if(cycles[0] != 0 &&
				   cycles[1] != 0 &&
				   cycles[2] != 0){
					goto p2;
				}
			}
		}
		updateMoons(moons);
	}
	p2:
	cout<<"[P2] "<<lcm(cycles[0], lcm(cycles[1], cycles[2]))<<endl;
}