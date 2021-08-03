#include "../aoc.h"
#include "../point.h"
#include <cassert>

#define ll long long

static short evalPower(const Point& p, int inp){
	ll combined = (p.x+10)*p.y + inp;
	combined*=(p.x+10);
	return combined/100%10 -5;
}

void test(){
	assert(evalPower(Point(122,79), 57)==-5);
	assert(evalPower(Point(217,196), 39)==0);
	assert(evalPower(Point(101,153), 71)==4);
}

static inline int pointToInd(const Point& p){
	return (p.x-1)+(p.y-1)*300;
}

static inline Point indToPoint(const int& n){
	return Point(n%300+1, n/300+1);
}

vector<short> m(300*300);

int eval(const Point& p, int size){
	int out = 0;
	for(int x = p.x; x<p.x+size;x++){
		for(int y = p.y; y<p.y+size;y++){
			out+=m[pointToInd(Point(x, y))];
		}
	}
	return out;
}

Point maxSlidingFrame(int size){
	int maxSize = 0;
	Point out;
	for(int y = 1;y<300-size; y++){
		for(int x = 1;x<300-size; x++){
			if(int e = eval(Point(x, y), size); e>maxSize){
				maxSize = e;
				out = Point(x, y);
			}
		}
	}

	return out;	
}

int main(){
	test();
	fstream file("Day 11/input");
	string line;
	getline(file, line);
	int inp = stoi(line);
	for(int i = 0;i<300*300;i++)
		m[i] = evalPower(indToPoint(i), inp);
	Point p1 = maxSlidingFrame(3);
	cout<<"[P1] "<<p1.x<<","<<p1.y<<endl;
}