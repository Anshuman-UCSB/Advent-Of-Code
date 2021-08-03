#include "../aoc.h"
#include <sstream>

int players, marbles;

void print(vector<int>& regs, int pos, int player){
	cout<<"["<<player<<"]	";
	bool start = true;
	for(int i = 0;i!=0 || start;i = regs[i]){
		start = false;
		cout<<(i==pos?"(":" ");
		cout<<i;
		cout<<(i==pos?")":" ");
	}cout<<endl;
}

int p1(int players, int marbles){
	vector<int> scores(players);
	vector<int> regs(marbles, -1);
	regs[0] = 0; //0 points to 0
	int cur = 0;
	int size = 1;
	int next;
	for(int i = 1;i<=marbles;i++){
		if(i%23){
			cur=regs[cur]; //cur++
			next = regs[cur];
			regs[cur] = i;
			regs[i] = next;
			cur=regs[cur];
			size++;
		}else{
			scores[i%players]+=i;
			for(int _ = 0;_<size-8;_++){
				cur = regs[cur];
			}
			scores[i%players]+=regs[cur];
			regs[cur] = regs[regs[cur]];
			cur = regs[cur];
			size--;
		}
		// print(regs, cur, i%players);
	}

	return *max_element(scores.begin(), scores.end());
}

int main(){
	fstream file("Day 9/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	ss>>players>>line>>line>>line>>line>>line>>marbles;
	cout<<"[P1] "<<p1(players, marbles)<<endl;
	cout<<"[P2] "<<p1(players, 100*marbles)<<endl;
}