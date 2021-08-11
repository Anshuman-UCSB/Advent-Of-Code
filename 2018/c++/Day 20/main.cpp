#include "../aoc.h"
#include "../point.h"
#include <stack>

map<Point, int> m;
stack<pair<Point, int>> s;

int main(){
	fstream file("Day 20/input");
	string line;
	file>>line;
	Point p;
	int dist = 0;
	for(auto& c: line){
		switch(c){
			case '(': s.push(make_pair(p, dist)); 		break;
			case ')': tie(p, dist) = s.top(); s.pop(); 	break;
			case '|': tie(p, dist) = s.top(); 			break;
			case 'N': 
		}
	}
}