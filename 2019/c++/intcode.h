#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <fstream>

#define ll long long
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v){
	cout<<"[";
	string delim = "";
	for(auto& val: v){
		cout<<delim<<val;
		delim = ", ";
	}cout<<"]";
	return os;
}

bool testOutput(string inp, const vector<ll>& out);
bool testOutput(string inp, const vector<ll>& out, const vector<ll>& inputs);

class IntCode{
	public:
		vector<ll> regs;		//registers
		int ind, rel;			//index, relative index
		vector<ll> inp, out;	//inputs, outputs
		bool done, debug;		//finished, debug prints or not

		IntCode(int day, bool debug = false);
		IntCode(string input, bool debug = false);
		IntCode(const vector<ll>& inputRegs, bool debug = false);
		IntCode();


		void push(ll val);		//push an input
		ll pop();				//pop an output
		
		void step();
		void run(bool print = false);

		void print();

	private:
		int getType(int pos);
		ll getParam(int pos);
		void setParam(int pos, ll val);
		void log(string inp);
};