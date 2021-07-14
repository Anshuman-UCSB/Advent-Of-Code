#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>


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

stack<string> getParentTree(map<string, string>& p, string node){
	stack<string> s;
	s.push(node);
	string temp = node;
	while(temp != "COM"){
		temp = p[temp];
		s.push(temp);
		// cout<<temp<<endl;
	}
	return s;
}

int main(){
	vector<string> inp;
	fstream file("Day 6/input");
	string line;
	while(getline(file, line)){
		inp.push_back(line);
	}

	map<string, vector<string>> orbits;
	map<string, string> parents;
	map<string, int> depth;
	for(auto l: inp){
		string a, b;
		a = l.substr(0,l.find(")"));
		b = l.substr(l.find(")")+1);
		parents[b] = a;
		orbits[a].emplace_back(b);
	}

	cout<<"P1: "<<p1(orbits, depth, "COM")<<endl;

	stack<string> san = getParentTree(parents, "SAN");
	stack<string> you = getParentTree(parents, "YOU");
	while(san.top() == you.top()){
		you.pop();
		san.pop();
	}
	cout<<"P2: "<<you.size() + san.size() - 2<<endl;
}