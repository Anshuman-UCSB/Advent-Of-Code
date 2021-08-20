// breadth first search
// depth first search

#include <iostream>
using namespace std;

int factorial(int x){
	//4!= 4 x 3 x 2 x 1
	//0!= 1
	if(x == 0){
		return 1;
	}
	return x * factorial(x-1);
}
//4! = 4 x 3 x 2 x 1
//4^4= 4 x 4 x 4 x 4
int main(){
	cout<<factorial(4)<<endl;
}