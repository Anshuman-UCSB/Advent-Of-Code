#include "AOC.h"

int getDistance(const pii& pos){
	int dist = abs(pos.x);
	dist+= (abs(pos.y)-dist)/2;
	return dist;
}

chrono::time_point<std::chrono::steady_clock> day11(input_t& inp){
	pii pos;
	stringstream ss(inp[0]);
	char t1, t2;
	int p2 = 0;
	while(ss>>t1){
		ss>>t2;
		if(t2 == ','){
			if(t1 == 'n')
				pos.y+=2;
			else
				pos.y-=2;
		}else{
			if(t1 == 'n')
				pos.y++;
			else
				pos.y--;
			
			if(t2 == 'e')
				pos.x++;
			else
				pos.x--;
			ss>>t2;
		}
		p2 = max(p2,getDistance(pos));
	}
	int p1 = getDistance(pos);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}