#pragma once
#include <iostream>
using namespace std;
struct Point{
	int x, y;
	Point(int x = 0, int y = 0):x(x), y(y){}

	Point(const Point& p){
		x = p.x;
		y = p.y;
	}

	int getx() const{return x;}
	int gety() const{return y;}

	Point& operator=(const Point& p){
		if(this != &p){
			x = p.getx();
			y = p.gety();
		}
		return *this;
	}

	Point& operator+=(const Point& p){
		x+=p.x; y+=p.y;
		return *this;
	}
	Point& operator++(int a){
		x++; y++;
		return *this;
	}
	Point& operator--(int a){
		x--; y--;
		return *this;
	}
	
	Point& operator-=(const Point& p){
		x-=p.x; y-=p.y;
		return *this;
	}

	Point operator+(const Point& p) const{
		return Point(x+p.x, y+p.y);
	}

	Point operator-(const Point& p){
		return Point(x-p.x, y-p.y);
	}

	bool operator<(Point& p){
		return y<p.y | (y==p.y && x<p.x);
	}

	bool operator<(const Point& p) const {
		return y<p.y | (y==p.y && x<p.x);
	}
	bool operator==(const Point& p) const {
		return y==p.y && x==p.x;
	}
	bool operator!=(const Point& p) const {
		return !(p==*this);
	}

	void min(const Point& p){
		x = std::min(x, p.x);
		y = std::min(y, p.y);
	}
	void max(const Point& p){
		x = std::max(x, p.x);
		y = std::max(y, p.y);
	}

	int distTo(const Point& p) const{
		return abs(p.y-y)+abs(p.x-x);
	}

	vector<Point> getNeighbors() const{
		return vector<Point>({Point(x, y-1), Point(x-1,y), Point(x+1, y), Point(x,y+1)});
	}
};

Point operator*(const Point& p, const int& sc){
	return Point(sc*p.x, sc*p.y);
}

Point operator*(const int& sc, const Point& p){
	return Point(sc*p.x, sc*p.y);
}

void updateRanges(Point& low, Point& high, const Point& p){
	if((low.x || low.y) == 0){
		low = p;
	}else
		low.min(p);
	if((high.x || high.y) == 0){
		high = p;
	}else
		high.max(p);
}

ostream& operator<<(ostream& os, const Point& p){
	os<<"("<<p.x<<", "<<p.y<<")";
	return os;
}

