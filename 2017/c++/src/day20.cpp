#include "AOC.h"

struct particle{
	int x, y, z;
	int dx, dy, dz;
	int ax, ay, az;
	particle(){}
	particle(const string& line){
		stringstream ss(line);
		ss.seekg(ss.tellg()+3L);
		char t;
		ss>>x>>t>>y>>t>>z;
		ss.seekg(ss.tellg()+6L);
		ss>>dx>>t>>dy>>t>>dz;
		ss.seekg(ss.tellg()+6L);
		ss>>ax>>t>>ay>>t>>az;
	}
	void iter(){
		x+=(dx+=ax);
		y+=(dy+=ay);
		z+=(dz+=az);
	}
};

vector<particle> particles;

void removeCollisions(){
	set<tuple<int, int, int>> positions;
	set<tuple<int, int, int>> toRemove;
	for(auto& p: particles){
		if(positions.insert(make_tuple(p.x,p.y,p.z)).second == false){
			toRemove.insert(make_tuple(p.x,p.y,p.z));
		}
	}

	for(auto& coord: toRemove){
		for(int i = particles.size()-1;i>=0;i--){
			if(make_tuple(particles[i].x, particles[i].y, particles[i].z) == coord){
				particles.erase(particles.begin() + i);
			}
		}
	}
}

chrono::time_point<std::chrono::steady_clock> day20(input_t& inp){
	for(auto& l: inp)
		particles.emplace_back(l);
	int p1 = 0;
	int p1val = abs(particles[0].ax)+abs(particles[0].ay)+abs(particles[0].az);
	for(int i = 1; i<particles.size();i++){
		if(auto val = abs(particles[i].ax)+abs(particles[i].ay)+abs(particles[i].az); val<p1val){
			p1val = val;
			p1 = i;
		}
	}
	auto done = chrono::steady_clock::now();
	int old = particles.size();
	int flag = 0;
	for(;;){
		for(auto& p : particles)p.iter();
		removeCollisions();
		if(old == particles.size()){
			if(++flag > 9){
				// cout<<flag<<endl;
				break;
			}
		}else{
			flag = 0;
			old = particles.size();
		}
	}
	
	cout<<"[P1] "<<p1<<endl;
	cout<<"[P2] "<<particles.size()<<endl;
	//730 too high
	return done;
}