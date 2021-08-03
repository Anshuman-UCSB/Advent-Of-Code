#include "../aoc.h"
#include <sstream>
#include <cassert>
#define Node pair<unsigned, unsigned>
#define next first
#define prev second

void print(vector<Node>& r, unsigned cur, unsigned player){
	cout<<"["<<player<<"]";
	bool start = true;
	for(unsigned i = 0;i!=0 || start ; i = r[i].next){
		start = false;
		if(i == cur){
			cout<<"("<<i<<") ";
		}else{
			cout<<" "<<i<<"  ";
		}
	}
	cout<<endl;
}

long eval(unsigned int players, unsigned int marbles){
	vector<Node> regs(marbles+1);
	vector<long> scores(players+1);
	unsigned int size = 1;
	unsigned int cur = 0;
	for(int i = 1;i<=marbles;i++){
		if(i%23){
			cur = regs[cur].next;
			regs[i] = make_pair(regs[cur].next, cur);
			regs[regs[cur].next].prev = i;
			regs[cur].next = i;
			size++;
			cur = regs[cur].next;
		}else{
			scores[i%players]+=i;
			for(int _ = 0;_<7;_++){
				cur = regs[cur].prev;
			}
			// cout<<"Removing "<<cur<<endl;
			regs[regs[cur].prev].next = regs[cur].next;
			regs[regs[cur].next].prev = regs[cur].prev;
			scores[i%players]+=cur;
			cur = regs[cur].next;
			size--;
		}
		// cout<<i%players<<" : "<<regs<<endl;
		// print(regs, cur, i%players);
		// string line;
		// cin>>line;
	}
	return *max_element(scores.begin(), scores.end());
}

void tests(){
	assert(eval(10, 1618) == 8317);
	assert(eval(13, 7999)== 146373);
	assert(eval(17, 1104)== 2764);
	assert(eval(21, 6111)== 54718);
	assert(eval(30, 5807)== 37305);
}

int main(){
	tests();
	unsigned int players, marbles;
	fstream file("Day 9/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	ss>>players>>line>>line>>line>>line>>line>>marbles;
	cout<<"[P1] "<<eval(players, marbles)<<endl;
	cout<<"[P2] "<<eval(players, marbles*100)<<endl;
}