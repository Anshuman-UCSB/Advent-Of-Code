#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day06(input_t& inp){
	vector<int> regs;
	set<vector<int>> cache;
	stringstream ss(inp[0]);
	int t;
	while(ss>>t)
		regs.push_back(t);
	
	int p1 = 0;
	while(cache.insert(regs).second){
		p1++;
		int maxInd = 0;
		for(int i = 1;i<regs.size();i++)
			if(regs[i]>regs[maxInd])
				maxInd = i;
		
		int redist = regs[maxInd];
		regs[maxInd] = 0;
		for(int i = (maxInd+1)%regs.size();redist--;i=(i+1)%regs.size()){
			regs[i]++;
		}
	}
	auto p1State = regs;
	int p2 = 0;
	while(regs!=p1State || p2==0){
		p2++;
		int maxInd = 0;
		for(int i = 1;i<regs.size();i++)
			if(regs[i]>regs[maxInd])
				maxInd = i;
		
		int redist = regs[maxInd];
		regs[maxInd] = 0;
		for(int i = (maxInd+1)%regs.size();redist--;i=(i+1)%regs.size()){
			regs[i]++;
		}
	}
	

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P1] "<<p2<<endl;
	return done;
}