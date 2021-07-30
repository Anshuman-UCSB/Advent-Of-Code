#include "../intcode.h"
#include <set>
#include <algorithm>
#define NAT pair<int, int>

int main(){
	vector<IntCode> network(50,IntCode(23));
	for(int i =0 ;i<50;i++){
		network[i].push(i);
	}
	NAT nat;
	bool p1 = false;
	vector<bool> idle(50, 0);
	vector<bool> flag(50, 0);
	set<NAT> seen;
	while(1){
		for(int i =0 ;i<50;i++){
			IntCode& c = network[i];
			if(c.regs[c.ind]%100 == 3){
				if(c.inp.empty()){
					c.push(-1);
					if(flag[i] == 1){ //gone a whole loop without outputting
						idle[i] = true;
					}else{
						flag[i] = 1;
					}
				}else
					idle[i] = false;
			}
			// c.print();
			// cout<<c.regs[c.ind]<<endl;
			c.step();
			if(c.out.size() == 3){
				idle[i] = false;
				flag[i] = 0;
				if(c.out[0]==255){
					// cout<<"HIT?"<<endl;
					if(p1++==false)
						cout<<"[P1] "<<c.out[2]<<endl;
					nat.first = c.out[1];
					nat.second = c.out[2];
					// cout<<nat<<endl;
				}else{
					network[c.out[0]].push(c.out[1]);
					network[c.out[0]].push(c.out[2]);
				}
				c.out.clear();
			}
		}
		if(all_of(idle.begin(), idle.end(), [](bool v){return v;})){
			// cout<<"Seen: "<<seen<<endl;
			// cout<<"Emitting "<<nat<<endl;
			if(seen.insert(nat).second == false){
				cout<<"[P2] "<<nat.second<<endl;
				return 1;
			}
			network[0].push(nat.first);
			network[0].push(nat.second);
			idle = vector<bool>(50,0);
			flag = vector<bool>(50,0);
		}
	}
}