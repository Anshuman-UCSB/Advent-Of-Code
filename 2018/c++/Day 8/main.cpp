#include "../aoc.h"
#include <sstream>

vector<int> regs;

map<int, int> cache;

int globalId = 1;
struct Node{
	int id;
	int childN, metaN;
	vector<Node> children;
	vector<int> meta;

	Node():childN(0), metaN(0){}
	Node(int& i){
		id = globalId++;
		childN = regs[i++];
		metaN = regs[i++];
		for(int j = 0;j<childN;j++){
			children.emplace_back(i);
		}
		for(int j = 0;j<metaN;j++){
			meta.push_back(regs[i++]);
		}
	}

	int sumMeta(){
		int out = 0;
		for(auto& c: children){
			out+=c.sumMeta();
		}
		for(auto& v: meta){
			out+=v;
		}
		return out;
	}

	int p2(){
		if(cache.count(id))
			return cache[id];
		if(childN == 0){
			for(auto& v: meta){
				cache[id]+=v;
			}
		} else{
			for(auto& ind: meta){
				if(0<ind && ind<=childN){
					cache[id]+=children[ind-1].p2();
				}
			}
		}

		return cache[id];
	}
};

Node head;
void p1(){
	cout<<"[P1] "<<head.sumMeta()<<endl;
}

void p2(){
	cout<<"[P2] "<<head.p2()<<endl;
}

int main(){
	fstream file("Day 8/input");
	string line;
	getline(file, line);
	int c;
	stringstream ss(line);
	while(ss>>c){
		regs.push_back(c);
	}
	int pos = 0;
	head = Node(pos);
	p1();
	p2();
}