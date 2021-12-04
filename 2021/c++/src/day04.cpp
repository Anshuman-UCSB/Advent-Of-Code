#include "AOC.h"

bool winner(const vector<int>& board, const unordered_set<int>& called){
	for(int i = 0;i<5;i++){
		for(int j = 0;j<5;j++)
			if(!called.count(board[i+j*5]))
				goto next;
		return true;
		next:;
		for(int j = 0;j<5;j++)
			if(!called.count(board[j+i*5]))
				goto next2;
		return true;
		next2:;
	}
	return false;
}

int score(const vector<int>& board, const unordered_set<int>& called){
	int s = 0;
	for(auto& v: board)
		if(!called.count(v))
			s+=v;
	return s;
}

int p1(const vector<vector<int>>& boards, const vector<int>& nums){
	unordered_set<int> called;
	for(auto& n: nums){
		called.insert(n);
		for(const auto& b: boards)
			if(winner(b, called))
				return score(b, called)*n;
	}
	return -1;
}
int p2(vector<vector<int>> boards, const vector<int>& nums){
	unordered_set<int> called;
	for(auto& n: nums){
		called.insert(n);
		if(boards.size() == 1)
			return score(boards[0], called)*n;
		for(int i = boards.size()-1;i>=0;i--)
			if(winner(boards[i], called))
				boards.erase(boards.begin()+i);
	}
	return -1;
}

chrono::time_point<std::chrono::steady_clock> day04(input_t& inp){
	vector<int> nums;
	vector<vector<int>> boards;
	int t;
	char trash;
	stringstream ss(inp[0]);
	while(ss>>t>>trash)
		nums.push_back(t);
	
	boards.emplace_back();
	for(int i = 1;i<inp.size();i++){
		if(inp[i].empty()) continue;
		if(boards.back().size() == 25)
			boards.emplace_back();
		stringstream ss(inp[i]);
		while(ss>>t)
			boards.back().push_back(t);
	}
	
	cout<<"[P1] "<<p1(boards, nums)<<"\n[P2] "<<p2(boards, nums)<<endl;
	auto done = chrono::steady_clock::now();
	return done;
}