#include "../util.h"

void p1();
void p2();

int main(){
	p1();
	p2();
}

int p1mass(int inp){
	return (inp/3)-2;
}

int p2mass(int inp){
	if(inp <= 0 ){
		return 0;
	}
	return max((inp/3)-2,0) + p2mass((inp/3)-2);
}

void p1(){
	int p1 = 0;
	auto inp = readInput();
	for(auto& s: inp){
		p1+=p1mass(stoi(s));
	}
	cout<<p1<<endl;
}

void p2(){
	int p2 = 0;
	auto inp = readInput();
	for(auto& s: inp){
		p2+=p2mass(stoi(s));
	}
	cout<<p2<<endl;
}

