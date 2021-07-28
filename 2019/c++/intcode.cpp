#include "intcode.h"

	
IntCode::IntCode(string input, bool debug){
	regs = vector<ll>();
	stringstream ss(input);
	ll temp;
	char trash;
	while(ss>>temp>>trash){
		regs.push_back(temp);
	}
	regs.push_back(temp);

	ind = 0;
	rel = 0;
	done = false;
	this->debug = debug;
	if(debug){
		log("debug turned on!");
	}
}

IntCode::IntCode(int day, bool debug){
	fstream file("Day "+to_string(day)+"/input");
	string line;
	getline(file, line);
	regs = vector<ll>();
	stringstream ss(line);
	ll temp;
	char trash;
	while(ss>>temp>>trash){
		regs.push_back(temp);
	}
	regs.push_back(temp);

	ind = 0;
	rel = 0;
	done = false;
	this->debug = debug;
	if(debug){
		log("debug turned on!");
	}
}
	
IntCode::IntCode(const vector<ll>& inputRegs, bool debug){
	regs = vector<ll>(inputRegs);
	ind = 0;
	rel = 0;
	done = false;
	this->debug = debug;
}

IntCode::IntCode(){
	ind = 0;
	rel = 0;
	done = false;
	debug = false;
}


void IntCode::step(){
	ll opc = regs[ind]%100;
	ll a, b;
	log("OPC: "+to_string(opc));
	switch(opc){
		case 1: //add opc
			a = getParam(1);
			b = getParam(2);			
			log("adding "+to_string(a)+" and "+to_string(b));
			setParam(3, a+b);
			ind+=4;
			break;
		case 2: //mult opc
			a = getParam(1);
			b = getParam(2);			
			log("multiplying "+to_string(a)+" and "+to_string(b));
			setParam(3, a*b);
			ind+=4;
			break;
		case 3:	//input
			assert(!inp.empty());
			setParam(1, inp[0]);
			log("Reading "+to_string(inp[0])+" as input.");
			assert(!inp.empty());
			inp.erase(inp.begin());
			ind+=2;
			break;
		case 4: //output
			out.emplace_back(getParam(1));
			log("Pushing output "+to_string(getParam(1)));
			ind+=2;
			break;
		case 5: //jump if true
			a = getParam(1);
			b = getParam(2);
			if(a)
				ind = b;
			else
				ind+=3;
			break;
		case 6: //jump if false
			a = getParam(1);
			b = getParam(2);
			if(a==0)
				ind = b;
			else
				ind+=3;
			break;
		case 7: //less than
			a = getParam(1);
			b = getParam(2);
			setParam(3, a<b);
			ind+=4;
			break;
		case 8: //equal to 
			a = getParam(1);
			b = getParam(2);
			setParam(3, a==b);
			ind+=4;
			break;
		case 9: //change rel pointer 
			a = getParam(1);
			rel+=a;
			ind+=2;
			break;
		case 99: //exit
			done = true;
			break;

		default:
			throw(-1);
	}
}

void IntCode::run(bool print){
	while(!done){
		step();
		if(print)
			this->print();
	}
}

void IntCode::print(){
	cout<<endl<<RED<<BOLD<<" + "<<RESET;
	cout <<RED<<BOLD<<"Registers:	"<<GREEN<<"("<<ind<<", "<<rel<<")"<<RESET<<endl;
	cout<<"	";
	for(int i = max(0, ind-1);i<min(int(regs.size()),ind+8);i++){
		if(i == ind)
			cout<<BOLD<<regs[i]<<" "<<RESET;
		else
			cout<<regs[i]<<" ";
	}cout<<endl;
	cout<<"	Size: "<<regs.size()<<endl;
	if(!inp.empty()){
		cout<<CYAN<<BOLD<<" + Inputs:"<<RESET<<endl;
		cout<<"	"<<inp<<endl;
	}
	if(!out.empty()){
		cout<<GREEN<<BOLD<<" + Outputs:"<<RESET<<endl;
		cout<<"	"<<out<<endl;
	}
	cout<<YELLOW<<BOLD<<" + "<<(done?"":"Not ")<<"done"<<RESET<<endl;
	
}

void IntCode::push(ll val){
	inp.push_back(val);
}

ll IntCode::pop(){
	ll temp = out[0];
	assert(!out.empty());
	out.erase(out.begin());
	return temp;
}

void IntCode::log(string inp){
	if(debug){
		cout<<GREEN<<"[DEBUG] "<<inp<<RESET<<endl;
	}
}

int IntCode::getType(int pos){
	ll opc = regs[ind];
	opc/=10;
	for(int i = 0;i<pos;i++){
		opc/=10;
	}
	return opc%10;
}

ll IntCode::getParam(int pos){
	int type = getType(pos);

	switch(type){
		case 0: return regs[regs[ind+pos]];
		case 1: return regs[ind+pos];
		case 2: return regs[rel + regs[ind+pos]];
	}
}

void IntCode::setParam(int pos, ll val){
	int type = getType(pos);

	while(ind+pos >= regs.size())
		regs.push_back(0);
	switch(type){
		case 0: 
			assert(ind+pos >=0);
			assert(regs[ind+pos] >=0);
			while(regs[ind+pos] >= regs.size())
				regs.push_back(0);
			regs[regs[ind+pos]] = val; break;
		case 1: 
			assert(ind+pos >=0);
			regs[ind+pos] = val; break;
		case 2: 
			while(rel + regs[ind+pos] >= regs.size())
				regs.push_back(0);
			assert(ind+pos >=0);
			assert(rel + regs[ind+pos] >0);
			regs[rel + regs[ind+pos]] = val; break;
	}
}

bool testOutput(string inp, const vector<ll>& out){
	IntCode c(inp);
	c.run();
	return c.out == out;
}

bool testOutput(string inp, const vector<ll>& out, const vector<ll>& inputs){
	IntCode c(inp);
	c.inp = vector<ll>(inputs);
	c.run();
	return c.out == out;
}