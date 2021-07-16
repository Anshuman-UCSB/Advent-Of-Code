#include <iostream>
#include <fstream>
#include "../util.h"

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
		// inp.pop_back();
		// inp.push_back(',');
		cout<<inp<<endl;
	}
};

int main(){
	fstream file("Day 12/input");
	string line;
	while(getline(file, line)){
		Moon m(line);
	}
}