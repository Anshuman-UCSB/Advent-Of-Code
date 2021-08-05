#include "../aoc.h"
#include "../point.h"
#include <tuple>
#include <cassert>

#define ll long long
#define smallInt int
#define GRIDSIZE 300

vector<vector<smallInt>> m(GRIDSIZE+1, vector<smallInt>(GRIDSIZE+1, 0));
int inp;

static smallInt evalPower(int x, int y, int inp){
	if(x==0||y==0) return 0;
	ll combined = (x+10)*y + inp;
	combined*=(x+10);
	return combined/100%10 -5;
}

void test(){
	assert(evalPower(122,79, 57)==-5);
	assert(evalPower(217,196, 39)==0);
	assert(evalPower(101,153, 71)==4);
}

static inline int sumSquare(int x, int y, int size){
	return m[y-1][x-1]+m[y+size-1][x+size-1] - m[y-1][x+size-1] - m[y+size-1][x-1];
}

pair<int, tuple<int, int, int>> solve(int size){
	int sum=0;
	tuple<int, int, int> out;
	int temp;
	for(int y = 1;y<=GRIDSIZE-size;y++){
		for(int x = 1;x<=GRIDSIZE-size;x++){
			if(temp=sumSquare(x, y, size); temp>sum){
				out = make_tuple(x, y, size);
				sum = temp;
			}
		}
	}
	return make_pair(sum, out);
}

int main(){
	test();
	fstream file("Day 11/input");
	string line;
	getline(file, line);
	inp = stoi(line);
	// inp = 42;
	for(int y = 1;y<=GRIDSIZE;y++){
		for(int x = 1;x<=GRIDSIZE;x++){
			m[y][x] = -m[y-1][x-1]+evalPower(x, y, inp)+m[y-1][x]+m[y][x-1];
		}
	}
	auto out = solve(3);
	cout<<"[P1] "<<get<0>(out.second)<<","<<get<1>(out.second)<<endl;
	pair<int, tuple<int, int, int>> t;
	for(int i = 4;i<300;i++){
		if(t = solve(i); t.first > out.first){
			out = t;
		}
	}
	cout<<"[P2] "<<get<1>(out.second)<<","<<get<1>(out.second)<<","<<get<2>(out.second)<<endl;
	
	
}