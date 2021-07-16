#include "../util.h"


using namespace std;

int p1(vector<string>& layers){

	int m = 25*6;
	int temp;
	int ones, twos;
	int out;
	for(auto& l : layers){
		temp = 0;
		ones = twos = 0;
		for(auto c: l){
			switch(c){
				case '0':
					temp++; break;
				case '1':
					ones++; break;
				case '2':
					twos++; break;
			}
		}
		if(temp < m){
			out = ones*twos;
			m = temp;
		}
	}
	return out;
}

void p2(vector<string>& layers){
	string out((25*6), '2');
	int j;
	for(int i = 0;i<25*6;i++){
		for(j = 0;layers[j][i]=='2';j++){}
		out[i] = layers[j][i];
	}

	for(int y = 0;y<6;y++){
		for(int x = 0;x<25;x++){
			cout<<(out[x+y*25]=='1'?"█":" ");
		}cout<<endl;
	}
}

int main(){
	fstream file("Day 8/input");
	string line;
	getline(file, line);
	vector<string> layers;
	int dim = 25*6;
	while(line.size() > 0){
		layers.push_back(line.substr(0,dim));
		line = line.substr(dim);
	}
	cout<<"[P1] "<<p1(layers)<<endl;
	cout<<"[P2] "<<endl;
	p2(layers);
}