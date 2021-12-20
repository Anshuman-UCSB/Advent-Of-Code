#include "AOC.h"

bool inRange(int x, int y, int size){
	return 0<=x && x<size && 0<=y && y<size;
}

int iter(vector<vector<bool>>& img, const vector<bool>& alg){
	int sz = img.size();
	bool t[200][200];
	int lights = 0;
	for(int y = 0;y<sz;y++){
		for(int x = 0;x<sz;x++){
			int b = 0;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++){
					b<<=1;
						b+=inRange(x+dx, y+dy, sz)&&img[y+dy][x+dx];
				}
			t[y][x] = alg[b];
		}
	}
	for(int y = 0;y<sz;y++){
		for(int x = 0;x<sz;x++){
			int b = 0;
			for(int dy = -1;dy<=1;dy++)
				for(int dx = -1;dx<=1;dx++){
					b<<=1;
					b+=!(inRange(x+dx, y+dy, sz))||(t[y+dy][x+dx]);
				}
			lights += img[y][x] = alg[b];
		}
	}
	return lights;
}

chrono::time_point<std::chrono::steady_clock> day20(input_t& inp){
	int p1(0), p2(0);
	vector<bool> alg;
	for(auto c:inp[0])
		alg.push_back(c!='.');
	vector<vector<bool>> img(200, vector<bool>(200));
	for(int i = 2;i<inp.size();i++)
		for(int j = 0;j<inp[i].size();j++)
			img[i+48][j+50] = inp[i][j]!='.';
	p1 = iter(img, alg);
	for(int i = 1;i<24;i++)
		iter(img, alg);
	p2 = iter(img, alg);
	
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}