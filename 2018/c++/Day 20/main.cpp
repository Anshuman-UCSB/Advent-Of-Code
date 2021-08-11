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
			case '^': case '$':
				break;
			default:
				if(c == 'N') p.y--; 
				else if(c == 'S') p.y++; 
				else if(c == 'W') p.x--; 
				else if(c == 'E') p.x++;
				else{
					cout<<"unknown "<<c<<endl;
					break;
				}
				dist++;
				// cout<<dist<<"	";
				if(m.count(p) == 0 || dist<m[p]){
					// cout<<m[p]<<" -> ";
					m[p] = dist;
					// cout<<m[p]<<endl;
				}
		}
	}

	int p2 = 0;
	int p1 = 0;
	for(auto& [k, v]: m){
		if(v>=1000) p2++;
		p1 = max(v, p1);
	}
	// cout<<m<<endl;
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
}