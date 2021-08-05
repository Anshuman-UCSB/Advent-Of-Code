#include "../aoc.h"
#include "../point.h"
#include <bitset>

struct cart{
	Point p;
	short turn;
	short dir;
	char onSquare;
	cart(int x, int y, short dir):p(x,y), turn(0), dir(dir){
		switch(dir){
			case 0:
			case 2: onSquare = '|';break;
			case 1:
			case 3: onSquare = '-';break;
		}
	}
};

Point dirMod[4] = {Point(0, -1), Point(1,0), Point(0,1), Point(-1,0)};
char sprite[4] = {'^','>','v','<'};

bool operator<(const cart& a, const cart& b){
	return a.p<b.p;
}

ostream& operator<<(ostream& os, const cart& c){
	os<<"	Cart: "<<c.p<<"	"<<c.turn<<"	"<<c.dir<<"	"<<c.onSquare<<endl;
	return os;
}

bool p1flag = false;

void step(vector<string>& m, vector<cart>& carts){
	Point next;
	sort(carts.begin(), carts.end());
	for(auto& c: carts){
		if(c.p.x == -1) continue;
		next = c.p + dirMod[c.dir];
		switch(m[next.y][next.x]){
			case '-':
			case '|':
				m[c.p.y][c.p.x] = c.onSquare;
				c.p = next;
				c.onSquare = m[c.p.y][c.p.x];
				m[c.p.y][c.p.x] = sprite[c.dir];
				break;
			case '\\':
				m[c.p.y][c.p.x] = c.onSquare;
				if(c.p.y == next.y){c.dir+=1;c.dir%=4;}
				else{c.dir+=3;c.dir%=4;}
				c.p = next;
				c.onSquare = m[c.p.y][c.p.x];
				m[c.p.y][c.p.x] = sprite[c.dir];
				break;
			case '/':
				m[c.p.y][c.p.x] = c.onSquare;
				if(c.p.y == next.y){c.dir+=3;c.dir%=4;}
				else{c.dir+=1;c.dir%=4;}
				c.p = next;
				c.onSquare = m[c.p.y][c.p.x];
				m[c.p.y][c.p.x] = sprite[c.dir];
				break;				
			case '+':
				m[c.p.y][c.p.x] = c.onSquare;
				c.p = next;
				c.onSquare = m[c.p.y][c.p.x];
				switch(c.turn){
					case 0: c.dir = (c.dir+3)%4; break;
					case 2: c.dir = (c.dir+1)%4; break;
				}
				c.turn = (c.turn+1)%3;
				m[c.p.y][c.p.x] = sprite[c.dir];
				break;
			default:
				//crash occured
				if(p1flag == false){
					cout<<"[P1] "<<next.x<<","<<next.y<<endl;
					p1flag=true;
				}
				for(auto& cr: carts){
					if(cr.p == c.p || cr.p == next){
						m[cr.p.y][cr.p.x] = cr.onSquare;
						cr.p = Point(-1,-1);
					}
				}
		}
	}
	for(int i = carts.size()-1;i>=0;i--){
		if(carts[i].p.x == -1){
			carts.erase(carts.begin()+i);
		}
	}
	
}

static void print(vector<string>& m , vector<cart>& carts){
	for(auto& v: m){
		cout<<v<<endl;
	}
}

void p1(vector<string>& m, vector<cart>& carts){
	// print(m, carts);
	for(int i = 1;carts.size()>1;i++){
		step(m, carts);
		// cout<<"Time "<<i<<":"<<endl;
		// print(m, carts);
		// cout<<carts<<endl;
	}
	cout<<"[P2] "<<carts[0].p.x<<","<<carts[0].p.y<<endl;
}

int main(){
	fstream file("Day 13/input");
	string line;
	vector<string> m;
	vector<cart> carts;
	while(getline(file, line)){
		m.push_back(line);
		for(int x = 0;x<line.size();x++)
			switch(m.back()[x]){
				case '^':
					carts.emplace_back(x,m.size()-1, 0);break;
				case '>':
					carts.emplace_back(x,m.size()-1, 1);break;
				case 'v':
					carts.emplace_back(x,m.size()-1, 2);break;
				case '<':
					carts.emplace_back(x,m.size()-1, 3);break;
			}
	}
	// cout<<carts<<endl;
	// for(const auto& l: m)cout<<l<<endl;
	p1(m, carts);
}