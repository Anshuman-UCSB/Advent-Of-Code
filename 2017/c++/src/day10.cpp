#include "AOC.h"
#include <iomanip>
#define SIZE 256

vector<int> n(SIZE);

void iter(int& pos, const int& length, int& skip){
	for(int i = 0;i<length/2;i++){
		swap(n[(pos+i)%SIZE], n[(pos+length-i-1)%SIZE]);
	}
	pos =(pos+length+skip++)%SIZE;
}

chrono::time_point<std::chrono::steady_clock> day10(input_t& inp){
	iota(n.begin(), n.end(), 0);
	int pos(0), skip(0);
	stringstream ss(inp[0]);
	int len;
	char t;
	while(ss>>len){
		iter(pos, len, skip);
		ss>>t;
	}
	int p1 = n[0]*n[1];

	vector<int> p2Regs;
	for(auto& c: inp[0]){
		p2Regs.push_back(c);
	}
	vector<int> manualAdd = {17,31,73,47,23};
	p2Regs.insert(p2Regs.end(), manualAdd.begin(), manualAdd.end());

	pos = skip = 0;
	iota(n.begin(), n.end(), 0);
	
	for(int i = 0 ;i<64;i++){
		for(auto& len: p2Regs){
			iter(pos, len, skip);
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
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<stream.str()<<endl;
	return done;
}

// 3efbe78a8d82f29979031a4aa0b16a9d
// 3cfbe78a8d82f29a79031a49a0b1689d

/*
	AoC 2017
	33efeb34ea91902bb2f59c9920caa6cd
	33efeb34ea91902bb2f59c9920caa6cd

	1,2,3
	3efbe78a8d82f29979031a4aa0b16a9d
	3efbe78a8d82f29979031a4aa0b16a9d
*/