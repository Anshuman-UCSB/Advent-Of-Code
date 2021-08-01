#include "../aoc.h"

vector<vector<int>> counts;
vector<string> inp;

pair<bool, string> oneDifferent(const string& a, const string& b){
	bool oneDiff = false;
	string out = a;
	for(int i =0 ;i<a.size();i++){
		if(a[i]!=b[i]){
			if(oneDiff) return make_pair(false, out);
			oneDiff = true;
			out.erase(out.begin()+i);
		}
	}
	return make_pair(oneDiff, out);
}

int main(){
	Timer t;
	fstream file("Day 2/input");
	string line;
	int two(0), three(0);
	bool flag2, flag3;
	while(getline(file, line)){
		counts.emplace_back(26);
		flag2 = false;
		flag3 = false;
		// for(int i = 0;i<26;i++) cout<<counts[i]<<" ";cout<<endl;
		for(auto c: line) counts.back()[c-'a']++;
		for(auto v:counts.back()){
			if(v == 2) flag2=true;
			if(v == 3) flag3=true;
		}
		two+=flag2;
		three+=flag3;
		inp.push_back(line);
	}
	cout<<"[P1] "<<two*three<<endl;
	
	for(int i = 0;i<inp.size()-1;i++){
		for(int j = i+1;j<inp.size();j++){
			if(pair<bool, string> t =oneDifferent(inp[i], inp[j]);t.first){
				cout<<"[P2] "<<t.second<<endl;
				goto done;
			}
		}
	}
	done:;
	t.end();
}