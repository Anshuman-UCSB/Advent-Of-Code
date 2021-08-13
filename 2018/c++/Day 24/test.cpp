#include "../aoc.h"
#include <algorithm>

int main(){
	vector<int> a = {4,2,5,3,1};
	vector<int*> b(5);
	for(int i = 0;i<5;i++){
		b[i] = &a[i];
	}
	cout<<a<<endl;
	
	auto comp = [](const int* a, const int* b) -> bool{
		return *a>*b;
	};

	sort(b.begin(), b.end(), comp);
	
	for(auto& v: b){
		cout<<*v<<" ";
	}cout<<endl;
	cout<<a<<endl;
	*b[0] = 10;
	cout<<a<<endl;
}