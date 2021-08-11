#include "../aoc.h"
#include "../point.h"

map<Point, char> m;


static void print(){
	Point tl, br;
	m[Point()] = 'X';
	for(auto& [k, v]: m){
		updateRanges(tl, br, k);
	}
	for(int y = tl.y-1;y<=br.y+1;y++){
		for(int x = tl.x-1;x<=br.x+1;x++){
			if(m.count(Point(x,y)))
				cout<<m[Point(x,y)];
			else
				cout<<"#";
		}cout<<endl;
	}
}
static void print(vector<Point> points){
	Point tl, br;
	auto cp = m;
	cp[Point()] = 'X';
	for(auto& p : points){
		cp[p] = '@';
	}
	for(auto& [k, v]: cp){
		updateRanges(tl, br, k, false);
	}
	for(int y = tl.y-1;y<=br.y+1;y++){
		for(int x = tl.x-1;x<=br.x+1;x++){
			if(cp.count(Point(x,y)))
				cout<<cp[Point(x,y)];
			else
				cout<<"#";
		}cout<<endl;
	}
}

vector<Point> explore(vector<Point> points, const string& rgx, int start, int end){
	int left, bar, right, depth;
	for(int i = start;i<end;i++){
		print(points);
		string t;
		cin>>t;
		switch(char c = rgx[i]; c){
			case 'W':
				for(auto& p: points){
					m[p+Point(-1,0)] = '|';	
					p+=Point(-2,0);
					m[p] = '.';
				}
				break;
			case 'E':
				for(auto& p: points){
					m[p+Point( 1,0)] = '|';	
					p+=Point( 2,0);
					m[p] = '.';
				}
				break;
			case 'N':
				for(auto& p: points){
					m[p+Point(0,-1)] = '-';
					p+=Point(0,-2);
					m[p] = '.';
				}
				break;
			case 'S':
				for(auto& p: points){
					m[p+Point(0, 1)] = '-';
					p+=Point(0, 2);
					m[p] = '.';
				}
				break;
			case '(':
				left = i;
				bar = rgx.find('|', left);
				for(right = bar+1, depth = 1;depth;right++){
					if(rgx[right] == ')') depth--;
					else if(rgx[right] == '(') depth++;
				}
				right--;
				cout<<"Branching with "<<points<<endl;
				vector<Point> temp  = explore(points, rgx, left+1, bar);
				vector<Point> temp2  = explore(points, rgx, bar+1, right);

				points = temp;
				points.insert(points.end(), temp2.begin(), temp2.end());
				set<Point> uniq(points.begin(), points.end());
				points.assign(uniq.begin(), uniq.end());
				cout<<"At this point active points are "<<points<<endl;
				i = right;
		}
	}
	return points;
}
void explore(const string& rgx){
	explore(vector<Point>(1), rgx, 1, rgx.size()-1);
	m[Point(0,0)] = 'X';
}


int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int p1(){
	set<Point> visited;
	set<Point> q, t;
	q.insert(Point(0,0));
	visited.insert(Point());
	int dist;
	cout<<m<<endl;
	for(dist = 0; !q.empty(); dist++){
		for(auto& p: q){
			for(int i = 0;i<4;i++){
				if(m.count(p+Point(dx[i], dy[i])) && m[p+Point(dx[i], dy[i])] != '#'){
					cout<<p+Point(dx[i], dy[i])<<":	";
					cout<<"'"<<m[p+Point(dx[i], dy[i])]<<"'"<<endl;
					if(visited.insert(p+Point(2*dx[i], 2*dy[i])).second){
						t.insert(p+Point(2*dx[i], 2*dy[i]));
					}
				}
			}
		}
		print();
		cout<<q<<endl;
		// string tm;
		// cin>>tm;
		q.swap(t);
		t.clear();
	}
	return dist-1;
}

int main(){
	fstream file("Day 20/input");
	string line;
	file>>line;
	explore(line);
	print();
	// cout<<"[P1] "<<p1()<<endl;
}