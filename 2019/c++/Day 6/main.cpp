#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	vector<string> inp;
	fstream file("Day 6/input");
	string line;
	while(getline(file, line)){
		inp.push_back(line);
	}

	for(auto l: inp){
		cout<<l<<endl;
	}
}