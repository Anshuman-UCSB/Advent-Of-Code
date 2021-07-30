#include "../prints.h"
#include <vector>
#include <fstream>
#include <utility>
#include <sstream>

// #define ll int64_t
#define ll long long
#define func pair<ll, ll>

void funcBuild(func& eq, func inst, ll mod){
	eq.first*=inst.first;
	eq.first%=mod;
	eq.second*=inst.first;
	eq.second+=inst.second+mod;
	eq.second%=mod;
}

func recursiveBuild(func eq, ll k, ll mod){
	func g(1,0);

	while (k>0){
		if(k%2)
			funcBuild(g, eq, mod);
		k/=2;
		funcBuild(eq, eq, mod);
	}

	return g;
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

// ll modularInverse(func& eq, const ll size){

// }

ll solveInverse(func& eq, const ll size, ll spot){
	return 1;
}

void p2(){
	const ll SIZE = 119315717514047;
	const ll SHUFFLES = 101741582076661;
	func eq = makeFunction(SIZE);
	eq = recursiveBuild(eq, SHUFFLES, SIZE);
	cout<<eq<<endl;
	cout<<"[P2] "<<solveInverse(eq, SIZE, 2020)<<endl;
	// func test(3,2);
	// cout<<test<<endl;
	/*
	3x+2 mod 10
	3(3x+2)+2 mod 10
	9x + 8 mod 10
	9(3x+2) + 8 mod 10
	7x + 6 mod 10
	*/
	// test = recursiveBuild(test, 3, 10);
	// cout<<test<<endl;
}



int main(){
	const ll size = 10007;
	func eq = makeFunction(size);
	// cout<<eq<<endl;
	cout<<"[P1] "<<apply(eq, size, 2019)<<endl;
	p2();
}

//57481683403608 too low
//7035538574573 