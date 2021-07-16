#include "../util.h"

int main(){
	int low, high, p1(0), p2(0), count;
	char trash, min, dup;
	bool p1Valid, p2Valid;
	string temp;
	fstream file("Day 4/input");
	string line;
	getline(file, line);
	stringstream ss(line);
	ss>>low>>trash>>high;
	for(int i = low;i<=high;i++){
		temp = to_string(i);
		min = temp[0];
		count = 0;
		dup = temp[0];
		p1Valid = p2Valid = false;
		for(int j = 0;j<temp.size();j++){
			if(temp[j]<min){
				// cout<<"curr: "<<temp[j]<<" < "<<min<<endl;
				goto next; //not increasing
			}
			min = temp[j];
			if(temp[j] == dup){
				count++;
			}
			else{
				if(count == 2){
					p2Valid=true;
				}
				if(count>=2){
					p1Valid=true;
				}
				dup = temp[j];
				count = 1;
			}
		}
		if(count == 2){
			p2Valid=true;
		}
		if(count>=2){
			p1Valid=true;
		}
		p1+=p1Valid;
		p2+=p2Valid;
		next:;
	}

	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
}