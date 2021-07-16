#include "../intcode.h"
#include "../util.h"
#include <utility>
#include <map>
#include <algorithm>

void printMap(map<pair<int, int>, bool> m){
	int lx(0), hx(0);
	int ly(0), hy(0);
	int x,y;
	for(auto& p: m){
		x = p.first.first;
		y = p.first.second;
		lx = min(lx, x);
		hx = max(hx, x);
		ly = min(ly, y);
		hy = max(hy, y);
	}
	
	vector<vector<string>> out(hy-ly+1, vector<string>(hx-lx+1, " "));
	for(auto& p: m){
		out[p.first.second-ly][p.first.first-lx] = p.second?"\033[1;37m█":("\033[0;30m█");
	}
	string prnt = "";
	reverse(out.begin(), out.end());
	for(auto& v: out){
		for(auto c: v){
			prnt+=c;
		}prnt+="\n";
	}prnt+=RESET;
	cout<<prnt;
}

void f(int part){
	map<pair<int, int>, bool> m;
	pair<int, int> pos = make_pair(0,0);
	int dir = 0; //up 0, right 1 etc.
	IntCode c(11);
	m[pos] = part-1;
	ll i = 0;
	while(!c.done){
		c.push(m[pos]);
		while(c.out.size() < 2){
			c.step();
			if(c.done)
				if(part == 1)
					goto p1;
				else
					goto p2;
		}
		// if(m.size() >2510)
		// 	c.print();
		m[pos] = c.pop();
		switch(c.pop()){
			case 0:dir--;if(dir<0){dir+=4;};break;
			case 1:dir++;dir%=4;break;
		}
		switch(dir){
			case 0:pos.second++;break;
			case 1:pos.first++;break;
			case 2:pos.second--;break;
			case 3:pos.first--;break;
		}
		// cout<<pos<<" "<<dir<<endl;
		// cout<<m.size()<<endl;
		// if(i++%1==0)
		// 	printMap(m);
	}

	p1:
	cout<<"[P1] "<<m.size()<<endl;
	return;

	p2:
	cout<<"[P2]"<<endl;
	printMap(m);
}

int main(){
	f(1);
	f(2);
}