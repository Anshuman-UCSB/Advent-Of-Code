#include "AOC.h"

long long p1(0);
long long parse(string& str, long long& pos){
	p1+=stoll(str.substr(pos,3), 0, 2);
	string opc = str.substr(pos+3, 3);
	if(opc == "100"){
		pos += 6;
		string val;
		while(str[pos]=='1'){
			val+=str.substr(pos+1, 4);
			pos+=5;
		}
		val+=str.substr(pos+1, 4);
		pos+=5;
		return stoll(val, 0, 2);
	}else{
		vector<long long> parsed;
		if(str[pos+6] == '0'){
			pos+=7;
			long long length = stoll(str.substr(pos, 15), 0, 2)+15+pos;
			pos+=15;
			while(pos != length)
				parsed.push_back(parse(str, pos));
		}else{
			long long count = stoll(str.substr(pos+7, 11), 0, 2);
			pos+=18;
			for(long long i = 0;i<count;i++)
				parsed.push_back(parse(str, pos));
		}
		if(!parsed.empty() && parsed.back() == -1)
			parsed.pop_back();
		switch(stoll(opc, 0, 2)){
			case 0:
				return accumulate(begin(parsed), end(parsed), 0ll);
			case 1:
				return accumulate(begin(parsed), end(parsed), 1ll, multiplies<long long>());
			case 2:
				return *min_element(begin(parsed), end(parsed));
			case 3:
				return *max_element(begin(parsed), end(parsed));
			case 5:
				return parsed[0]>parsed[1];
			case 6:
				return parsed[0]<parsed[1];
			case 7:
				return parsed[0]==parsed[1];
		}
	}
	return -1;
}

chrono::time_point<std::chrono::steady_clock> day16(input_t& inp){
	map<char, string> m = {
		{'0', "0000"},
		{'1', "0001"},
		{'2', "0010"},
		{'3', "0011"},
		{'4', "0100"},
		{'5', "0101"},
		{'6', "0110"},
		{'7', "0111"},
		{'8', "1000"},
		{'9', "1001"},
		{'A', "1010"},
		{'B', "1011"},
		{'C', "1100"},
		{'D', "1101"},
		{'E', "1110"},
		{'F', "1111"},
	};
	string bin = "";
	for(char c: inp[0]){
		bin+=m[c];
	}
	long long pos = 0;
	long long p2 = parse(bin, pos);
	auto done = chrono::steady_clock::now();
	cout<<"[P1] "<<p1<<"\n[P2] "<<p2<<endl;
	return done;
}