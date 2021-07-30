#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "../prints.h"
using namespace std;

int main(){
	fstream file("Day 2/input");
	string line;
	vector<vector<int>> dat;
	while(getline(file, line)){
		dat.emplace_back();
		stringstream ss(line);
		int temp;
		while(ss>>temp){
			dat.back().push_back(temp);
		}
	}

	int mn, mx;
	int p1 = 0;
	int p2 = 0;
	for(auto& v: dat){
		mn = 9999999;
		mx = 0;
		for(auto num: v){
			mn = min(mn, num);
			mx = max(mx, num);
		}
		for(auto n1: v){
			for(auto n2: v){
				if(n1==n2)
					continue;
				if(n1%n2 == 0){
					p2+=n1/n2;
					break;
				}
			}
		}
		p1+=mx-mn;
	}

	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
}