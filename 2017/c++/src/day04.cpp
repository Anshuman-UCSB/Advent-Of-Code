#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day04(input_t& inp){
	int p1=0, p2=0;
	bool p1flag, p2flag;
	for(auto& r: inp){
		p1flag = p2flag = true;
		unordered_set<string> counter;
		unordered_set<string> counter2;
		stringstream ss(r);
		string t;
		while(ss>>t && (p1flag || p2flag)){
			if(counter.insert(t).second == false) p1flag = false;
			sort(t.begin(), t.end());
			if(counter2.insert(t).second == false) p2flag = false;
		}
		if(p1flag) p1++;
		if(p2flag) p2++;
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P1] "<<p2<<endl;
	return done;
}