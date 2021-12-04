#include "AOC.h"
#include <chrono>
#define STR1(x)  #x
#define STR(x)  STR1(x)

static const advent adventDays[] = {
	{ day01, "/input/day01.txt" },
	{ day02, "/input/day02.txt" },
	{ day03, "/input/day03.txt" },
	{ day04, "/input/day04.txt" },
	{ day05, "/input/day05.txt" },
	{ day06, "/input/day06.txt" },
	{ day07, "/input/day07.txt" },
	{ day08, "/input/day08.txt" },
	{ day09, "/input/day09.txt" },
	{ day10, "/input/day10.txt" },
	{ day11, "/input/day11.txt" },
	{ day12, "/input/day12.txt" },
	{ day13, "/input/day13.txt" },
	{ day14, "/input/day14.txt" },
	{ day15, "/input/day15.txt" },
	{ day16, "/input/day16.txt" },
	{ day17, "/input/day17.txt" },
	{ day18, "/input/day18.txt" },
	{ day19, "/input/day19.txt" },
	{ day20, "/input/day20.txt" },
	{ day21, "/input/day21.txt" },
	{ day22, "/input/day22.txt" },
	{ day23, "/input/day23.txt" },
	{ day24, "/input/day24.txt" },
	{ day25, "/input/day25.txt" },
};

static input_t loadInput(const string& path){
	fstream file(STR(SOURCE_DIR)+path);
	
	string line;
	input_t out;
	while(getline(file, line))
		out.push_back(line);
	return out;
}

int main(int argc, char **argv){
	if(argc == 1){
		double totalTime = 0;
		for(int i = 0;i<25;i++){
			auto &A = adventDays[i];
			input_t inp = loadInput(A.input_file);
			cout<<"	DAY "<<i+1<<": "<<endl;
			auto t0 = chrono::steady_clock::now();
			auto elapsed = (*A.fn)(inp)-t0;
			totalTime += elapsed.count();
			printf("[%ld μs]\n", int64_t(elapsed.count() * 1e-3));
			cout<<endl;
		}
		printf("Total: %ld μs\n", int64_t(totalTime * 1e-3));
	}else{
		auto &A = adventDays[atoi(argv[1])-1];
		input_t inp = loadInput(A.input_file);
		cout<<"	DAY "<<atoi(argv[1])<<":"<<endl;
		auto t0 = chrono::steady_clock::now();
		(*A.fn)(inp);
		auto elapsed = chrono::steady_clock::now()-t0;
		printf("[%ld μs]\n", int64_t(elapsed.count() * 1e-3));
	}
}