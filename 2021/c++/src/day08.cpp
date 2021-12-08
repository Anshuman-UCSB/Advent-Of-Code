	#include "AOC.h"

	char getOutlier(const string& a, const string& b){
		vector<int> m(26);
		for(int c: a)
			m[c-'a']++;
		for(int c: b)
			m[c-'a']--;
		for(char c = 'a';c<='z';c++)
			if(m[c-'a']) return c;
		return -1;
	}

	map<char, char> getMap(vector<string>& lhs){
		map<char, char> out;
		string s2, s3, s4;
		vector<int> uses(7);
		for(auto& w: lhs){
			switch(w.size()){
				case 2: s2 = w; break;
				case 3: s3 = w; break;
				case 4: s4 = w; break;
			}
			for(auto c: w)
				uses[c-'a']++;
		}
		out['a']=getOutlier(s3, s2);
		for(int i = 0;i<7;i++){
			switch(uses[i]){
				case 6:
					out['b'] = i+'a';	break;
				case 8:
					if(i+'a'!=out['a'])
						out['c'] = i+'a';
					break;
				case 4:
					out['e'] = i+'a'; 	break;
				case 9:
					out['f'] = i+'a';	break;
			}
		}
		out['d'] = getOutlier(s4, string{out['b'],out['c'],out['f']});
		for(int i = 0;i<7;i++)
			if(uses[i] == 7 && i+'a'!=out['d']){
				out['g'] = i+'a';
				break;
			}
		map<char, char> rev;
		for(auto& [k, v]: out)
			rev[v] = k;
		
		return rev;
	}

	ull checksum(const string& s, map<char, char>& m){
		ull out = 1;
		for(char c: s)
			out*=m[c];
		return out;
	}

	int translateChecksum(const ull& cs){
		vector<ull> nums = {998600489964, 10098, 9990000900, 10088911800, 98960400, 9987003600, 1008687363600, 979506, 99860048996400, 988713356400};
		for(int i = 0;i<10;i++){
			if(nums[i] == cs) return i;
		}
		return -1;
	}

	chrono::time_point<std::chrono::steady_clock> day08(input_t& inp){
		int p1(0), p2(0);
		for(auto& l: inp){
			vector<string> lhs, rhs;
			string s;
			stringstream ss(l);
			for(; ss>>s;lhs.emplace_back(s))
				if(s == "|") break;
			for(; ss>>s;rhs.emplace_back(s)){}
			auto mapping = getMap(lhs);
			int n = 0;
			for(auto& w: rhs){
				n = n*10+translateChecksum(checksum(w, mapping));
				switch(w.size()){
					case 2:	case 3:	case 4:	case 7:
						p1++;
				}
			}
			p2+=n;
		}
		
		auto done = chrono::steady_clock::now();
		cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
		return done;
	}