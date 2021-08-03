#include "../aoc.h"
#include <sstream>

vector<int> regs;

struct Node{
	int childN, metaN;
	vector<Node> children;
	vector<int> meta;

	Node():childN(0), metaN(0){}
	Node(int& i){
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
};

void p1(){
	int pos = 0;
	Node a(pos);
	cout<<"[P1] "<<a.sumMeta()<<endl;
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

	p1();
}