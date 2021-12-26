#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day01(input_t& inp){
	int p1(0), p2(0);

	int old = 999999, n;
	vector<int> nums;
	for(auto& v: inp){
		nums.emplace_back(stoi(v));
		p1+=(nums.back()>old);
		old = nums.back();
	}

	old = nums[0]+nums[1]+nums[2];
	for(int i =3;i<nums.size();i++){
		n=old+nums[i]-nums[i-3];
		p2+=n>old;
		old+=nums[i-3];
	}
	
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}