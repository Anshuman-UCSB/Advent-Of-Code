#include "AOC.h"

void print(const vector<vector<bool>>& m){
	for(int y = 0;y<m.size();y++){
		for(int x = 0;x<m.size();x++){
			cout<<(m[y][x]?"#":".");
		}cout<<endl;
	}
}

/**
 * reg    y     x     r     l    180    r'    l'
 * 123   789   321   741   369   987   963   147
 * 456   456   654   852   258   654   852   258
 * 789   123   987   963   147   321   741   369
 * 
 * reg:	123/456/789
 * y:	789/456/123
 * x:	321/643/987
 * r:	741/852/963
 * l:	369/258/147
 * 180:	987/654/321
 * r':	963/852/741
 * l':	147/258/369
 * 
 * use this to generate the code lol:
		inp = """123/456/789
		789/456/123
		321/643/987
		741/852/963
		369/258/147
		987/654/321
		963/852/741
		147/258/369
		"""
		for l in inp.splitlines():
			print("ss.clear();\nss",end="")
			for c in l:
				if c == '/':
					print("<<\""+c+"\"", end = "")
				else:
					print("<<inp[{}]".format(int(c)-1), end="")
			print(";")
 **/

void addPermutations(const string& inp, const string& res, map<string, vector<vector<bool>>>& rules){
	vector<vector<bool>> match;
	match.emplace_back();
	for(auto& c: res){
		switch(c){
			case '#': match.back().push_back(1);	break;
			case '.': match.back().push_back(0);	break;
			case '/': match.emplace_back();			break;
		}
	}
	if(inp.size() == 11){
		stringstream ss;
		ss<<(inp[0]=='#')<<(inp[1]=='#')<<(inp[2]=='#')<<"/"<<(inp[4]=='#')<<(inp[5]=='#')<<(inp[6]=='#')<<"/"<<(inp[8]=='#')<<(inp[9]=='#')<<(inp[10]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[8]=='#')<<(inp[9]=='#')<<(inp[10]=='#')<<"/"<<(inp[4]=='#')<<(inp[5]=='#')<<(inp[6]=='#')<<"/"<<(inp[0]=='#')<<(inp[1]=='#')<<(inp[2]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[2]=='#')<<(inp[1]=='#')<<(inp[0]=='#')<<"/"<<(inp[6]=='#')<<(inp[4]=='#')<<(inp[2]=='#')<<"/"<<(inp[10]=='#')<<(inp[9]=='#')<<(inp[8]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[8]=='#')<<(inp[4]=='#')<<(inp[0]=='#')<<"/"<<(inp[9]=='#')<<(inp[5]=='#')<<(inp[1]=='#')<<"/"<<(inp[10]=='#')<<(inp[6]=='#')<<(inp[2]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[2]=='#')<<(inp[6]=='#')<<(inp[10]=='#')<<"/"<<(inp[1]=='#')<<(inp[5]=='#')<<(inp[9]=='#')<<"/"<<(inp[0]=='#')<<(inp[4]=='#')<<(inp[8]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[10]=='#')<<(inp[9]=='#')<<(inp[8]=='#')<<"/"<<(inp[6]=='#')<<(inp[5]=='#')<<(inp[4]=='#')<<"/"<<(inp[2]=='#')<<(inp[1]=='#')<<(inp[0]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[10]=='#')<<(inp[6]=='#')<<(inp[2]=='#')<<"/"<<(inp[9]=='#')<<(inp[5]=='#')<<(inp[1]=='#')<<"/"<<(inp[8]=='#')<<(inp[4]=='#')<<(inp[0]=='#');
		rules[ss.str()] = match;
		ss.str(string());
		ss<<(inp[0]=='#')<<(inp[4]=='#')<<(inp[8]=='#')<<"/"<<(inp[1]=='#')<<(inp[5]=='#')<<(inp[9]=='#')<<"/"<<(inp[2]=='#')<<(inp[6]=='#')<<(inp[10]=='#');
		rules[ss.str()] = match;
	}
	else{
		/*
			used regex 	ss<<inp\[(\d)\]<<inp\[(\d)\]<<"/"<<inp\[(\d)\]<<inp\[(\d)\];
			to			ss<<inp[$1]<<inp[$2]<<"/"<<inp[$3]<<inp[$4];
						ss<<inp[$3]<<inp[$1]<<"/"<<inp[$4]<<inp[$2];
		*/
		stringstream ss;
		ss<<(inp[0]=='#')<<(inp[1]=='#')<<"/"<<(inp[3]=='#')<<(inp[4]=='#');
		rules[ss.str()] = match;
		
		ss.str(string());
		ss<<(inp[3]=='#')<<(inp[0]=='#')<<"/"<<(inp[4]=='#')<<(inp[1]=='#');
		rules[ss.str()] = match;
		
		ss.str(string());
		ss<<(inp[4]=='#')<<(inp[3]=='#')<<"/"<<(inp[1]=='#')<<(inp[0]=='#');
		rules[ss.str()] = match;

		ss.str(string());
		ss<<(inp[1]=='#')<<(inp[4]=='#')<<"/"<<(inp[0]=='#')<<(inp[3]=='#');
		rules[ss.str()] = match;
	}
}

vector<vector<bool>> iter(const vector<vector<bool>>& m, map<string, vector<vector<bool>>>& rules){
	int s = m.size();
	if(s%2==0){
		int ns = (s/2)*3;
		vector<vector<bool>> out(ns, vector<bool>(ns));

		for(int y = 0;y<s/2;y++){
			for(int x = 0;x<s/2;x++){
				stringstream ss;
				ss<<m[y*2][x*2]<<m[y*2][x*2+1]<<"/"<<m[y*2+1][x*2]<<m[y*2+1][x*2+1];
				auto& match = rules[ss.str()];
				for(int i = 0; i<3;i++){
					for(int j = 0;j<3;j++){
						out[y*3+i][x*3+j] = match[i][j];
					}
				}
			}
		}

		return out;
	}else{
		int ns = (s/3)*4;
		vector<vector<bool>> out(ns, vector<bool>(ns));

		for(int y = 0;y<s/3;y++){
			for(int x = 0;x<s/3;x++){
				stringstream ss;
				ss<<m[y*3][x*3]<<m[y*3][x*3+1]<<m[y*3][x*3+2]<<"/"
				  <<m[y*3+1][x*3]<<m[y*3+1][x*3+1]<<m[y*3+1][x*3+2]<<"/"
				  <<m[y*3+2][x*3]<<m[y*3+2][x*3+1]<<m[y*3+2][x*3+2];
				// cout<<"segfault here"<<endl;
				// cout<<ss.str()<<endl;
				const auto& match = rules[ss.str()];
				// print(match);
				// cout<<"segfault not here"<<endl;
				for(int i = 0; i<4;i++){
					for(int j = 0;j<4;j++){
						out[y*4+i][x*4+j] = match[i][j];
					}
				}
			}
		}

		return out;
	}
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp){
	vector<vector<bool>> m = {{0,1,0},{0,0,1},{1,1,1}};
	map<string, vector<vector<bool>>> rules;
	for(auto& l: inp){
		stringstream ss(l);
		string t;
		string p2;
		ss>>t>>p2>>p2;
		addPermutations(t, p2, rules);
	}
	// cout<<rules<<endl;
	for(int i = 0;i<5;i++){
		m = iter(m, rules);
	}
	int p1 = 0;
	for(auto& r: m){
		for(auto c: r){
			p1+=c;
		}
	}
	for(int i = 5;i<18;i++){
		m = iter(m, rules);
	}
	int p2 = 0;
	for(auto& r: m){
		for(auto c: r){
			p2+=c;
		}
	}
	// print(m);
	// cout<<rules<<endl;
	// for(auto& [p, rep]: rules){
	// 	cout<<p<<endl;
	// 	for(auto& c: p){
	// 		if(c == '/') cout<<endl;
	// 		else cout<<c;
	// 	}
	// 	cout<<endl<<endl;
	// }
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}