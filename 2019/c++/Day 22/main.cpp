#include <iostream>
#include "../prints.h"
#include <fstream>
#include <utility>
#include <sstream>
#define ll long long
#define func pair<ll, ll>

ll MOD;

static inline ll add(ll a, ll b){
	return (MOD + (a+b)%MOD)%MOD;
}

static inline ll mult(ll a, ll b){
	if(b<0) {a*=-1; b*=-1;}
	while(a<0)a+=MOD;
	a%=MOD;
	ll res = 0;
	while(b){
		if (b&1) res = add(res, a);
		while(a<0)a+=MOD;
		a = (2*a)%MOD;
		b >>=1;
	}
	return res;
}

static inline ll exp(ll a, ll b){
	ll res = 1;
	if(b<0) {a*=-1; b*=-1;}
	while(a<0)a+=MOD;
	a%=MOD;
	while(b){
		if(b&1) res = mult(res, a);
		b>>=1;
		a = mult(a,a);
	}
	return res;	
}

static func compose(func a, func b){
	return func(mult(a.first, b.first), add(mult(a.second, b.first), b.second));
}

static func powCompose(func a, ll n){
	func g(1,0);
	while(n>0){
		if(n&1) g = compose(g, a);
		n>>=1;
		a = compose(a, a);
	}
	return g;
}

func read(){
	fstream file("Day 22/input");
	string line;
	func out(1,0);
	int n;
	string temp;
	while(getline(file, line)){
		if(line[0] == 'c'){
			stringstream ss(line);
			ss>>temp>>n;
			out.second = add(out.second, -n);
		}else if(line[5] == 'i'){
			out.first*=-1;
			out.second = add(-out.second, -1);
		}else{
			stringstream ss(line);
			ss>>temp>>temp>>temp>>n;
			out.first = mult(out.first, n);
			out.second = mult(out.second, n);
		}
	}
	return out;
}

void p1(){
	MOD = 10007;
	func f = read();
	cout<<"[P1] "<<add(f.second, mult(f.first, 2019))<<endl;
}

void p2(){
	MOD = 119315717514047;
	const ll SHUFFLES = 101741582076661;
	func f = read();
	cout<<f<<endl;
	f = powCompose(f, SHUFFLES);
	ll a, b;
	a = f.first;
	b = f.second;
	
	cout<<f<<endl;
}
int main(){
	p1();
	p2();
}