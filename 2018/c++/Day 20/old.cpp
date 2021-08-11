#include "../aoc.h"
#include "../point.h"

map<Point, char> m;


void explore(Point p, const string& rgx, int ind, int next = 0){
	m[p] = '.';
	int left, right, bar;
	int nest;
	string t;
	for(int i = ind;;i++){
		const char& s = rgx[i];
		cout<<i<<":	"<<p<<"	"<<"'"<<s<<"'"<<endl;
		cin>>t;
		switch(s){
			case 'W': m[p+Point(-1,0)]='|'; p+=Point(-2,0); break;
			case 'E': m[p+Point(1,0)]='|';  p+=Point( 2,0); break;
			case 'N': m[p+Point(0,-1)]='-'; p+=Point(0,-2); break;
			case 'S': m[p+Point(0,1)]='-';  p+=Point(0,2); break;
			case '(': //branch
				left = i; 					// ( pos
				bar  = rgx.find('|', i+1);	// | pos
				for(right = bar, nest = 1;nest; right++){
					if(rgx[right] == '(') nest++;
					if(rgx[right] == ')') nest--;
				}
				cout<<left<<", "<<bar<<", "<<right<<endl;
				cout<<"Branching"<<endl;
				explore(p, rgx, left+1, right);
				explore(p, rgx, bar+1,  right);
				return;
				break;

			case '|':
			case ')':
				cout<<"next: "<<next<<endl;
				explore(p, rgx, next);
				return;
			case '$':
				return;
		}
		m[p] = '.';
	}
	return;
}
void explore(const string& rgx){
	explore(Point(0,0), rgx, 1);
	m[Point(0,0)] = 'X';
}

static void print(){
	Point tl, br;
	for(auto& [k, v]: m){
		updateRanges(tl, br, k);
	}
	for(int y = tl.y-1;y<=br.y+1;y++){
		for(int x = tl.x-1;x<=br.x+1;x++){
			cout<<(m[Point(x,y)]?m[Point(x,y)]:'#');
		}cout<<endl;
	}
}

int main(){
	fstream file("Day 20/input");
	string line;
	file>>line;
	explore(line);
	print();
}