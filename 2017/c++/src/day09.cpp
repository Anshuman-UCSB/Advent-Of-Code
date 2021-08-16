#include "AOC.h"

chrono::time_point<std::chrono::steady_clock> day09(input_t& inp){
	bool inTrash = false;
	int level = 0;
	int p1 = 0;
	int p2 = 0;
	for(int i = 0;i<inp[0].size();i++){
		auto& c = inp[0][i];
		if(c == '!'){
			i++; continue;
		}else if(c == '<' && inTrash == false){
			inTrash = true;
		}else if(c == '>' && inTrash == true){
			inTrash = false;
		}else if(inTrash){
			p2++;
		}else{
			if(c == '{'){
				p1+=++level;
			} else if(c == '}'){
				level--;
			}
		}
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}