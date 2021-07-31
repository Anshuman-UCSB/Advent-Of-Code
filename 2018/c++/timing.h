#pragma once

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Timer{
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime, stopTime;
<<<<<<< HEAD
	double totalTime;
	Timer(){
		totalTime = 0;
		start();
	}
=======
	double totalTime = 0;
>>>>>>> 9b5cc1ba6d3640016b215cfd288c2393f829fce7
	void start(){
		startTime = high_resolution_clock::now();
	}
	void end(bool print = true){
		stopTime = high_resolution_clock::now();
		duration<double, milli> dur = stopTime - startTime;
		if(print){
			if(dur.count()<1){
				cout<<"[Timer] Took "<<dur.count()*1000<<" μs."<<endl;
<<<<<<< HEAD
			}else if(dur.count()>1000){
				cout<<"[Timer] Took "<<dur.count()/1000<<" s."<<endl;
=======
>>>>>>> 9b5cc1ba6d3640016b215cfd288c2393f829fce7
			}else{
				cout<<"[Timer] Took "<<dur.count()<<" ms."<<endl;
			}
		}
		totalTime+=dur.count();
	}
	void total(){
		if(totalTime<1){
			cout<<"[Timer] Total recorded time "<<totalTime*1000<<" μs."<<endl;
		}else{
			cout<<"[Timer] Total recorded time "<<totalTime<<" ms."<<endl;
		}
	}
};