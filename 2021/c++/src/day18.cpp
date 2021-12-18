#include "AOC.h"
#include <cassert>

list<pii> build(const string& l){
	list<pii> o;
	int level = 0;
	for(const auto& c: l){
		if(c == '[') level++;
		else if(c==']') level--;
		else if(c!=',') o.emplace_back(c-'0', level);
	}
	return o;
}

bool explode(list<pii>& p){
	for(auto it = p.begin(); it!=prev(p.end());it++){
		auto n = next(it);
		if(it->second > 4 && it->second == n->second){
			if(it != p.begin())
				prev(it)->first+=it->first;
			if(it != prev(p.end()))
				next(next(it))->first+=next(it)->first;
			it = p.erase(it);
			it->first=0;
			it->second--;
			return true;
		}
	}
	return false;
}

bool split(list<pii>& p){
	int t;
	for(auto it = p.begin(); it!=p.end();it++){
		if(it->first >= 10){
			t = it->first>>1;
			it->second++;
			p.insert(it, pii(t, it->second));
			it->first=t+(it->first)%2;
			return true;
		}
	}
	return false;
}
void inline reduce(list<pii>& p){
	while (explode(p) || split(p));
}

list<pii> add(list<pii> a, list<pii> b){
	a.splice(a.end(), b);
	for(auto& [k, v]: a)
		v++;
	reduce(a);
	return a;
}

int magnitude(list<pii> l){
	while(l.begin() != prev(end(l))){
		for(auto it = begin(l); it!=prev(end(l));it++){
			auto n = next(it);
			if(it->second == n->second){
				it->first = 3*it->first + 2*n->first;
				it->second--;
				l.erase(n);
				break;
			}
		}
	}
	return l.begin()->first;
}

chrono::time_point<std::chrono::steady_clock> day18(input_t& inp){
	vector<list<pii>> nums;
	for(auto& l: inp)
		nums.push_back(build(l));
	auto s = nums[0];
	for(int i = 1;i<nums.size();i++){
		s = add(s, nums[i]);
	}
	int p1 = magnitude(s), p2(0);
	for(int i = 0;i<inp.size()-1;i++){
		for(int j = i+1;j<inp.size();j++){
			p2 = max(p2, magnitude(add(nums[i], nums[j])));
			p2 = max(p2, magnitude(add(nums[j], nums[i])));
		}
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}