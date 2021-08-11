#include "../aoc.h"
#include "../point.h"
#define MODVAL 20183
int depth;
Point target;

vector<vector<int>> m;

int modMult(int a,int b){
	int out = 0;
	a%=MODVAL;
	while(b){
		if(b&1)
			out = (out+a)%MODVAL;
		a = (2*a)%MODVAL;
		b>>=1;
	}
	return out;
}

static void print(){
	for(auto& r: m){
		for(auto& c: r){
			switch(c){
				case 0:cout<<'.';break;
				case 1:cout<<'=';break;
				case 2:cout<<'|';break;

			}
		}
		cout<<endl;
	}
}

static void eval(int& x, int& y){
	if(x==0 || y==0){
		m[y][x] = (modMult(y, 48271)+modMult(x, 16807)+depth)%MODVAL;
	}else{
		m[y][x] = (modMult(m[y-1][x], m[y][x-1]) + depth)%MODVAL;
	}
}

static void fillGrid(){
	int maxX(0), maxY(0);
	for(int y = 0;y<m.size();y++){
		for(int x = 0;x<m[0].size();x++){
			eval(x,y);
			maxX = max(maxX, x);
			maxY = max(maxY, y);
		}
	}
	int p1=0;
	for(auto& r: m){
		for(auto& v: r){
			v%=3;
			p1+=v;
		}
	}
	p1-=at(m,target);
	cout<<"[P1] "<<p1<<endl;
}


int main(){
	fstream file("Day 22/input");
	string t;
	char tr;
	file>>t>>depth;
	file>>t>>target.x>>tr>>target.y;
	m = vector<vector<int>>(target.y+1, vector<int>(target.x+1, -1));
	fillGrid();
	// print();
}