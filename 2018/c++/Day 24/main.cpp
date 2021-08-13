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

	Group(const string& line, bool friendly,int uid):uid(uid), friendly(friendly){
		stringstream ss(line);
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
		}else{
			ss>>t;
		}
		part2:;
		// cout<<t<<endl;
		ss>>t>>t>>t>>t>>atk>>t;
		switch(t[0]){
			case 'b': atkType = 0; break;
			case 's': atkType = 1; break;
			case 'c': atkType = 2; break;
			case 'f': atkType = 3; break;
			case 'r': atkType = 4; break;
		}
		ss>>t>>t>>t>>initiative;
		attacked = false;
	}

	int getEffectivePower() const{
		return atk*units;
	}

	int getDamage(const Group& g) const{
		if(units <=0) return -1;
		if(g.strong[atkType]) return -2;
		if(g.weak[atkType]) return units*atk*2;
		return units*atk;
	}

	void print() const{
		cout<<(attacked?"*":"")<<units<<(friendly?" ally ": " enemy ")<<"units with "<<unitHP<<" hp,	with "<<initiative<<"	initiative."<<endl;
		cout<<"  Attack: "<<atk;
		switch(atkType){
			case 0: cout<<" bludgeoning damage."<<endl;break;
			case 1: cout<<" slashing damage."<<endl;break;
			case 2: cout<<" cold damage."<<endl;break;
			case 3: cout<<" fire damage."<<endl;break;
			case 4: cout<<" radiation damage."<<endl;break;
		}
		cout<<"  Weak:		"<<weak<<endl;
		cout<<"  Immune:	"<<strong<<endl;
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

map<int, Group> groups;
vector<int> initiativeOrder;

static void printHeader(){
	cout<<"\nImmune System:"<<endl;
	for(auto& [id, g]: groups)
		if(g.friendly && g.units>0)
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
	cout<<"Infection:"<<endl;
	for(auto& [id, g]: groups)
		if(!g.friendly && g.units>0)
			cout<<"  Group "<<g.uid<<" contains "<<g.units<<" units"<<endl;
}

auto turnOrder = [](const int& a, const int& b) -> bool{
		return make_tuple(groups[a].getEffectivePower(), groups[a].initiative)
			 > make_tuple(groups[b].getEffectivePower(), groups[b].initiative);
	};

int rNum = 1;
bool chooseTargets(){
	vector<int> targetSel = initiativeOrder;
	sort(targetSel.begin(), targetSel.end(), turnOrder);
	//assume all set to not attacked yet
	bool done = true;
	for(auto& attacker: targetSel){
		auto& g = groups[attacker];
		g.target = -1;
		auto mComp = make_tuple(-1, 0, 0); //dmg, ep, init
		// g.print();
		for(auto& potentialTarget: targetSel){
			auto& t = groups[potentialTarget];
			if(t.friendly == g.friendly) continue; 	//attacking friend
			if(t.attacked) continue; 				//already targeted
			if(auto tComp = make_tuple(g.getDamage(t), t.getEffectivePower(), t.initiative); tComp > mComp){
				mComp = tComp;
				g.target = potentialTarget;
				done = false;
			}
		}
		groups[g.target].attacked = true;
	}
	return !done;
}

bool executeAttacks(){
	bool done = true;
	int old;
	for(auto& id: initiativeOrder){
		auto& g = groups[id];
		if(g.units <=0 || g.target == -1) continue; //dead or no target
		auto& t = groups[g.target];
		old = t.units;
		// cout<<g<<" atk:"<<g.getDamage(t)<< " with units having "<<t.unitHP<<" hp. to "<<t<<endl;
		t.units -= min(t.units, g.getDamage(t)/t.unitHP);
		// cout<<"Target now at "<<t.units<<" units. "<<endl;
		if(t.units != old)
			done = false;
	}
	for(int i = initiativeOrder.size()-1;i>=0;i--){
		groups[initiativeOrder[i]].attacked = false;
		if(groups[initiativeOrder[i]].units<=0){
			// cout<<groups[initiativeOrder[i]]<< "Was killed."<<endl;
			initiativeOrder.erase(initiativeOrder.begin() + i );
		}
	}
	return done;
}

void simulate(const map<int, Group>& orig, int boost = 0){
	groups = orig;
	
	for(auto& [ignore, g]: groups){
		if(g.friendly) g.atk+=boost;
	}
	auto initiativeCompare = [](const int& a, const int& b){
		return groups[a].initiative>groups[b].initiative;
	};
	initiativeOrder.clear();
	for(auto& [id, g]: groups)
		initiativeOrder.push_back(id);
	sort(initiativeOrder.begin(), initiativeOrder.end(), initiativeCompare);
	while(chooseTargets()){
		if(executeAttacks()) return;
		vector<int> aUnits, eUnits;
		// for(auto& [ignore, g]: groups){
		// 	auto& t = (g.friendly?aUnits:eUnits);
		// 	if(g.units>0)
		// 		t.push_back(g.units);
		// }
		// sort(aUnits.begin(), aUnits.end());
		// sort(eUnits.begin(), eUnits.end());
		// // cout<<"	"<<rNum<<endl;
		// // cout<<aUnits<<endl<<eUnits<<endl<<endl;
		// rNum++;
		// // printHeader();
	}
}

int main(){
	fstream file("Day 24/input");
	string line, line2;
	getline(file, line);
	int uId(0);
	while(getline(file, line)){
		if(line.size() == 0) break;
		groups[uId++] = Group(line, true, uId);
	}
	getline(file, line);
	while(getline(file, line)){
		groups[uId++] = Group(line, false, uId);
	}
	auto orig = groups;


	// printHeader();
	// groups[19].print();
	simulate(orig);
	// printHeader();
	//[6702, 8588, 254, 819, 7479, 735, 2326, 8453, 2652]
	int p1 = 0;
	for(auto& [id, g]: groups){
		if(g.friendly == false && g.units>0)p1+=g.units;
	}
	cout<<"[P1] "<<p1<<endl;
	//14224 too low
	//38023 too high
	//43300 too high

	bool done = false;
	int p2 = 0;
	for(int boost = 0;!done;boost++){
		done = true;
		// cout<<boost<<endl;
		simulate(orig, boost);
		p2 = 0;
		for(auto& [ignore, g]: groups){
			// g.print();
			if(g.friendly && g.units>0) p2 += g.units;
			if(g.friendly == false && g.units>0){
				done = false;
				// cout<<boost<<endl;
				break;
			}
		}
	}
	cout<<"[P2] "<<p2<<endl;
	// 6842 too high
}