#pragma once
#include <iostream>
#include <vector>

#define ll long long
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

class IntCode{
	public:
		vector<ll> regs;		//registers
		int ind, rel;			//index, relative index
		vector<ll> inp, out;	//inputs, outputs
		bool done, debug;		//finished, debug prints or not

		IntCode(const vector<ll>& inputRegs, bool debug = false);
		IntCode();

	private:
		int getType(int pos);
		ll getParam(int pos);
		void setParam(int pos, ll val);
};