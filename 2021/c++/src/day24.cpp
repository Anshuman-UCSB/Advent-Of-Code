#include "AOC.h"
#define block tuple<int, int, int>

inline ull buildNum(vector<int>& d){
	ull out = 0;
	for(auto& v: d)
		out=out*10+v;
	return out;
}

ull solve(bool p1, map<int, pii>& criteria){
	vector<int> order;
	for(int i = 1;i<10;i++)
		order.push_back(p1?10-i:i);
	stack<pair<vector<int>,int>> s;
	s.push(make_pair(vector<int>(14), 0));
	while(!s.empty()){
		auto [digits, pos] = s.top();
		s.pop();
		while(pos<14&&digits[pos])
			pos++;
		if(pos==14)
			return buildNum(digits);
		for(auto& v: order){
			auto t = digits;
			t[pos] = v;
			if(t[pos]<=0 || t[pos] > 9)	continue;
			auto it = criteria.find(pos);
			if(it != criteria.end()){
				int val = v+it->second.second;
				t[it->second.first] = val;
				if(val<=0 || val > 9)	continue;
			}
			s.push(make_pair(t, pos+1));
		}
	}
	return 0;
}

chrono::time_point<std::chrono::steady_clock> day24(input_t& inp){
	ull p1(0), p2(0);
	int a, b, c;
	string t;
	vector<block> nums;
	for(int i = 0;i<18*14;i+=18){
		stringstream ss;
		ss = stringstream(inp[i+4]);
		ss>>t>>t>>a;
		ss = stringstream(inp[i+5]);
		ss>>t>>t>>b;
		ss = stringstream(inp[i+15]);
		ss>>t>>t>>c;
		nums.emplace_back(a,b,c);
	}
	int level = 0;
	vector<vector<int>> layers(7);
	for(int i = 0;i<14;i++){
		auto [a,b,c] = nums[i];
		layers[a==26?level--:++level].push_back(i);
	}
	map<int, pii> criteria;
	for(int i = 0;i<layers.size();i++){
		for(int j = 0;j<layers[i].size();j+=2){
			criteria[layers[i][j]] = pii(layers[i][j+1],
				get<2>(nums[layers[i][j]])+get<1>(nums[layers[i][j+1]]));
		}
	}
	p1 = solve(true,  criteria);
	p2 = solve(false, criteria);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}