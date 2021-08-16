#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day01(input_t& inp){
	vector<short> nums;
	for(auto& c: inp[0])
		nums.push_back((short)(c-'0'));
	int p1(0), p2(0);
	for(int i = 0;i<nums.size();i++){
		if(nums[i] == nums[(i+1)%nums.size()])
			p1+=nums[i];
		if(nums[i] == nums[(i+nums.size()/2)%nums.size()])
			p2+=nums[i];
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}