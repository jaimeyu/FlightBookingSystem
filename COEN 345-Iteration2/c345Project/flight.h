/// This is where we store the flight information such as airline and flight number. 
/* 
 * File:   flight.h
 * Author: jaime
 *
 * Created on September 30, 2009, 11:50 PM
 */

#ifndef _FLIGHT_H
#define	_FLIGHT_H

#include <string>
using namespace std;
class flight {

private:

    int flightNumber;
    string airline;
	string depAirport;
	string arrivalAirport;    
	string arrivalCity;
	string depCity;
	bool crash;

/*
    int scheduleHour;
    int scheduleMin;
    int scheduleDay;*/
public:

    flight() {
		flightNumber = -1; 
		airline ="none";}

    //method
    int setAirline(string airline) {
		this->airline = airline;
		return 1;
	}    
    string getAirline() {return this->airline;}
    int getFlightNumber() {return this->flightNumber;}
    bool setFlightNumber(int number) {
/*
        if (number>0){
            this->flightNumber = number;
            return true;
        }
        else{
            this->flightNumber = -1;
            return false;
        }*/
		this->flightNumber = number;
		return true;
    }

	int setDepCity(string depCity) {
		this->depCity = depCity;
		return true;
	}
	int setArrivalCity(string arrivalCity) {
		this->arrivalCity = arrivalCity;
		return true;
	}

	string getArrivalCity() { return this->arrivalCity;}
	string getDepCity() { return this->depCity;}
/*
    bool setSchedule(int day, int hour, int min) {
        if (day <0 || day >6)
            return false;
        else if (hour >24 || hour < 0)
            return false;
        else if (min <0 || min >60)
            return false;
        else {
            scheduleDay = day;
            scheduleHour = hour;
            scheduleMin = min;
            return true;
        }
    }
*/
	
	void setDepAirport(string airport) {this->depAirport = airport;} 
	void setArrivalAirport(string airport) {this->arrivalAirport = airport;}
	string getDepAirport() {return this->depAirport;}
	string getArrivalAirport(){return this->arrivalAirport;}
	void setCrash(bool crash){this->crash = crash;}
	bool getCrash(){return this->crash;}



};
#endif	/* _FLIGHT_H */

