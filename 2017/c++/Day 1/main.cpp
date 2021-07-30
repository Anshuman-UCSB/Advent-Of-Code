#include <iostream>
#include <fstream>
using namespace std;

int main(){
	fstream file("Day 1/input");
	string line;
	getline(file, line);
	int p1 = 0;
	int p2 = 0;
	for(int i = 0;i<line.size();i++){
		if(line[i] == line[(i+1)%line.size()])
			p1+=line[i]-'0';
		if(line[i] == line[(i+line.size()/2)%line.size()])
			p2+=line[i]-'0';
	}
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
}