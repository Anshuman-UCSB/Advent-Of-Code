#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day03(input_t& inp){
	unsigned long p1, p2;
	const int width = 12;

	vector<bitset<width>> nums;
	for(auto& v: inp)
		nums.emplace_back(v);
	int c;
	bool res;
	bitset<width> eps, gam;
	for(int i = 0;i<width;i++){
		c = 0;
		for(auto& b: nums)
			c+=b[i];
		res = c*2>=nums.size();
		gam[i]=res;
		eps[i]=!res;
	}
	p1 = gam.to_ulong()*eps.to_ulong();
	list<bitset<width>> mx, mn;
	for(auto& b: nums){
		mx.push_back(b);
		mn.push_back(b);
	}
	eps = gam = bitset<width>();
	int i = width-1;
	while(mx.size()>1){
		c=0;
		for(auto& b: mx)
			c+=b[i];
		res = c*2>=mx.size();
		mx.remove_if([&](const bitset<width>& b){return b[i]!=res;});
		i--;
	}
	i = width-1;
	while(mn.size()>1){
		c=0;
		for(auto& b: mn)
			c+=b[i];
		res = c*2>=mn.size();
		mn.remove_if([&](const bitset<width>& b){return b[i]==res;});
		i--;
	}
	p2= mx.front().to_ulong()*mn.front().to_ulong();
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}