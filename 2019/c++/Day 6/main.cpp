#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int p1(map<string, vector<string>>& orbits,map<string, int>& depth, string node){
	if(node == "COM"){
		depth["COM"] = 0;
	}else{
		
	}
	int out = depth[node];
	for(auto& c: orbits[node]){
		depth[c] = depth[node]+1;
		out+=p1(orbits, depth, c);
	}
	return out;
	
}

int main(){
	vector<string> inp;
	fstream file("Day 6/input");
	string line;
	while(getline(file, line)){
		inp.push_back(line);
	}

	map<string, vector<string>> orbits;
	map<string, int> depth;
	for(auto l: inp){
		string a, b;
		a = l.substr(0,l.find(")"));
		b = l.substr(l.find(")")+1);
		orbits[a].emplace_back(b);
	}
	
	
	// for(auto& v: orbits){
	// 	cout<<v.first<<": [ ";
	// 	for(auto &c: v.second){
	// 		cout<<c<<" ";
	// 	}cout<<"]"<<endl;
	// }

	cout<<"P1: "<<p1(orbits, depth, "COM")<<endl;

}