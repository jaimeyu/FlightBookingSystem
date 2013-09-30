#ifndef FLIGHTMANIFEST_H
#define	FLIGHTMANIFEST_H

#include "passenger.h"
#include "bookingInfo.h"
#include <vector>


class flightManifest
{
private:
	vector<bookingInfo> bookings;
	bool full;

	int date;
	int month;
	int year;


public:

	flightManifest(){};

	int getDate(){return this->date;}
	int getMonth() {return this->month;}
	int getYear() {return this->year;}
	
	void setDMY(int date, int month, int year){
		this->date = date;
		this->month = month;
		this->year = year;
	}





	void pushBooking(bookingInfo book){
		bookings.push_back(book);
	}
	vector<bookingInfo> getBooking(){
		return bookings;
	}

	bool isSeatRowLetterAvailable(int row, string letter)
	{
	bool available = true;

		for (int i=0; i<bookings.size();i++){
			if ((bookings.at(i).getSeatRow() == row )&& (bookings.at(i).getSeatLetter() == letter)) //check if letter is available
				available = false;
		}
      return available;

	}

	bool isFull(){
		int size = 1;

		for (int row = 0; row <19; row++){
			{
				if (!isSeatRowLetterAvailable(row,"a"))//is true
					size++;
				if (!isSeatRowLetterAvailable(row,"b"))
					size++;
				if (!isSeatRowLetterAvailable(row,"c"))
					size++;
				if (!isSeatRowLetterAvailable(row,"d"))
					size++;
			}
	}
		if (size >=(20*4)) //if  80+ people on place, then its a full plane
			return true;
		else
			return false;
	}

	

};
#endif