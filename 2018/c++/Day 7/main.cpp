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
bool canMake(set<char>& made, vector<char>& need){
	for(auto& c: need){
		if(made.count(c)==0){
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

int p2(){
	int time = 0;
	vector<pair<char, int>> workers(5, make_pair('_',0));
	set<char> made;
	set<char> q, taken;
	for(auto& [k, v] : m){
		if (v.empty()){
			q.insert(k);
			break;
		}
	}
	for(time = 0;made.size()<m.size(); time++){
		for(auto& [k, v]: m){
			if(canMake(made, v) && taken.count(k)==0 && made.count(k) == 0){
				for(auto& w: workers){
					if(w.first == '_'){
						w.first = k;
						taken.insert(k);
						w.second = (k&31)+60;
						break;
					}
				}
			}
		}
		for(auto& w: workers){
			if(w.first != '_'){
				if(--w.second==0){
					made.insert(w.first);
					taken.erase(w.first);
					w.first = '_';
				}
			}
		}
	}
	return time;
}

int main(){
	fstream file("Day 7/input");
	string line;

	while(getline(file, line)){
		m[line[5]];
		m[line[36]].push_back(line[5]);
	}
	cout<<"[P1] "<<p1()<<endl;
	cout<<"[P2] "<<p2()<<endl;
}