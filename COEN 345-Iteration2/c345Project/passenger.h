/// This is where we store the passenger information such as passport number, passenger name etc. 
/* 
 * File:   passenger.h
 * Author: gaurav
 *
 * Created on November 15, 2009, 12:50 PM
 */

#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>


using namespace std;


class passenger
{
private:
	string passportNum;
	string name;
	string address;
	int telephone;
public:
	passenger() {};
	passenger(string passportNum,string name,string address,int telephone)
	{
		this->passportNum = passportNum;
		this->name = name;
		this->address = address;
		this->telephone = telephone;
	}

	void setName(string name)
	{
		//if(nm.size()<50) // can be tested in the gui
		this->name = name;
		
	}
	void setPassportNum(string passportNum){this->passportNum = passportNum;}
	void setAddress(string address){this->address = address;}
	void setTelephone(int telephone){this->telephone = telephone;}

	string getName(){return this->name;}
	string getPassportNum(){return this->passportNum;}
	string getAddress(){return this->address;}
	int getTelephone(){return this->telephone;}
	
};


#endif	