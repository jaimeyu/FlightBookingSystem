///This is the schedule object. this is where you store the arrival and departure times. 
/* 
 * File:   schedule.h
 * Author: jaime
 *
 * Created on October 1, 2009, 12:00 AM
 */

#ifndef _SCHEDULE_H
#define	_SCHEDULE_H

#include "day.h"
#include "flight.h"
#include "flightManifest.h"

class schedule { 

private:

	int scheduleNumber;	//a key
	int depDate;			//depDate
	int depMonth;			//depMonth
    day days;			//monday-sunday boolean container
    int depHour;			//14:
    int depMin;			//32
	int depYear;
	int flightLength;
	/*
	int arrDate;			//depDate
	int arrMonth;			//depMonth
    int arrHour;			//14:
    int arrMin;			//32
*/
	//extras
    bool repeat;		//repeat?
    int flightNumber;	//a key -- DO NOT USE ANYMORE. USE THE FLIGHT NUMBER IN THE FLIGHT OBJECT
	int bookingNumber;	//a key

	//delays cancellation etc
	int delay;	//in 
	bool cancelled;
	string reason;

	//flight object -- better than using the flight numbers above
	flight flightInfo;
	//booking bookingInfo

	vector<flightManifest> bookingDB;
	flightManifest bookDB;
	vector<bookingInfo> book;
	bool full;



public:

    schedule() {};
    schedule(day days, int depHour, int depMin, int flightNumber, bool repeat) {
        this->days = days;
        this->depHour = depHour;
        this->depMin = depMin;
        this->repeat = repeat;
        this->flightNumber = flightNumber;
    }
	schedule(day days, int depHour, int depMin, int flightNumber, int depDate, int depMonth) {
        this->days = days;
        this->depHour = depHour;
        this->depMin = depMin;
        this->depDate = depDate;
        this->flightNumber = flightNumber;
    }

	int getdepDate() {return this->depDate;}
	int getdepYear() {return this->depYear;}
	int getdepMonth() {return this->depMonth;}
    day getDay() {return this->days;}
    int getdepHour() { return this->depHour;}
    int getdepMin() { return this->depMin;}
    bool getRepeat() {return this->repeat;}
    //int getFlightNumber(){return this->flightNumber;} //DO NOT USE THIS- USE flight object
	void setdepDate(int depDate) {this->depDate = depDate;}
	void setdepMonth(int depMonth) {this->depMonth = depMonth;}
	void setDay(day days) {this->days = days;}
	void setdepHour(int depHour) {this->depHour = depHour;}
	void setdepMin(int depMin) {this->depMin = depMin;}
	void setdepYear(int depYear) {this->depYear = depYear;}
	void setRepeat(bool repeat) {this->repeat = repeat;}
	void setFlightNumber(int flightNumber){this->flightNumber = flightNumber;}
	
	bool getCancelled(){return this->cancelled;}
	string getReason(){return this->reason;}
	void setCancelled(bool cancelled){this->cancelled = cancelled;}
	void setReason(string reason) {this->reason = reason;}
	void setPlaneFull(bool full) {this->full = full;}
	bool isPlanFull(){
	
		if (book.size() == 80)
			full = true;
		else 
			full = false;
		
		return this->full;
	}

	
	

	int setFlight(flight temp){
	
		this->flightInfo = temp;

		return 0;
	}

	flight getFlight(){
		return this->flightInfo;
	}


	void setFlightLength(int flightLength){
		this->flightLength = flightLength;
	}
	int getFlightLength(){
		return this->flightLength;
	}


	//yet to be done
	//int getBookingNumber() {}; ///this isn't implemented yet. 

	void setBookingDB(vector<flightManifest> booking){this->bookingDB = booking;}
	vector<flightManifest> getBookingDB(){return this->bookingDB;}

	flightManifest getBookDB(){return this->bookDB;}


	vector<bookingInfo> getBook(){return this->book;}
	void setBook( vector<bookingInfo> book) { this->book = book;}
};

#endif	/* _SCHEDULE_H */

