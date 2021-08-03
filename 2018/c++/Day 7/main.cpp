#include "../aoc.h"
#include "../prints.h"

map<char, vector<char>> m;

bool canMake(string& made, vector<char>& need){
	for(auto& c: need){
		if(made.find(c) == string::npos){
			return false;
		}
	}
	return true;
}

string p1(){
	string out;
	for(auto& [k, v] : m){
		if (v.empty()){
			out+=k;
			break;
		}
	}
	bool done = false;
	char next;
	while(!done){
		done = true;
		next = 'Z'+1;
		for(auto& [k, v] : m){
			if(out.find(k) != string::npos) continue;
			if(canMake(out, v)){
				next = min(next, k);
				done = false;
			}
		}
		if(next == 'Z'+1){
			break;
		}
		out+=next;
	}

	return out;
}

int main(){
	fstream file("Day 7/input");
	string line;

	while(getline(file, line)){
		m[line[5]];
		m[line[36]].push_back(line[5]);
	}
	cout<<p1()<<endl;
}