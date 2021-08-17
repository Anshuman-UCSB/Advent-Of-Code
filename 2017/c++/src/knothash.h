#pragma once
#include <vector>
#include <algorithm>
#include <iomanip>

void iter(vector<int>& n, int& pos, const int& length, int& skip){
	for(int i = 0;i<length/2;i++){
		swap(n[(pos+i)%256], n[(pos+length-i-1)%256]);
	}
	pos =(pos+length+skip++)%256;
}

string knothash(const string& inp){
	vector<int> n(256);

	vector<int> p2Regs;
	for(auto& c: inp){
		p2Regs.push_back(c);
	}
	vector<int> manualAdd = {17,31,73,47,23};
	p2Regs.insert(p2Regs.end(), manualAdd.begin(), manualAdd.end());

	int pos(0), skip(0);
	iota(n.begin(), n.end(), 0);
	
	for(int i = 0 ;i<64;i++){
		for(auto& len: p2Regs){
			iter(n, pos, len, skip);
		}
	}
	

	stringstream stream;
	stream<<setfill('0')<<hex;
	int temp = 0;
	for(int i = 0;i<n.size();i++){
		if(i%16==0){
			temp = n[i];
			continue;
		}
		temp^=n[i];
		if(i%16 == 15){
			stream<<setw(2)<<temp;
		}
	}
	return stream.str();
}