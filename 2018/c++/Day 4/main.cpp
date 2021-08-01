#include "../aoc.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

int main(){
	map<int, vector<int>> m;
	fstream file("Day 4/input");
	string line;
	vector<string> inps;
	while(getline(file, line)){
		inps.push_back(line);
	}
	sort(inps.begin(), inps.end());
	// for(auto& c: inps){
	// 	cout<<c<<endl;
	// }
	int id;
	int hour, min;
	char c;
	int startTime;
	for(auto& v: inps){
		// cout<<v<<endl;
		stringstream ss(v);
		ss>>line>>hour>>c>>min>>c>>line;
		if(line == "Guard"){
			ss>>c>>id;
			if(m.count(id)==0){
				m[id] = vector<int>(60);
			}
		}else if(line == "falls"){
			startTime = min;
		}else{
			// cout<<startTime<<" -> "<<min<<endl;
			for(int i = startTime;i<min;i++){
				m[id][i]++;
			}
		}
	}

	int maxMin;
	int maxTime = 0;
	int timeSlept=0;
	int tempMin;
	int maxId;
	int id2(0);
	int tempMin2;
	int p2Minute(0);
	for(auto& [k, v]: m){
		tempMin = 0;
		timeSlept = 0;
		tempMin2=0;
		for(int i = 0;i<60;i++){
			if(v[i]>v[tempMin]){
				tempMin = i;
			}
			if(v[i]>v[tempMin2]){
				tempMin2 = i;
			}
			timeSlept+=v[i];
		}
		if(timeSlept>maxTime){
			maxTime = timeSlept;
			maxMin = tempMin;
			maxId = k;
		}
		if(id2==0||v[tempMin2]> m[id2][p2Minute]){
			id2 = k;
			p2Minute = tempMin2;
		}
	}

	cout<<"[P1] "<<maxId*maxMin<<endl;
	cout<<"[P1] "<<id2*p2Minute<<endl;
}