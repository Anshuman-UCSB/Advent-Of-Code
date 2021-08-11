#include "../aoc.h"
#include "../point.h"
#include <queue>

map<Point, char> m;
map<Point, int> dists;

void print(map<Point, char> m, Point p = Point()){
	Point tl, br;
	for(auto& [k, v]: m){
		updateRanges(tl, br, k, false);
	}
	if(p!= Point())
		m[p] = '@';
	
	for(int y = tl.y-1;y<=br.y+1;y++){
		for(int x = tl.x-1;x<=br.x+1;x++){
			if(m.count(Point(x,y)))
				cout<<m[Point(x,y)];
			else cout<<'#';
		}
		cout<<endl;
	}
}

void printDists(map<Point, char> m){
	Point tl, br;
	string Colors[4] = {RED, YELLOW, CYAN, BOLD};
	for(auto& [k, v]: m){
		updateRanges(tl, br, k, false);
	}
	for(auto& [p, d]: dists){
		m[p] = d;
	}
	for(int y = tl.y-1;y<=br.y+1;y++){
		for(int x = tl.x-1;x<=br.x+1;x++){
			if(m.count(Point(x,y))){
				if(m[Point(x, y)]<=42){
					cout<<Colors[(m[Point(x, y)]/10)%4];
					cout<<m[Point(x,y)]%10;
					cout<<RESET;
				}
				else
					cout<<m[Point(x,y)];
			}
			else cout<<'#';
		}
		cout<<endl;
	}
}
void printDists(){printDists(m);}

void print(){print(m);}

set<pair<Point, int>> cache;

void explore(Point p, const string& rgx, int start){
	// cout<<"Branch started from "<<p<<endl;
	if(cache.insert(make_pair(p, start)).second == false) return; //already visited
	int left, bar, right, stk;
	for(int i = start;i<rgx.size()-1;i++){
		// cout<<"At "<<i<<"	"<<"'"<<rgx[i]<<"'"<<endl;
		// cout<<"	"<<p<<endl;
		// print(m, p);
		// string t;
		// cin>>t;
		switch(rgx[i]){
			case 'N': m[p+Point(0,-1)] = '-'; p+=Point(0,-2); break;
			case 'S': m[p+Point(0, 1)] = '-'; p+=Point(0, 2); break;
			case 'W': m[p+Point(-1,0)] = '|'; p+=Point(-2,0); break;
			case 'E': m[p+Point( 1,0)] = '|'; p+=Point( 2,0); break;
			case '(': 
				left = i;
				bar = rgx.find('|', left+1);
				for(stk = 0, bar = left+1;stk || rgx[bar] != '|';bar++){
					if(rgx[bar] == '(') stk++;
					else if(rgx[bar] == ')') stk--;

				}
				right--;
				for(stk = 1, right = bar+1;stk;right++){
					if(rgx[right] == '(') stk++;
					else if(rgx[right] == ')') stk--;
				}
				right--;
				// cout<<"Branching on left part of tree, "<<left<<endl;
				explore(p, rgx, left+1);
				// cout<<"Branching on right part of tree, "<<bar<<endl;
				explore(p, rgx, bar+1);
				return;
			case '|':
				// cout<<"Left portion, hit end so skipping right portion "<<i<<endl;
				for(stk = 1;stk;i++){
					if(rgx[i] == '(') stk++;
					else if(rgx[i] == ')') stk--;
				}
				i--;
				break;
			case ')':
				// cout<<"Right portion, skipping delim "<<i<<endl;
				break;
		}
		m[p] = '.';
	}
	return;
}

void explore(const string& rgx){
	m[Point(0,0)] = 'X';
	explore(Point(0,0), rgx, 1);
}


Point deltas[4] = {Point(1,0),Point(-1,0),Point(0,-1),Point(0,1)};

void bfs(map<Point, char>& m){
	queue<pair<Point, int>> q;
	q.push(make_pair(Point(), 0));
	dists[Point()] = 0;

	while(!q.empty()){
		auto pr = q.front();
		auto& [p, d] = pr;
		q.pop();
		if(m.count(p) && m[p] != '.' && m[p]!= 'X') continue;
		// if(dists.insert(pr).second == false) continue;
		
		for(auto& dlt: deltas){
			if(m.count(p+dlt) == 0) continue;
			if(m[p+dlt] != '#'){
				auto tmp = p+2*dlt;
				if(dists.count(tmp) == 0){
					dists[tmp] = d+1;
					q.push(make_pair(tmp, d+1));
				}
			}
		}		
	}
}

int main(){
	fstream file("Day 20/input");
	string line;
	file>>line;
	explore(line);
	bfs(m);
	// cout<<dists<<endl;
	int p1 = 0;
	int p2 = 0;
	for(auto& [_,v]: dists){
		p1= max(p1, v);
		if(v>=998){
			p2++;
		}
	}
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	//8386 too low
	//8389 too low
	print();
	// printDists();
}