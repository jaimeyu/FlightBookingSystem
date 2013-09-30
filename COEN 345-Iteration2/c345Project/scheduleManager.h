///the schedule manager is used to find todays flight. It will also be used to check on flight status once its implemented. 
#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include "flight.h"
#include "schedule.h"
#include <vector>
#include <stack>
#include <time.h>
#include <iostream>
#include <string>
#include "day.h"
using namespace std;

class scheduleManager{

private:

	vector<schedule> schedList; //this holds the master schedule
	vector<schedule> inFlightList; //this holds the list of flights currently in the air
	int countList;	///not used.
	int countFlying; ///not used.

public:

	scheduleManager(){
	countList = 0;
	countFlying = 0;
	}

	scheduleManager(vector<schedule> schedList){
	countList = 0;
	countFlying = 0;
	this->schedList = schedList;
	}


//push a schedule into the vector

	//insert the entire flight list into this class for processing
	int push(vector<schedule> schedList){ 

		this->schedList = schedList;

		//schedList

		return 0;
	}


	int push(vector<schedule> schedList, vector<schedule> inFlightList){ 

		this->schedList = schedList;
		this->inFlightList = inFlightList;
		//schedList

		return 0;
	}

	
	//the following should be made into their own class file. everyone should have access to these functions. 
	int getDay(struct tm * timeinfo){
		char day [80];
		string conv;
		int today;
		//int data;
		strftime (day,80,"%a",timeinfo);
		conv = day;

		if (conv == "Sun")
			today = 6;
		else if (conv == "Sat")
			today = 5;
		else if (conv == "Fri")
			today = 4;
		else if (conv == "Thu")
			today = 3;
		else if (conv == "Wed")
			today = 2;
		else if (conv == "Tue")
			today = 1;
		else if (conv == "Mon")
			today = 0;
		else
			today = -1;

		
		return today;

	}
	int getDate(struct tm * timeinfo){
		char date [3];
		string conv;
		int output;

		strftime (date,3,"%d",timeinfo);
		conv = date;
		output = atoi(conv.c_str());

		return output;
	}

	int getHour(struct tm * timeinfo){
		char hour [3];
		string conv;
		int output;

		strftime (hour,3,"%H",timeinfo);
		conv = hour;
		output = atoi(conv.c_str());

		return output;

	}

	int getMin(struct tm * timeinfo){
		char min [3];
		string conv;
		int output;

		strftime (min,3,"%M",timeinfo);
		conv = min;
		output = atoi(conv.c_str());

		return output;

	}
	
	int getMonth(struct tm * timeinfo){
		char month [4];
		string conv;
		int output;

		strftime (month,4,"%m",timeinfo);
		conv = month;
		output = atoi(conv.c_str());

		return output;

	}

	int getYear(struct tm * timeinfo){
		char year [5];
		string conv;
		int output;

		strftime (year,5,"%Y",timeinfo);
		conv = year;
		output = atoi(conv.c_str());

		return output;

	}

	
	//GETS current clock thats processable by the time.h fns
	struct tm* getSysClock(){ 
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime ); //THROWS A WARNING IN VS2008
		return timeinfo;
	}

	//returns the flight list of current flights in the sky
	vector<schedule> getFlyingTodayList(){

		inFlightList.clear();
		
/*test code
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime ); //THROWS A WARNING IN VS2008

		cout <<"TODAY IS " << getDay(timeinfo) <<endl;
		cout <<"Date IS " << getDate(timeinfo) <<endl;
		cout <<"Hour IS " << getHour(timeinfo) <<endl;
		cout <<"Min IS " << getMin(timeinfo) <<endl;
		cout <<"Month IS " << getMonth(timeinfo) <<endl;
		cout <<"Year IS " << getYear(timeinfo) <<endl;
*/
		
		struct tm * timeinfo = getSysClock();
		for (int i =0; i < (int)this->schedList.size(); i++){
			if ( (getDay(timeinfo) == 6)&& ( this->schedList.at(i).getDay().sunday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 5)&& ( this->schedList.at(i).getDay().saturday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 4)&& ( this->schedList.at(i).getDay().friday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 3)&& ( this->schedList.at(i).getDay().thursday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 2)&& ( this->schedList.at(i).getDay().wednesday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 1)&& ( this->schedList.at(i).getDay().tuesday == true))
				inFlightList.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 0)&& ( this->schedList.at(i).getDay().monday == true))
				inFlightList.push_back(schedList.at(i));
		}




		//cout << getDay(timeinfo);

		return this->inFlightList;

	}
/*
	vector<schedule> getCurrentlyFlyingList(){
		vector<schedule> output;
		vector<schedule> temp;
		
		int endTime;
		int curTime;

		struct tm * timeinfo = getSysClock();
		for (int i =0; i < (int)this->schedList.size(); i++){
			if ( (getDay(timeinfo) == 6)&& ( this->schedList.at(i).getDay().sunday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 5)&& ( this->schedList.at(i).getDay().saturday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 4)&& ( this->schedList.at(i).getDay().friday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 3)&& ( this->schedList.at(i).getDay().thursday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 2)&& ( this->schedList.at(i).getDay().wednesday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 1)&& ( this->schedList.at(i).getDay().tuesday == true))
				temp.push_back(schedList.at(i));
			else if ( (getDay(timeinfo) == 0)&& ( this->schedList.at(i).getDay().monday == true))
				temp.push_back(schedList.at(i));
		}

		curTime = (getHour(timeinfo)*60 ) + getMin(timeinfo);

		int erase =0;
		stack<int> eraseList;

		for (int i =((int)temp.size())-1; i >=0 ; i++){
			endTime = temp.at(i).getdepMin() + temp.at(i).getFlightLength() + (temp.at(i).getdepHour()*60);

			cout << curTime <<endl;
			cout << endTime <<endl;

			

			if (curTime > endTime){
				eraseList.push(i);
				erase++;

			}
				
		}

		for (int j=0; j <erase;j++){
			temp.erase(temp.begin()+eraseList.top());
			eraseList.pop();

		}
		output = temp;

		
		return output;

	}*/

};

#endif