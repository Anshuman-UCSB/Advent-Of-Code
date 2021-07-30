#include <iostream>
#include "../intcode.h"
#include <algorithm>
#include <set>
#include "../prints.h"
#include <utility>

IntCode inp(19);
IntCode c(19);

void reset(){
	c.ind = 0;
	c.rel = 0;
	c.inp.clear();
	c.regs = inp.regs;
	c.done = false;
}

bool testSquare(int x, int y){
	c.push(x);
	c.push(y);
	c.run();
	reset();
	return c.pop();
}

const int squareSize = 100;
pair<bool, int> test(int y){
	int x = y;
	for(;testSquare(x,y)==false;x--){}
	for(;testSquare(x,y)==true ;x--){}
	x++;
	if(y<squareSize)return make_pair(false, 0);
	// cout<<x<<", "<<y<<endl;
	return make_pair(testSquare(x+squareSize-1, y-squareSize+1), x*10000+y-squareSize+1);
}

int main(){
	const int gridSize =50;
	vector<vector<bool>> m(gridSize,vector<bool>(gridSize));
	for(int i =0;i<gridSize;i++){
		for(int j = 0;j<gridSize;j++){
			m[i][j] = testSquare(j, i);
		}
	}
	int p1 = 0;
	for(auto& r: m){
		for(auto v: r){
			// cout<<(v?"#":".");
			p1+=v;
		}//cout<<endl;
	}
	cout<<"[P1] "<<p1<<endl;
	int l(0), h(100), mid;
	for(;test(h).first==false;h*=2){} // while h doesn't fit it, double
	l = h/2;
	while(l<=h){
		mid = (l+h)/2;
		if(l==h){
			// cout<<"Found at y="<<l<<endl;
			cout<<"[P2] "<<test(l).second<<endl;
			break;
		}
		if(test(mid).first){
			h = mid;
		}else{
			l = mid+1;
		}
	}
	//8151016 too high
	//8071006 try
}