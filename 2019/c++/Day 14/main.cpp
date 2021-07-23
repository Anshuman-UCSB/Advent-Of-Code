#include "../prints.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#define ll long long
#define ORECOUNT 1000000000000
// #define ORECOUNT 100000000

struct reagent{
	string item;
	int amt;
	reagent(){}
	reagent(string inp){
		stringstream ss(inp);
		ss>>amt>>item;
	}
	reagent(string item, int amt):item(item), amt(amt){
		if(item.back() == ','){
			this->item.pop_back();
		}
	}

	bool operator<(const reagent& r) const {
		if(item<r.item){
			return true;
		}
		if(item == r.item && amt<r.amt){
			return true;
		}
		return false;
	}

};

struct recipie{
	reagent out;
	vector<reagent> inp;
	recipie(){}
	string a;
	int b;
	recipie(string line){
		a = ",";
		stringstream ss(line);
		while(a.back() == ','){
			ss>>b>>a;
			inp.emplace_back(a, b);
		}
		ss>>a>>b>>a;
		out = reagent(a,b);
	}
};

ostream& operator<<(ostream& os, const reagent& r){
	os<<r.amt<<" "<<r.item;
	return os;
}

ostream& operator<<(ostream& os, const recipie& r){
	cout<<r.inp<<" => "<<r.out;
	return os;
}



map<string, recipie> recipies;
void initRecipies(){
	fstream file("Day 14/input");
	string line;
	string a;
	int b;
	while(getline(file, line)){
		recipie r(line);
		// cout<<r.end<<endl;
		recipies[r.out.item] = r;
	}
}

map<string, ll> counts;
void printCounts(){
	for(auto p: counts){
		cout<<p.first<<", "<<p.second<<endl;
	}
}

void make(const reagent& r){
	// cout<<"make called on "<<r<<endl;
	counts[r.item] -= r.amt; //use up r.amt of r.item
	while(r.item != "ORE" && counts[r.item]<0){
		counts[r.item] += recipies[r.item].out.amt;
		for(auto& reg: recipies[r.item].inp){
			make(reg);
		}
	}
}
bool make2(const reagent& r, ll mult){
	// cout<<"make called on "<<r<<endl;
	
	counts[r.item] -= r.amt*mult; //use up r.amt of r.item
	if(r.item == "ORE" && counts[r.item] < -ORECOUNT){
		return false;
	}
	if(r.item != "ORE" && counts[r.item]<0){
		ll newMult;
		// for(newMult=1;recipies[r.item].out.amt*newMult+counts[r.item]<0;newMult++){}
		ll k;
		for(k = -counts[r.item];k%recipies[r.item].out.amt!= 0;k++){}
		k/=recipies[r.item].out.amt;
		newMult = k;
		if(newMult != k){
			cout<<"ERROR: "<<newMult<<" = "<< k/recipies[r.item].out.amt<<endl;
		}
		// newMult = k/recipies[r.item].out.amt;		
		
		counts[r.item] += recipies[r.item].out.amt*newMult;
		for(auto& reg: recipies[r.item].inp){
			if(!make2(reg, newMult)){
				return false;
			}
		}
	}
	return true;
}

void p1(){
	// counts["FUEL"] = -1; //request 1 fuel to be made
	make2(reagent("FUEL", 1), 1);
	cout<<"[P1] "<<-counts["ORE"]<<endl;
}

void p2(){
	counts.clear();
	int i;
	make2(reagent("FUEL", 1), 1);
	for(i = 2;make2(reagent("FUEL", 1), i/2);i*=2){
		// cout<<"Upper limit of "<<i<<endl;
		// printCounts();
		// string trash;
		// cin>>trash;
	}
	// cout<<"Upper limit of "<<i<<endl;
	counts.clear();
	int l, h;
	l = i/2;
	h = i;
	int m;
	while(l+1<h){
		counts.clear();
		m = (l+h)/2;
		if(make2(reagent("FUEL", 1), m)){
			l = m;
			// cout<<"Could make "<<m<<" fuel."<<endl;
		}else{
			// cout<<"Could not make "<<m<<" fuel."<<endl;
			h = m-1;
		}
		// cout<<l<<"->"<<h<<endl;
	}
	cout<<"[P2] "<<h<<endl;
}

int main(){
	initRecipies();
	p1();
	p2();
}