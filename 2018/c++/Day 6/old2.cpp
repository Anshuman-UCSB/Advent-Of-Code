#include "../aoc.h"
#include <sstream>

int main(){
	fstream file("Day 6/input");
	string line;
	int lx(999), ly(999), hx(0), hy(0);
	int x, y;
	char ch;
	char id='a';
	while(getline(file, line)){
		stringstream ss(line);
		ss>>x>>ch>>y;
		lx = min(lx, x);
		ly = min(ly, y);
		hx = max(hx, x);
		hy = max(hy, y);
		
	}
	
}