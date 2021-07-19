#include "../prints.h"
#include <utility>
#include <sstream>
#include <fstream>
#include <map>
#define reagent pair<string, int>

string upTo(string& inp, string pattern){
	string out = inp.substr(0, inp.find(pattern));
	inp=inp.substr(inp.find(pattern) + pattern.size());
	return out;
}

struct Recipie{
	vector<reagent> components;
	reagent output;
	Recipie(){
		output = make_pair("-1",-1);
	}
	Recipie(string inp){
		string left = upTo(inp, " => ");
		stringstream ss(inp);
		ss>>output.second>>output.first;
		
		while(left.find(",")!=string::npos){
			string temp = upTo(left, ", ");
			components.emplace_back();
			ss = stringstream(temp);
			ss>>components.back().second>>components.back().first;
		}
		ss = stringstream(left);
		components.emplace_back();
		ss>>components.back().second>>components.back().first;
	}
};

ostream& operator<<(ostream& os, Recipie& r){
	cout<<r.components<<" => "<<r.output;
	return os;
}
int level = 0;
void create(map<string, Recipie>& recipies, map<string, int>& needs, const reagent& make){
	if(make.first == "ORE"){
		needs["ORE"] += make.second;
		return;
	}
	// in needs:
	// positive means how much there is surplus
	// negative means how much needed
	// Recipie r = recipies[make.first];
	needs[make.first]-=make.second;
	for(auto& p: needs){
		if(p.second < 0){
			for(int i = 0;i<level;i++){cout<<"	";}
			cout<<"Needs more "<<p.first<<endl;
			Recipie r = recipies[make.first];
			while(p.second<0){
				p.second+=r.output.second;
				for(auto& reg: r.components){
					level++;
					create(recipies, needs, reg);
					level--;
				}
			}
			for(auto& n: needs){
				for(int i = 0;i<level;i++){cout<<"	";}
				cout<<" + "<<n.first<<", "<<n.second<<endl;
			}
		}
	}
}

int main(){
	fstream file("Day 14/input");
	string line;
	map<string, Recipie> m;
	while(getline(file, line)){
		Recipie r(line);
		m[r.output.first] = r;
	}
	// for(auto& p: m){
	// 	cout<<p.first<<" => "<<p.second<<endl;
	// }
	map<string, int> needs;
	reagent fuel = make_pair("FUEL", 1);
	create(m, needs, fuel);
	cout<<needs["ORE"]<<endl;
}