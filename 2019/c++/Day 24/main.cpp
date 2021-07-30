#include "../prints.h"
#include <fstream>
#define coord pair<int, int>
#define layer set<coord>
#define x first
#define y second

map<int, layer> g;
layer floor1;

static void printLayer( layer& l){
	for(int y = 0;y<5;y++){
		cout<<" ";
		for(int x = 0;x<5;x++){
			if(x == 2 && y == 2){
				cout<<"? ";
			}else
				cout<<(l.count(coord(x,y))?"# ":". ");
		}cout<<endl;
	}
}

static void printGrid( map<int, layer>& g){
	vector<string> out(6);
	for(auto& p: g){
		out[0]+=" Depth "+to_string(-p.first)+(p.first>0?"":" ")+" |";
		for(int y = 0;y<5;y++){
			for(int x = 0;x<5;x++){
				if(x==2 && y==2){
					out[y+1] += "? ";
				}
				else if(p.second.count(coord(x,y))){
					out[y+1] += "# ";
				}else{
					out[y+1] += ". ";
				}
			}
			out[y+1]+="|";
		}
	}
	for(auto& r: out){
		cout<<r<<endl;
	}
}

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

vector<coord> getCardinals(coord c){
	vector<coord> out;
	for(int i = 0;i<4;i++)
		out.emplace_back(c.x+dx[i], c.y+dy[i]);
	return out;
}

vector<coord> getLayerCardinals(coord c) {
	auto t = getCardinals(c);
	for(int i = 3;i>=0;i--){
		if(t[i].x == -1 || t[i].x == 5 || t[i].y == -1 || t[i].y == 5){
			t.erase(t.begin()+i);
		}
	}
	return t;
}

int getLayerNeighbor( layer& l, coord c){
	int out = 0;
	for(auto& t: getLayerCardinals(c))
		out+=l.count(t);
	return out;
}

int getGridNeighbor( map<int, layer>& g, coord c, int level){
	int out = getLayerNeighbor(g[level], c);
	if(c.x&1 && c.y&1)
		return out;
	if(c.x == 0)
		out+=g[level+1].count(coord(1,2));
	else if(c.x == 4)
		out+=g[level+1].count(coord(3,2));
	if(c.y == 0)
		out+=g[level+1].count(coord(2,1));
	else if(c.y == 4)
		out+=g[level+1].count(coord(2,3));
	
	if(c == coord(1,2)){
		for(int i = 0;i<5;i++)
			out+=g[level-1].count(coord(0,i));
	}
	else if(c == coord(3,2)){
		for(int i = 0;i<5;i++)
			out+=g[level-1].count(coord(4,i));
	}
	else if(c == coord(2,1)){
		for(int i = 0;i<5;i++)
			out+=g[level-1].count(coord(i,0));
	}
	else if(c == coord(2,3)){
		for(int i = 0;i<5;i++)
			out+=g[level-1].count(coord(i,4));
	}
	return out;	
}

layer generation( layer& l){
	layer out;
	set<coord> checks;
	for(auto& c: l){
		for(auto v: getLayerCardinals(c)) checks.insert(v);
		if(getLayerNeighbor(l,c) == 1){
			out.insert(c);
		}
	}

	for(auto& c: checks){
		if(l.count(c)) //cell is already alive, and checked
			continue;
		if(getLayerNeighbor(l,c) ==1 || getLayerNeighbor(l,c) ==2){
			out.insert(c);
		}
	}
	return out;
}

map<int, layer> generation( map<int, layer>& g){
	map<int, layer> tempG;
	for(auto& p: g){
		int level = p.first;
		layer l = p.second;
		for(auto& c: l){
			tempG[level].insert(c);
			for(auto& t: getLayerCardinals(c)){
				if(t!=coord(2,2))
					tempG[level].insert(t);
			}
			if(c.x == 0){
				tempG[level+1].emplace(1,2);
			}
			else if(c.x == 4){
				tempG[level+1].emplace(3,2);
			}
			if(c.y == 0){
				tempG[level+1].emplace(2,1);
			}
			else if(c.y == 4){
				tempG[level+1].emplace(2,3);
			}

			if(c == coord(1,2)){
				for(int i = 0;i<5;i++)
					tempG[level-1].emplace(0, i);
			}
			else if(c == coord(3,2)){
				for(int i = 0;i<5;i++)
					tempG[level-1].emplace(4, i);
			}
			else if(c == coord(2,1)){
				for(int i = 0;i<5;i++){
					tempG[level-1].emplace(i,0);
				}
			}
			else if(c == coord(2,3)){
				for(int i = 0;i<5;i++)
					tempG[level-1].emplace(i,4);
			}
		}
	}
	vector<pair<int, coord>> toRemove;
	// printGrid(tempG);
	for(auto& p: tempG){
		int level = p.first;
		layer l = p.second;
		for(auto& c: l){
			if(g[level].count(c)){
				//bug exists
				if(getGridNeighbor(g,c,level)!=1) //only keep if 1 neighbor
					toRemove.emplace_back(level, c);
			}else{
				int neighbors = getGridNeighbor(g, c, level);
				if(neighbors != 1 && neighbors != 2){
					toRemove.emplace_back(level, c);
				}
			}
		}
	}
	for(auto& p: toRemove){
		tempG[p.first].erase(p.second);
	}
	return tempG;
}

void p1(){
	set<layer> cache;
	// printLayer(floor1);
	while(cache.insert(floor1).second){
		floor1 = generation(floor1);
	}
	int out = 0;
	for(auto& c: floor1){
		out+=(1<<(c.x+c.y*5));
	}
	cout<<"[P1] "<<out<<endl;
}

void p2(){
	// cout<<"BEFORE"<<endl;
	// printGrid(g);
	for(int i = 0;i<200;i++){
		g = generation(g);
		// cout<<"\nAFTER "<<i+1<<endl;
		// printGrid(g);
		// cin>>trsh;
	}
	int p2 = 0;
	for(auto& p: g){
		p2+=p.second.size();
	}
	cout<<"[P2] "<<p2<<endl;
}

int main(){
	fstream file("Day 24/input");
	string line;
	int y = 0;
	while(getline(file, line)){
		for(int x=0;x<5;x++){
			if(line[x] == '#'){
				floor1.emplace(x,y);
			}
		}
		y++;
	}
	// cout<<floor1<<endl;
	// printLayer(floor1);
	g[0] = floor1;
	p1();
	p2();
}