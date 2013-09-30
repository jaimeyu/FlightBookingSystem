/// This is where we store the booking information such as flight number, passenger seat etc. 
/* 
 * File:   booking.h
 * Author: gaurav
 *
 * Created on November 15, 2009, 03:50 PM
 */
#ifndef _BOOKINGINFO_H
#define	_BOOKINGINFO_H

#include "passenger.h"

class bookingInfo
{
private:
	//flight flightBooked;
	passenger passengerBooked;
	int seatRow;
	string seatLetter;
	/*int date;
	int month;
	int year;*/


public:
	bookingInfo(){};
	bookingInfo(passenger passengerB, int seatRow, char seatLetter)
	{
		this->passengerBooked = passengerB;
		this->seatRow = seatRow;
		this->seatLetter = seatLetter;
	}
	void setPassenger(passenger passengerBooked){
		this->passengerBooked = passengerBooked;
	}
	void setSeatRow(int seatRow){
		this->seatRow = seatRow;
	}
	void setSeatLetter(string seatLetter){
		this->seatLetter = seatLetter;
	}
/*	void setDMY(int date, int month, int year){
		this->date = date;
		this->month = month;
		this->year = year;
	}



*/
	passenger getPassenger(){return this->passengerBooked;}
	int getSeatRow() {return this->seatRow;}
	string getSeatLetter() {return this->seatLetter;}
	
	/*
	int getDate(){return this->date;}
	int getMonth() {return this->month;}
	int getYear() {return this->year;}
	*/


};
#endif	