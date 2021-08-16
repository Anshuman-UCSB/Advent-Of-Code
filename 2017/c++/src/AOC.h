#include <iostream>
#include <fstream>
#include <sstream>
#include "prints.h"
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stack>
#include <queue>

#define pii pair<int, int>
#define x first
#define y second

#define input_t vector<string>

using namespace std;

struct advent{
	chrono::time_point<std::chrono::steady_clock> (*fn)(input_t&);
	string input_file;
};

chrono::time_point<std::chrono::steady_clock> day01(input_t&);
chrono::time_point<std::chrono::steady_clock> day02(input_t&);
chrono::time_point<std::chrono::steady_clock> day03(input_t&);
chrono::time_point<std::chrono::steady_clock> day04(input_t&);
chrono::time_point<std::chrono::steady_clock> day05(input_t&);
chrono::time_point<std::chrono::steady_clock> day06(input_t&);
chrono::time_point<std::chrono::steady_clock> day07(input_t&);
chrono::time_point<std::chrono::steady_clock> day08(input_t&);
chrono::time_point<std::chrono::steady_clock> day09(input_t&);
chrono::time_point<std::chrono::steady_clock> day10(input_t&);
chrono::time_point<std::chrono::steady_clock> day11(input_t&);
chrono::time_point<std::chrono::steady_clock> day12(input_t&);
chrono::time_point<std::chrono::steady_clock> day13(input_t&);
chrono::time_point<std::chrono::steady_clock> day14(input_t&);
chrono::time_point<std::chrono::steady_clock> day15(input_t&);
chrono::time_point<std::chrono::steady_clock> day16(input_t&);
chrono::time_point<std::chrono::steady_clock> day17(input_t&);
chrono::time_point<std::chrono::steady_clock> day18(input_t&);
chrono::time_point<std::chrono::steady_clock> day19(input_t&);
chrono::time_point<std::chrono::steady_clock> day20(input_t&);
chrono::time_point<std::chrono::steady_clock> day21(input_t&);
chrono::time_point<std::chrono::steady_clock> day22(input_t&);
chrono::time_point<std::chrono::steady_clock> day23(input_t&);
chrono::time_point<std::chrono::steady_clock> day24(input_t&);
chrono::time_point<std::chrono::steady_clock> day25(input_t&);