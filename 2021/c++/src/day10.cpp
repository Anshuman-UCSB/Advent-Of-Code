#include "AOC.h"

ull p2s(stack<char>& s){
	ull out = 0;
	while(!s.empty()){
		out *= 5;
		char t = s.top();
		s.pop();
		switch(t){
			case '>':out++;
			case '}':out++;
			case ']':out++;
			case ')':out++;
		}
	}
	return out;
}

chrono::time_point<std::chrono::steady_clock> day10(input_t& inp){
	ull p1(0);

	vector<ull> incomplete;
	map<char, char> closers = {{'(',')'}, {'[',']'}, {'{','}'}, {'<','>'}};
	map<char, int> illegal = {{')',3}, {']',57}, {'}',1197}, {'>',25137}};
	for(auto& l: inp){
		bool invalid = false;
		stack<char> s;
		for(auto c: l){
			if(c == '(' || c == '[' || c == '{' || c == '<')
				s.push(closers[c]);
			else{
				if(c != s.top()){
					invalid = true;
					p1+=illegal[c];
					break;
				}
				s.pop();
			}
		}
		if(!invalid)
			incomplete.push_back(p2s(s));
	}
	sort(begin(incomplete), end(incomplete));
	ull p2 = incomplete[incomplete.size()/2];
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}