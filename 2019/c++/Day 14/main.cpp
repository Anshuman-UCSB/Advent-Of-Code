#include "../prints.h"
#include <vector>
#include <map>
#include <sstream>
#include <fstream>

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

map<string, int> counts;
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

void p1(){
	// counts["FUEL"] = -1; //request 1 fuel to be made
	make(reagent("FUEL", 1));
	cout<<"[P1] "<<-counts["ORE"]<<endl;
}

int main(){
	initRecipies();
	p1();
}