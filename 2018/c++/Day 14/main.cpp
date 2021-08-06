#include "../aoc.h"

#define REGSSIZE 50000000
#define small uint_fast8_t

small regs[REGSSIZE] = {3,7};
int rsize = 2;
int inp;

int elf1(0), elf2(1);

static void print(){
	for(int i = 0;i<rsize;i++){
		if(i == elf1) cout<<"(";
		else if(i == elf2) cout<<"[";
		else cout<<" ";
		cout<<(int)regs[i];
		if(i == elf1) cout<<")";
		else if(i == elf2) cout<<"]";
		else cout<<" ";
	}cout<<endl;
}

int p2 = 0;
int sInd = 10;
small match[6];

static void steps(int count){
	small sum;
	while(rsize<count){
		if(regs[elf1] == 0 && regs[elf2] == 0){
			regs[rsize++] = 0;
			elf1++; elf2++;
			continue;
		}
		sum = regs[elf1]+regs[elf2];
		if(sum>=10){
			regs[rsize++] = sum/10;
			regs[rsize++] = sum%10;
		}else{
			regs[rsize++] = sum;
		}
		elf1=(elf1+1+regs[elf1])%rsize;
		elf2=(elf2+1+regs[elf2])%rsize;
		// print();
	}
	for(;sInd<=rsize-6;sInd++){
		
	}
}

int main(){
	fstream file("Day 14/input");
	file>>inp;
	for(int temp = inp, pos=5; temp;temp/=10){
		match[pos--] = temp%10;
	}
	for(int i = 0;i<6;i++){
		cout<<(int)match[i];
	}cout<<endl;
	// inp = 9;
	steps(inp+10);
	cout<<"[P1] ";
	for(int i = inp;i<inp+10;i++){
		cout<<(int)regs[i];
	}cout<<endl;
	while(p2==0){
		steps(rsize*2);
		cout<<rsize<<endl;
	}
}