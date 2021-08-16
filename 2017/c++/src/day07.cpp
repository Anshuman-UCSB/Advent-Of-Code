#include "AOC.h"

map<string, vector<string>> m;
map<string, int> weights;
map<string, int> totalWeights;

int getWeight(const string& n){
	if(m.count(n) == 0){
		totalWeights[n] = weights[n];
		return totalWeights[n];
	}else{
		if(totalWeights.count(n))
			return totalWeights[n];
		else{
			totalWeights[n] = weights[n];
			for(auto& c: m[n]){
				totalWeights[n]+=getWeight(c);
			}
			return totalWeights[n];
		}
	}
}

bool isBalanced(const string& s){
	if(m.count(s) == 0){
		return true;
	}
	int comp = getWeight(m[s][0]);
	for(int i = 1;i<m[s].size();i++){
		// cout<<comp<<" ? "<<getWeight(m[s][i])<<endl;
		if(comp != getWeight(m[s][i])) return false;
	}
	return true;
}

int solveP2(const string& head, int target){
	map<int, int> counter;
	string problem;
	for(auto& c: m[head]){
		counter[getWeight(c)]++;
		if(!isBalanced(c)) problem = c;
	}
	if(counter.size() == 1){
		return target;
	}
	if(problem.empty()){
		int target;
		for(auto& [w, cnt]: counter){
			if(cnt>1){
				target = w;
			}
		}
		for(auto& c: m[head]){
			if(getWeight(c) !=target){
				return (target-getWeight(c))+weights[c];
			}
		}
	}
	for(auto& [w, cnt]: counter){
		if(cnt>1){
			target = w;
		}
	}
	return solveP2(problem, target);
}

chrono::time_point<std::chrono::steady_clock> day07(input_t& inp){
	string parent,s;
	char t;
	int w;
	set<string> notParent;
	for(auto& l : inp){
		stringstream ss(l);
		ss>>parent>>t>>w>>t>>s;
		auto& v = m[parent];
		weights[parent] = w;
		while(ss>>s){
			if(s.back() == ',') s.pop_back();
			v.push_back(s);
			notParent.insert(s);
		}
	}
	string p1;
	for(auto& [k, ignore] : m){
		if(notParent.find(k) == notParent.end()){
			p1 = k;
			break;
		}
	}

	int p2 = solveP2(p1, -1);

	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}