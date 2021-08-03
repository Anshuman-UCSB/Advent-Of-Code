#pragma once
#include <iostream>
using namespace std;
struct Point{
	int x, y;
	Point(int x = 0, int y = 0):x(x), y(y){}

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

	Point operator+(const Point& p){
		return Point(x+p.x, y+p.y);
	}
	Point operator-(const Point& p){
		return Point(x-p.x, y-p.y);
	}

	bool operator<(Point& p){
		return x<p.x | (x==p.x && y<p.y);
	}

	bool operator<(const Point& p) const {
		return x<p.x | (x==p.x && y<p.y);
	}

	void min(const Point& p){
		if(p<*this){
			*this = p;
		}
	}
	void max(const Point& p){
		if(*this<p){
			*this = p;
		}
	}
};

ostream& operator<<(ostream& os, const Point& p){
	os<<"("<<p.x<<", "<<p.y<<")";
	return os;
}

