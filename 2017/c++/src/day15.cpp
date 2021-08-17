#include "AOC.h"

inline unsigned long generate(unsigned long g, const unsigned long& factor){
	unsigned long prod = g*factor;
	g = (prod&0x7fffffff) + (prod>>31);
	return (g>>31 ? g-0x7fffffff : g);
}

inline unsigned long g2(unsigned long g, const unsigned long& factor, const int& mult){
	do{
		g = generate(g, factor);
	}while(g%mult != 0);
	return g;
}

chrono::time_point<std::chrono::steady_clock> day15(input_t& inp){
	unsigned long a, b;
	a = stoi(inp[0].substr(24));
	b = stoi(inp[1].substr(24));
	int p1 = 0;
	for(int i = 0;i<40000000;i++){
		a = generate(a, 16807);
		b = generate(b, 48271);
		if((a&0xffff) == (b&0xffff)) p1++;
	}

	a = stoi(inp[0].substr(24));
	b = stoi(inp[1].substr(24));
	int p2 = 0;
	for(int i = 0;i<5000000;i++){
		a = g2(a, 16807, 4);
		b = g2(b, 48271, 8);
		if((a&0xffff) == (b&0xffff)) p2++;
	}
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<p2<<endl;
	return done;
}