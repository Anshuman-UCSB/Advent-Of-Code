#include "AOC.h"
#define state tuple<int, int, int, int>

int getRoll(int& roll){
	roll+=3;
	return (roll -4)%100+(roll-3)%100+(roll-2)%100+3;
}

chrono::time_point<std::chrono::steady_clock> day21(input_t& inp){
	vector<pair<int, ull>> dice = {{6,7}, {5,6}, {7,6}, {4,3}, {8,3}, {3,1}, {9,1}};
	int start1(inp[0].back()-'0'), start2(inp[1].back()-'0');
	map<state, ull> universe = {{make_tuple(start1, 0, start2, 0), 1}};
	ull p1win(0), p2win(0);
	ull pos1, score1, pos2, score2;
	ull p1, s1, p2, s2;
	while(!universe.empty()){
		map<state, ull> tuniv;
		for(auto& [st, count]: universe){
			tie(pos1, score1, pos2, score2) = st;
			for(auto& [r1, d1]: dice){
				p1 = (pos1+r1-1)%10+1;
				s1 = score1+p1;
				if(s1>=21){
					p1win+=count*d1;
					continue;
				}
				for(auto& [r2, d2]: dice){
					p2 = (pos2+r2-1)%10+1;
					s2 = score2+p2;
					if(s2>=21){
						p2win+=count*d1*d2;
						continue;
					}
					tuniv[make_tuple(p1, s1, p2, s2)]+=count*d1*d2;
				}
			}
		}
		universe = move(tuniv);
	}
	int roll = 1;
	pos1 = start1;
	pos2 = start2;
	score1 = score2 = 0;
	while(true){
		pos1=(pos1+getRoll(roll)-1)%10+1;
		score1+=pos1;
		if(score1>=1000){
			p1 = score2*(roll-1);
			break;
		}
		pos2=(pos2+getRoll(roll)-1)%10+1;
		score2+=pos2;
		if(score2>=1000){
			p1 = score1*(roll-1);
			break;
		}
	}
	p2 = max(p1win, p2win);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}