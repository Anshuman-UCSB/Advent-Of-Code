#include "../aoc.h"
#include <sstream>
#include <bitset>
#include <algorithm>

int maxInit = 0;

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
		maxInit = max(maxInit, initiative);
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
};

ostream& operator<<(ostream& os, const Group& g){
	os<<g.units<<(g.friendly?" ally ": " enemy ")<<"units with "<<g.unitHP<<" hp,	with "<<g.initiative<<"	initiative."<<endl;
	os<<"  Attack: "<<g.atk;
	switch(g.atkType){
		case 0: cout<<" bludgeoning damage."<<endl;break;
		case 1: cout<<" slashing damage."<<endl;break;
		case 2: cout<<" cold damage."<<endl;break;
		case 3: cout<<" fire damage."<<endl;break;
		case 4: cout<<" radiation damage."<<endl;break;
	}
	os<<"  Weak:		"<<g.weak<<endl;
	os<<"  Immune:	"<<g.strong<<endl;
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

set<int> ally, enemy;
vector<Group> groups;

static void printAll(){
	cout<<"\nImmune System:"<<endl;
	for(auto& g: groups)
		if(ally.count(g.uid))
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
	cout<<"Infection:"<<endl;
	for(auto& g: groups)
		if(enemy.count(g.uid))
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
}

auto turnOrder = [](const Group& a, const Group& b) -> bool{
		if(a.getEffectivePower() > b.getEffectivePower())
			return true;
		else if(a.getEffectivePower() == b.getEffectivePower())
			return a.initiative > b.initiative;
		return false;
	};

void chooseTargets(){
	for(auto& g : groups){
		g.attacked = false;
	}
	sort(groups.begin(), groups.end(), turnOrder);
	for(auto& g: groups) cout<<g.uid<<" ";cout<<endl;
	
	// for(auto& g: order)cout<<g.units<<" :	"<<g.getEffectivePower()<<endl;

	printAll();
	for(auto& g: groups){
		if(g.units<=0) continue;
		auto& e = (g.friendly?enemy:ally);
		g.target = -1;
		auto comp = make_tuple(0,0,0); //dmg, ep, init
		for(int i = 0;i<groups.size();i++){
			auto& tempG = groups[i];
			if(tempG.attacked) continue;
			if(e.count(tempG.uid) == 0) continue;
			auto tComp = make_tuple(g.getDamage(tempG), tempG.getEffectivePower(), tempG.initiative);
			// cout<<groups[i].uid<<" compare: "<<tComp<<endl;
			if(g.target==-1 || tComp>comp){
				g.target = tempG.uid;
				comp = tComp;
			}
		}
		cout<<g.uid<<" reserved "<<g.target<<" for attack. "<<endl;
		for(auto& g: groups){
			if(g.uid == g.target){
				g.attacked = true;
			}
		}
	}
	cout<<endl;
	for(auto& g: groups){
		cout<<(g.friendly?"Immune System":"Infection")<<" group "<<g.uid<<" targets defending group "<<g.target<<endl;
	}
}

void executeAttacks(){
	for(int init = maxInit;init>0;init--){
		for(auto& g: groups){
			if(g.initiative != init) continue;
			if(g.uid == -1 || g.units <=0){
				continue;
			}
			for(auto& t: groups){
				if(t.uid!=g.target) continue;
				int dmg = g.getDamage(t);
				cout<<g.uid<<" hits "<<t.uid<<" for "<<dmg<<endl;
				t.units-= (dmg/t.unitHP);
			}
			break;
		}
	}
	for(int i = groups.size()-1;i>=0;i--){
		if(groups[i].units<=0){
			groups.erase(groups.begin()+i);
		}
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
		groups.emplace_back(line, line2, true, uId);
		ally.insert(uId++);
	}
	while(getline(file, line)){
		getline(file, line2);
		if(line2[0] == 'I'){
			break;
		}
		groups.emplace_back(line, line2, false, uId);
		enemy.insert(uId++);
	}


	chooseTargets();
	executeAttacks();
	chooseTargets();
	executeAttacks();
	printAll();
}