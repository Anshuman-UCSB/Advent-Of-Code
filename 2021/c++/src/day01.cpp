#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day01(input_t& inp){
	int p1(0), p2(0);

	vector<int> nums;
	for(auto& v: inp)
		nums.emplace_back(stoi(v));

	for(int i =1;i<inp.size();i++){
		if(nums[i]>nums[i-1])
			p1++;
	}
	for(int i =3;i<inp.size();i++){
		if(nums[i]+nums[i-1]+nums[i-2]>nums[i-3]+nums[i-1]+nums[i-2])
			p2++;
	}
	
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}