#include "../intcode.h"

int main(){
	vector<IntCode> network(50,IntCode(23));
	for(int i =0 ;i<50;i++){
		network[i].push(i);
	}
	while(1){
		for(auto& c: network){
			if(c.regs[c.ind]%100 == 3 && c.inp.empty()){
				c.push(-1);
				// cout<<"PUSHED: "<<c.inp<<endl;
			}
			// c.print();
			// cout<<c.regs[c.ind]<<endl;
			c.step();
			if(c.out.size() == 3){
				if(c.out[0]==255){
					cout<<"[P1] "<<c.out[2]<<endl;
					return 0;
				}
				network[c.out[0]].push(c.out[1]);
				network[c.out[0]].push(c.out[2]);
				c.out.clear();
			}
		}
	}
}