#include "../aoc.h"
#include <sstream>
#include <bitset>
#include <algorithm>

struct Group{
	int units;
	int unitHP;
	int initiative;
	int atk;
	int atkType;
	int target;
	int uid;
	bitset<5> weak, strong;
	bool attacked;
	bool friendly;
	Group(){
		units = unitHP = initiative = 0;
		atk = 0;
		uid = -1;
		friendly = false;
	}

	Group(const string& line, const string& line2, bool friendly,int uid):uid(uid), friendly(friendly){
		stringstream ss(line + line2);
		string t;
		char tr;
		ss>>units>>t>>t>>t>>unitHP>>t>>t;
		ss>>tr;
		if(tr == '('){
			readSpecial:;
			ss>>t;
			if(t == "with"){
				goto part2;
			}
			if(t[0] == 'w'){
				ss>>t;
				readWeak:
				ss>>t;
				switch(t[0]){
					case 'b': weak[0]=1; break;
					case 's': weak[1]=1; break;
					case 'c': weak[2]=1; break;
					case 'f': weak[3]=1; break;
					case 'r': weak[4]=1; break;
				}
				if(t.back() == ',')
					goto readWeak;
			}
			if(t[0] == 'i'){ //immune
				ss>>t;
				readImmune:
				ss>>t;
				switch(t[0]){
					case 'b': strong[0]=1; break;
					case 's': strong[1]=1; break;
					case 'c': strong[2]=1; break;
					case 'f': strong[3]=1; break;
					case 'r': strong[4]=1; break;
				}
				if(t.back() == ',')
					goto readImmune;
			}
			goto readSpecial;
		}
		part2:;
		ss>>t>>t>>t>>t>>atk>>t;
		switch(t[0]){
			case 'b': atkType = 0; break;
			case 's': atkType = 1; break;
			case 'c': atkType = 2; break;
			case 'f': atkType = 3; break;
			case 'r': atkType = 4; break;
		}
		ss>>t>>t>>t>>initiative;
	}

	int getEffectivePower() const{
		return atk*units;
	}

	int getDamage(const Group& g) const{
		if(units <=0) return 0;
		if(g.strong[atkType]) return 0;
		if(g.weak[atkType]) return units*atk*2;
		return units*atk;
	}

	void print(const Group& g) const{
		cout<<g.units<<(g.friendly?" ally ": " enemy ")<<"units with "<<g.unitHP<<" hp,	with "<<g.initiative<<"	initiative."<<endl;
		cout<<"  Attack: "<<g.atk;
		switch(g.atkType){
			case 0: cout<<" bludgeoning damage."<<endl;break;
			case 1: cout<<" slashing damage."<<endl;break;
			case 2: cout<<" cold damage."<<endl;break;
			case 3: cout<<" fire damage."<<endl;break;
			case 4: cout<<" radiation damage."<<endl;break;
		}
		cout<<"  Weak:		"<<g.weak<<endl;
		cout<<"  Immune:	"<<g.strong<<endl;
	}
};

ostream& operator<<(ostream& os, const Group& g){
	os<<"["<<g.uid<<"]";
	return os;
}

/**
 * Attack      |  bitset pos
 * -------------------------
 * bludgeoning |           0
 * slashing    |           1
 * cold        |           2
 * fire        |           3
 * radiation   |           4
 */

vector<Group> groups;

static void printHeader(){
	cout<<"\nImmune System:"<<endl;
	for(auto& g: groups)
		if(g.friendly && g.units>0)
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
	cout<<"Infection:"<<endl;
	for(auto& g: groups)
		if(!g.friendly && g.units>0)
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
}

auto turnOrder = [](const Group* a, const Group* b) -> bool{
		return make_tuple(a->getEffectivePower(), a->initiative) > make_tuple(b->getEffectivePower(), b->initiative);
	};

bool chooseTargets(){
	vector<Group*> order(groups.size());
	for(int i = 0;i<groups.size();i++){
		order[i] = &groups[i];
		groups[i].attacked = false;
	}
	sort(order.begin(), order.end(), turnOrder);
	bool done = true;
	for(auto& gp: order){
		auto& g = *gp;
		if(g.units<=0){
			g.attacked = true;
			continue;
		}
		int maxDmg = 0;
		g.target = -1;
		for(int i = 0;i<groups.size();i++){
			if(groups[i].units<=0) continue;
			if(groups[i].friendly != g.friendly && groups[i].attacked == false){
				if(g.target == -1 || g.getDamage(groups[i]) > maxDmg || 
					(g.getDamage(groups[i]) == maxDmg && 
					groups[i].getEffectivePower() > groups[g.target].getEffectivePower())
				){
					maxDmg = g.getDamage(groups[i]);
					g.target = i;
					done = false;
				}
			}
		}
		// cout<<g<<" attacking "<<groups[g.target]<<endl;
		groups[g.target].attacked = true;
	}
	order.clear();
	return done;
	// for(auto& o: order)cout<<*o<<" ";cout<<endl;
}

void executeAttacks(){
	for(int i = 0;i<groups.size();i++){
		auto& g = groups[i];
		if(g.units<=0) continue;
		auto& trg = groups[g.target];
		cout<<g<<" attacked "<<trg<<" killing "<< min(g.getDamage(trg)/trg.unitHP, trg.units)<<" units."<<endl;
		trg.units -= min(g.getDamage(trg)/trg.unitHP, trg.units);
	}

}

void simulate(){
	for(;;){
		// printHeader();
		if(chooseTargets()){
			return;
		}
		executeAttacks();
	}
}

int main(){
	fstream file("Day 24/input");
	string line, line2;
	getline(file, line);
	int uId(0);
	while(getline(file, line)){
		getline(file, line2);
		if(line2[0] == 'I'){
			break;
		}
		groups.emplace_back(line, line2, true, uId++);
	}

	auto initiativeCompare = [](const Group& a, const Group& b){
		return a.initiative>b.initiative;
	};
	while(getline(file, line)){
		getline(file, line2);
		if(line2[0] == 'I'){
			break;
		}
		groups.emplace_back(line, line2, false, uId++);
	}
	sort(groups.begin(), groups.end(), initiativeCompare);

	simulate();
	int p1 = 0;
	for(auto& g: groups){
		if(g.units>0)p1+=g.units;
	}
	cout<<"[P1] "<<p1<<endl;
}