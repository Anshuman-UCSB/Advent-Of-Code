#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day03(input_t& inp){
	int p1(0), p2(0);
	int width = inp[0].size();

	int counter;
	string eps, gam;
	for(int i = 0;i<width;i++){
		counter = 0;
		for(auto& w: inp){
			counter+=w[i]=='1'?1:-1;
		}
		if(counter>=0){
			eps+='1';
			gam+='0';
		}else{
			eps+='0';
			gam+='1';
		}
	}
	p1 = stoi(eps, 0, 2)* stoi(gam, 0, 2);

	vector<string> oxy(inp), co2(inp);
	int ox(0), co(0);
	int oxyc, co2c;
	for(int i =0;i<width;i++){
		oxyc = co2c = 0;
		for(auto& w: oxy)
			oxyc+=(w[i]=='1'?1:-1);
		for(auto& w: co2)
			co2c+=(w[i]=='1'?1:-1);
		if(!ox){
			for(int j = oxy.size()-1;j>=0;j--)
				if(oxy[j][i] != (oxyc>=0?'1':'0')){
					oxy.erase(oxy.begin()+j);
				}
			if(oxy.size() == 1)
				ox = stoi(oxy[0],0,2);
		}
		if(!co){
			for(int j = co2.size()-1;j>=0;j--)
				if(co2[j][i] == (co2c>=0?'1':'0'))
					co2.erase(co2.begin()+j);
			if(co2.size() == 1)
				co = stoi(co2[0],0,2);
		}
		if(ox && co)
			break;
	}
	p2 = co*ox;
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}