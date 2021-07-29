#include "../prints.h"
#include <vector>
#include <fstream>
#include <utility>
#include <sstream>

#define ll long long
#define func pair<ll, ll>

void funcBuild(func& eq, func inst, ll size){
	eq.first*=inst.first;
	eq.first%=size;
	eq.second*=inst.first;
	eq.second+=inst.second;
	eq.second%=size;
}

ll apply(func& eq, ll size, ll inp){
	inp*=eq.first;
	inp%=size;
	if(inp<0)inp+=size;
	inp+=eq.second;
	inp%=size;
	if(inp<0)inp+=size;
	return inp;
}

func makeFunction(ll size){
	func eq(1,0); //ax+b
	fstream file("Day 22/input");
	string line;
	func tfunc;
	while(getline(file, line)){
		// cout<<eq<<endl;
		stringstream ss(line);
		string temp;
		int n;
		ss>>temp;
		if(temp == "cut"){ //cut
			tfunc=make_pair(1,0);
			ss>>tfunc.second;
			tfunc.second*=-1;
		}else{
			ss>>temp;
			if(temp == "into"){ //reverse
				tfunc=make_pair(-1,-1);
			}else{				//deal
				tfunc=make_pair(0, 0);
				ss>>temp>>tfunc.first;
				// cout<<"."<<tfunc<<endl;
			}
		}
		funcBuild(eq, tfunc, size);
	}

	return eq;
}

int main(){
	const ll size = 10007;
	func eq = makeFunction(size);
	// cout<<eq<<endl;
	cout<<"[P1] "<<apply(eq, size, 2019)<<endl;
}