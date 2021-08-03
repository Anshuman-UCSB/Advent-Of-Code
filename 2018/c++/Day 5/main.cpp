#include "../aoc.h"
#include <stack>

static inline bool react(const char& a, const char& b){
	return (a^' ')==b;
}

int p2(const string& inp){
	size_t minSize = inp.size();
	for(char ch = 'a';ch<='z';ch++){
		stack<char> temp;
		for(const auto& c: inp){
			if(tolower(c) == ch) continue;
			if(!temp.empty()){
				if(react(c, temp.top()))
					temp.pop();
				else
					temp.push(c);
			}else
				temp.push(c);
		}
		if(temp.size() == inp.size()) return minSize;
		minSize = min(temp.size(), minSize);
	}

	return minSize;
}

string p1(const string& inp){
	stack<char> s;
	for(const auto& c: inp){
		if(!s.empty()){
			if(react(c, s.top())){
				s.pop();
			}
			else{
				s.push(c);
			}
		}else
			s.push(c);
	}
	string out(s.size(), ' ');
	for(int i = out.size()-1;!s.empty();i--){
		out[i] = s.top();
		s.pop();
	}
	return out;
}

int main(){
	fstream file("Day 5/input");
	string line;
	getline(file, line);
	string p1String = p1(line);
	cout<<"[P1] "<<p1String.size()<<endl;
	cout<<"[P2] "<<p2(p1String)<<endl;
}