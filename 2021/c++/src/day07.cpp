#include "AOC.h"
#include <algorithm>
inline long p2h(long n){
	return (n*(n+1))/2;
}
chrono::time_point<std::chrono::steady_clock> day07(input_t& inp){
	unsigned long p1(0), p2(0);
	vector<int> nums;
	long avg = 0, med;
	int t;
	char tr;
	for(stringstream ss(inp[0]); ss>>t;nums.push_back(t))
		ss>>tr;
	sort(nums.begin(), nums.end());
	for(auto& v: nums) avg+=v;
	avg/=nums.size();
	med = nums[nums.size()>>1];
	if(avg<med) avg++;
	for(auto& n: nums){
		p1+=abs(n-med);
		p2+=p2h(abs(n-avg));
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}