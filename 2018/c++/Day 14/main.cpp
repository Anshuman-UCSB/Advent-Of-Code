#include "../aoc.h"

#define REGSSIZE 50000000
#define small uint_fast8_t

small regs[REGSSIZE] = {3,7};
int size = 2;
int inp;

int elf1(0), elf2(1);

static void steps(int count){
	small sum;
	for(int i = 0;i<count;i++){
		if(regs[elf1] == 0 && regs[elf2] == 0){
			regs[size++] = 0;
			elf1++; elf2++;
			continue;
		}
		sum = regs[elf1]+regs[elf2];
		
	}
}

int main(){
	fstream file("Day 14/input");
	file>>inp;
	
}