#include "../intcode.h"
#include "../prints.h"
#include <map>

void printBoard(vector<vector<int>>& m, int score){
	map<int, string> mapping;
	mapping[0] = " ";
	mapping[1] = "█";
	mapping[2] = "▀";
	mapping[3] = "─";
	mapping[4] = "o";
	string out = "";
	for(auto& r: m){
		for(auto c: r){
			out+=mapping[c];
		}out+="\n";
	}

	cout<<out<<"Score: "<<score<<endl;
}

int main(){
	IntCode c(13);
	c.regs[0] = 2;
	for(int i = 1564;c.regs[i]!=1;i++){ //change paddle to take up entire length lmao
		c.regs[i] = 3;
	}
	for(int i =0 ;i<100;i++){
		c.inp = vector<ll>(15000, 0);
	}
	c.run();
	vector<vector<int>> m(24, vector<int>(42));
	int p1 = 0;
	int score = 0;
	for(int i = 0;i<c.out.size();i+=3){
		// cout<<c.out[i]<<", "<<c.out[i+1]<< "="<<c.out[i+2]<<endl;
		p1+=c.out[i+2] == 2;
		if(c.out[i] == -1 && c.out[i+1] == 0)
			score = c.out[i+2];
		else
			m[c.out[i+1]][c.out[i]] = c.out[i+2];
	}
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<score<<endl;
	// printBoard(m, score);

	// for(int i = 0;;i++){ //to find which regs to change
	// 	if(c.regs[i] == 3 && c.regs[i+1] == 3 && c.regs[i+2] == 3){
	// 		cout<<i<<endl;
	// 	}
	// }
}