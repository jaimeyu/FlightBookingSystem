/**\brief The GUI Class
This contains the code for the GUI. 
This is the object the user will interact with.
**/
/* 
* File:   gui.h
* Author: Joseph Khater
*
* Created on October 3rd, 2009, 11:59 PM
*/
/// Global variables
// yes, globals are no nos but this is for the old school dos code - we added it last minute, no time to refactor it. 
int menucol = 6;
int questcol = 3;
int inputcol = 4;
int replycol = 5;

#ifndef GUI_H
#define GUI_H
#include <string>	///used for data entry
#include <ctype.h>	///Using this to check types. There, happy sir?
#include <iomanip>	///setw() - for screen writing - ie: truncate decimals etc
#include <conio.h>	///conio.h is a header file used in old MS-DOS compilers to create text user interfaces. OLD SCHOOL BABY!
#include "flight.h"	///the flight object. refer to object diagram from documentation.
#include "schedule.h"	///schedule object
#include "scheduleManager.h"	///originally for making connecting flights. now used to find flights for today.
#include "day.h"	///simple object to store days such as mondays wed, etc
#include "fileops.h"	///this is our file reading/writing functions
#include "passenger.h"	///passenger object
#include "bookingInfo.h"	///booking object
#include "flightManifest.h"	///was originally designed to control bookings for each repeating flight. too many errors in it so it is no longer used
#include "utility.h"		///This is how we paint to the screen using short commands. 
#include "random.h"		///added ramdomly. JK. Its for the rand function for just 1 line of code. 
using namespace std;

class gui{	

	//// [JK] i have to stop pointing to my private members in this class. [/JK]


private:
	vector<int> flightNumbers; ////We're using this to quickly discover doubles instead of going through the entire flying list.

	///	vector<flight> flightList; ///
	vector<schedule> schedList;	////contains the master schedule list
	vector<schedule> flyingList;	////constains only today's flights


	/// Variables for menus and choices
	int choice, user, managermenu;	///safer to put this in the functions themselves!
	string  managerchoice, agentchoice;			

	scheduleManager manager;		////this is the scheduler to figure out today's flights. 

public:


	gui(){}	////constructor

	///validation functions
	bool doesFlightExistOn(int year, int month, int date, int flightNum){

		/*http:///5dspace-time.org/Calendar/Algorithm.html*/

		int yearincent=0; int centuryoff=0; int yearoff=0; int monthoff=0; int dayoff=0; int weekday=0;

		//// Century + Year + Month + Day = Weekday

		//// Century offset //// Not really needed unless user enters something other than the 21st century :S we know u want to!!
		///centuryoff = 7 - (((year%100) + 3) %7);
		centuryoff = ((39 - (year/100)) % 4 ) * 2;

		//// Year Offset
		//// leap year:
		//// is divisable by 4 and not by 100
		//// is divisable by 400
		if ( (year%4==0 && year%100!=0) || year%400==0 ) /// Leap Year
		{
			if (month==1 || month==2) /// Before Leap Day
				yearoff = ( ( (year%100)+(year%100)/4 ) %7 )-1;
			else 
				yearoff = ( (year%100)+(year%100)/4 ) %7;
		}
		else 
			yearoff = ( (year%100)+(year%100)/4 ) %7;

		//// Month Offset
		if ((month==1)||(month==10))
			monthoff = 0;
		if (month==5)
			monthoff = 1;
		else if (month==8)
			monthoff = 2;
		else if ((month==2)||(month==3)||(month==11))
			monthoff = 3;
		else if (month==6)
			monthoff = 4;
		else if ((month==9)||(month==12))
			monthoff = 5;
		else if ((month==4)||(month==7))
			monthoff = 6;	

		//// Date Offset
		dayoff = (date%7);

		//// Day is
		weekday = (centuryoff + yearoff + monthoff + dayoff)%7; //// day of the week 	//// 1=Monday ... 7=Sunday


		///cout << "day is: " << weekday << endl;  /// just for testing purposes jk
		///cout << " FLIGHT NUM: " << flightNum << endl; /// just for testing purposes jk


		//// check flightnum if exists
		string tempin = "a";
		bool fexists =false;
		schedule current;

		///does this flight number exist?
		for (int i = 0; i< flightNumbers.size(); i++){
			if (flightNumbers.at(i) == flightNum)
			{	
				fexists = true;
				current = schedList.at(i);
				cout << "Flight exists. Going to check if available on the same date!" <<endl;
			}
		}
		if (fexists == true){
			if (current.getRepeat() == true){
				///check date schedule if same as flight date
				if ((current.getDay().monday) && (weekday==1))
					return true; /// cout<< "MONDAY" << endl; /// good! book passenger function	

				if ((current.getDay().tuesday) && (weekday==2))
					return true; /// cout<< "TUESDAY" << endl; /// good! book passenger function	 

				if ((current.getDay().wednesday) && (weekday==3))
					return true; /// cout<< "WEDNESDAY" << endl;	/// good! book passenger function

				if ((current.getDay().thursday) && (weekday==4))
					return true; /// cout<< "THURSDAY" << endl;	/// good! book passenger function

				if ((current.getDay().friday) && (weekday==5))
					return true; /// cout<< "FRIDAY" << endl;	/// good! book passenger function	

				if ((current.getDay().saturday) && (weekday==6))
					return true; /// cout<< "SATURDAY" << endl;	/// good! book passenger function

				if ((current.getDay().sunday) && (weekday==7))
					return true; /// cout<< "SUNDAY " << endl;	/// good! book passenger function

				else	/// Flight not available on that day :'( try another booking on a different day
				{

					cout << "No Flight is scheduled on that day." <<endl; 
					return false;
				}
			}
			else
			{
				if (current.getdepYear() == year)
					if (current.getdepMonth() == month)
						if (current.getdepDate() == date)
							return true;
						else
							return false;
					else 
						return false;
				else
					return false;
			}
		}
		else {
			cout << "Flight doesn't exist." <<endl; /// Flight is not scheduled and does not exist yet
			return false;
		}
	}
	bool checkDuplicate(int number){////Check duplicate flight numbers
		int error = 0;
		if (flightNumbers.empty() == false) {
			for (int i=0; i <(int) flightNumbers.size();i++){
				///cout << flightNumbers.at(i);
				if (flightNumbers.at(i) == number)
				{
					///cout << flightNumbers.at(i) <<endl;
					///cout << number <<endl;
					error++;
				}
			}
		}
		if (error == 1){
			///cout << " !!!!!!!dup " <<endl;
			return false;
		}
		else
		{
			///cout << "!!!!! WOrk" <<endl;
			return true;
		}
	}

	bool checkFlightNumber(int number) { ////checks flight number to make sure its valid (4digits & !existed)
		if ( (number >999) && (number <10000) && (checkDuplicate(number)) ) ///check if flight number is 4 digits. 
			return true;
		else 
			return false;
	}

	bool checkDay(int day) {	////checks if the day entered is a valid day of the week
		///DOES NOT CHECK IF ITS A 28-29-30 day month! - someone should implement it
		if ( (day>0) && (day<8))
			return true;
		else
			return false;
	}

	bool checkHour(int hour) {
		if ( (hour >=0) && (hour <24))
			return true;
		else
			return false;
	}

	bool checkMin(int min) {
		if ( (min >=0) && (min <60) )
			return true;
		else 
			return false;
	}

	bool checkDate(int date){ ////simple check - is obsolete, please replace with the newer and more stronger version below
		if ((date >0) && (date <32))
			return true;
		else
			return false;
	}
	bool checkDate(int date, int month, int year){
		int daysOfMonth = 31;
		switch (month){
			case 1:case 3:case 5: case 7: case 8:case 10: case 12:
				daysOfMonth = 31;
				break;
			case 4:case 6:case 9:case 11:
				daysOfMonth = 30;
				break;
			case 2:
				if  ( ( (year%4) == 0 ) || ( (year%400) == 0) || ( (year%100) !=0)) ///leap year code
					daysOfMonth = 29;
				else
					daysOfMonth = 28;
				break;
			default:
				daysOfMonth = 31;
		}

		if ((date >0) && (date <= daysOfMonth))
			return true;
		else
			return false;
	}

	bool checkMonth(int month) {
		if ( (month >0) && (month <13) )
			return true;
		else
			return false;
	}

	bool checkYear(int year){ //// does not allow for negative years! we can but lets not introduce random errors. 
		if (year >0)
			return true;
		else
			return false;
	}
	bool isInputDigit(string temp){ ////checks if the string is an integer
		bool isNumber = true;
		for (int i =0; i < (int)temp.size() ; i++){
			if ( !isdigit(temp[i]) )
				isNumber = false;
		}
		return isNumber;
	}
	/* end error checking code*/
	///----------------------------------------------------------------------------------------------------------------------------------------------
	void cancelFlight(){
		string tempin = "a";
		bool fexists =false;

		setrgb(questcol);
		cout << "Flight Cancellation" <<endl;

		do {
			setrgb(questcol);
			cout << "What is the flight number you want to cancel?" <<endl;
			setrgb(inputcol);
			getline(cin, tempin);

		}while ( isInputDigit(tempin.c_str() ) == false );

		int flightNumCancel = atoi(tempin.c_str() );
		///does this flight number exist?

		for (int i = 0; i< flightNumbers.size(); i++){
			if (flightNumbers.at(i) == flightNumCancel)
			{	
				flightNumbers.erase( flightNumbers.begin()+i);
				fexists = true;
				setrgb(replycol);
				cout << "Flight exists. Going to delete it from memory!" <<endl;
			}
		}


		if (fexists == true){
			///delete schedule
			for (int i =0; i < schedList.size(); i++){
				if (schedList.at(i).getFlight().getFlightNumber() == flightNumCancel)
					schedList.erase( schedList.begin()+i );
			}
			setrgb(replycol);
			cout << "Flight and its schedule have been deleted from memory!" <<endl;
		}
		else
		{
			setrgb(replycol);
			cout << "Flight doesn't exist." <<endl;
		}
		OperationManagers();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///update flight status
	///!!needs to be error checked
	void boardingPass()
	{
		int err = 0; ///error codes
		string temp;
		int i=0, y=0;
		int fnumber;
		string pnum;
		setrgb(questcol);
		cout << "Enter Flight Number: " ;
		setrgb(inputcol);
		err = 0;

		do{
			err = 0;
			getline( cin, temp);

			if (isInputDigit(temp.c_str()))
				fnumber = atoi(temp.c_str());
			else{
				err = 1;
				setrgb(replycol);
				cout << "Not a number" <<endl;
			}
		}while (err==1);

		int foundi =-1;
		for (i=0; i< (int)schedList.size();i++){
			if (schedList.at(i).getFlight().getFlightNumber() == fnumber)
				foundi = i;

		}
		/*	///fnumber = atoi(temp.c_str());

		///for (i=0; i < schedList.size();i++)
		///{
		for (y=0;y<schedList.at(foundi).getBook().size();y++)
		{
		if (schedList.at(foundi).getBook().at(y).getPassenger().getName() == temp){
		///flights.push_back(schedList.at(i);
		cout << "Flight Number: " << schedList.at(foundi).getFlight().getFlightNumber() << endl;
		cout <<	"Seat : " << schedList.at(foundi).getBook().at(y).getSeatRow() << schedList.at(foundi).getBook().at(y).getSeatLetter() <<endl<<endl;
		}
		}
		///}

		*/
		setrgb(questcol);
		cout << "Enter Passport Number: " ;
		setrgb(inputcol);
		getline(cin, pnum);

		clrscr();

		if (foundi != -1){
		for (i=0; i < schedList.size();i++)
		{
			for (int y=0;y<schedList.at(i).getBook().size();y++)
			{
				if (schedList.at(i).getBook().at(y).getPassenger().getPassportNum() == pnum){

					setrgb(2);			
					gotoxy(45,8);
					cout<<schedList.at(i).getBook().at(y).getSeatRow() << schedList.at(i).getBook().at(y).getSeatLetter()<<endl; /// seat #

					gotoxy(45,10);
					if ((schedList.at(i).getBook().at(y).getSeatRow()<6) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"First - Window"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<11) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"Business - Window"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<21) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"Economy - Window"<<endl; 

					if ((schedList.at(i).getBook().at(y).getSeatRow()<6) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"First - Aisle"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<11) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"Business - Aisle"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<21) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"Economy - Aisle"<<endl;




					setrgb(3);
					gotoxy(62,10);
					if ((schedList.at(i).getBook().at(y).getSeatRow()<6) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"First - Window"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<11) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"Business - Window"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<21) && (schedList.at(i).getBook().at(y).getSeatLetter()=="a") || (schedList.at(i).getBook().at(y).getSeatLetter()=="d"))
						cout<<"Economy - Window"<<endl; 

					if ((schedList.at(i).getBook().at(y).getSeatRow()<6) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"First - Aisle"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<11) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"Business - Aisle"<<endl; 

					else if ((schedList.at(i).getBook().at(y).getSeatRow()<21) && (schedList.at(i).getBook().at(y).getSeatLetter()=="b") || (schedList.at(i).getBook().at(y).getSeatLetter()=="c"))
						cout<<"Economy - Aisle"<<endl;


					///SEATS


					gotoxy(69,16);
					cout<<" "<<schedList.at(i).getBook().at(y).getSeatRow() << schedList.at(i).getBook().at(y).getSeatLetter()<<endl; /// seat #


			setrgb(4);
			gotoxy(23,26);
			cout<<"SEATS ECON BNESS FIRST #"<<endl;
			setrgb(5);
			gotoxy(23,28);
			cout<<"OOOOOOOOOO OOOOO OOOOO A"<<endl;
			gotoxy(23,29);
			cout<<"OOOOOOOOOO OOOOO OOOOO B"<<endl;
			gotoxy(23,31);
			cout<<"OOOOOOOOOO OOOOO OOOOO C"<<endl;
			gotoxy(23,32);
			cout<<"OOOOOOOOOO OOOOO OOOOO D"<<endl;
			setrgb(4);
			gotoxy(23,34);
			cout<<"2111111111 19876 54321 #"<<endl;
			gotoxy(23,35);
			cout<<"0987654321 0            "<<endl;

					int gotoy;
					if(schedList.at(i).getBook().at(y).getSeatLetter()=="a")
						gotoy=28;
					else if(schedList.at(i).getBook().at(y).getSeatLetter()=="b")
						gotoy=29;
					else if(schedList.at(i).getBook().at(y).getSeatLetter()=="c")
						gotoy=31;
					else if(schedList.at(i).getBook().at(y).getSeatLetter()=="d")
						gotoy=32;

					int gotox;
					if(schedList.at(i).getBook().at(y).getSeatRow()<6)
						gotox=2;
					else if(schedList.at(i).getBook().at(y).getSeatRow()<11)
						gotox=1;
					else if(schedList.at(i).getBook().at(y).getSeatRow()<21)
						gotox=0;


					setrgb(2);
					gotoxy(23+(20-schedList.at(i).getBook().at(y).getSeatRow())+gotox,gotoy);
					cout<<"X"<<endl;
					
					setrgb(3);
					gotoxy(62,7);
					cout<<schedList.at(i).getBook().at(y).getPassenger().getName()<<endl; /// passenger name number

					setrgb(2);
					gotoxy(45,6);
					cout<<schedList.at(i).getBook().at(y).getPassenger().getName()<<endl; /// passenger name number currentPassenger.getName()


			
		

				}
			}
		}


		int x=0; /// changing colors

		schedule current;
		current = schedList.at(foundi);


		passenger currentPassenger;
		bookingInfo currentPassengerBooking;

		flight flightinfo;
		schedule sched;

		int gate=rand();
		do{


			gotoxy(0,0);
			setrgb(6);
			cout<<"  ***************************************************************************"<<endl;
			cout<<" *                                                                           *"<<endl;
			for(int a=2; a<22; a++)
			{
				cout<<"*"<<endl;gotoxy(78,a);cout<<"*"<<endl;
			}
			for(int b=1; b<22; b++)
			{
				gotoxy(60,b);cout<<"|"<<endl;
			}
			cout<<" *                                                          |                *"<<endl;
			cout<<"  ***************************************************************************"<<endl;


			setrgb(9);
			gotoxy(20,2);
			cout<<"CARTE D'EMBARQUEMENT - BOARDING PASS"<<endl;

			setrgb(3);
			gotoxy(20,17);
			cout<<"CABINE NON FUMEUR - NON SMOKING CABIN"<<endl;

			setrgb(1);
			gotoxy(20,20);
			cout<<"EMBARQUEMENT MAINTENANT - NOW BOARDING"<<endl;
			Sleep(500);
			setrgb(9);
			gotoxy(20,20);
			cout<<"EMBARQUEMENT MAINTENANT - NOW BOARDING"<<endl;

			setrgb(12);
			gotoxy(5,5);
			cout<<" VOL - FLIGHT"<<endl;

			gotoxy(5,7);
			cout<<" DATE - DATE"<<endl;

			gotoxy(5,9);
			cout<<" DEPART - TIME"<<endl;

			gotoxy(5,11);
			cout<<" DE - FROM"<<endl;

			gotoxy(5,13);
			cout<<" A - TO"<<endl;

			setrgb(5);
			gotoxy(20,5);
			cout<<current.getFlight().getFlightNumber()<<endl; /// flight number

			gotoxy(20,7);
			///cout<<current.getdepDate()<<endl; /// display departure date
			if (current.getdepDate() == -1)
				cout << "Repeating" <<endl;
			else
				cout << current.getdepDate() <<endl;

			gotoxy(20,9);
			cout<<current.getdepHour() <<":"<<current.getdepMin()<<endl; /// display departure time

			gotoxy(20,11);
			cout<<current.getFlight().getDepCity()<<endl; /// display departure city

			gotoxy(20,13);
			cout<<current.getFlight().getArrivalCity()<<endl; /// diaplay arrival city

			setrgb(12);
			gotoxy(31,6);
			cout<<" TRAVELLER"<<endl; 

			gotoxy(31,8);
			cout<<" SEAT #"<<endl;

			gotoxy(31,10);
			cout<<" CLASSE-CLASS"<<endl; 

			gotoxy(31,12);
			cout<<" GATE #"<<endl;
			
			gotoxy(45,12);
			cout<<get_rand(1,99)<<endl; /// gate number

			setrgb(12);
			gotoxy(61,6);
			cout<<" TRAVELLER"<<endl; 

			gotoxy(61,9);
			cout<<" CLASSE-CLASS"<<endl; 		

			gotoxy(61,12);
			cout<<" SEAT #"<<endl;






			setrgb(x);
			gotoxy(68,14);
			cout<<"#######"<<endl;
			gotoxy(68,15);
			cout<<"#"<<endl;
			gotoxy(68,16);
			cout<<"#"<<endl;
			gotoxy(68,17);
			cout<<"#"<<endl;

			gotoxy(68,18);
			cout<<"#######"<<endl;
			gotoxy(74,15);
			cout<<"#"<<endl;
			gotoxy(74,16);
			cout<<"#"<<endl;
			gotoxy(74,17);
			cout<<"#"<<endl;
			gotoxy(0,23);

			Sleep(1000);
			x++;
			if (x==7)
				x=0;
			///clrscr();
		}while (!kbhit());
		clrscr();
		setrgb(0 );
		}
		///AirlineAgents();
	}


	///----------------------------------------------------------------------------------------------------------------------------------------------
	///create passenger,enter personal info, and book on a flight
	void optionPI() ////User uses this function to enter passenger personal information and book him/her on a flight.
	{


		string input;
		bool isProperPassport = false;
		bool isProperTelephone = false;
		bool isProperName = false;
		bool isProperFlightNumber = false;
		bool isProperAdd = false;
		bool isProperDate = false;
		bool isProperRow = false;
		bool isProperLetter = false;
		bool isProperSeat = false;
		string test;
		int temp;
		int foundi =-1;
		int date,month, year;
		int fnum;
		int row;
		string letter;
		bool flightExist= false;
		passenger currentPassenger;
		bookingInfo currentPassengerBooking;
		flightManifest current;
		int foundExistingBooking =-1;
		vector<bookingInfo> tempBookList;


		if (flightNumbers.empty() == true)
		{
			setrgb(replycol);
			cout << "ERROR! No flights exist! We cannot book anyone at the moment." << endl;
		}
		else{
			setrgb(questcol);
			cout << "	Book a Passenger on a Flight:" << endl;


			do ///get passport number
			{
				setrgb(questcol);
				cout << "	What is the passenger's passport info?" <<endl;
				cout <<"	Passport #: ";
				setrgb(inputcol);
				getline(cin, input);

				if (input.size() == 11) ///1 char + 10 numbers
				{
					test = input.at(0);
					if ( isInputDigit(test) == false)
						isProperPassport = true;
					else{
						setrgb(replycol);
						cout << "ERROR! First alphanumeric character is not an alphabet character!" <<endl;
					}
				}
				else
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect passport format. 1 letter then 10 digits please." <<endl;
				}
			}while ( !isProperPassport);

			currentPassenger.setPassportNum(input);


			do ///passenger name
			{

				setrgb(questcol);
				cout << "	What is the passenger's Full Name?" <<endl;
				cout << "	Name: ";
				setrgb(inputcol);
				getline(cin, input);
				if(input.size()<50)
				{
					if ( isInputDigit(input) == false)
						isProperName = true;
					else{
						setrgb(replycol);
						cout << "ERROR! Name should be characters and not numbers!" <<endl;
					}
				}
				else
					cout << "ERROR! Incorrect name format. Name should be less than 50 characters." <<endl;
			}while ( !isProperName);
			currentPassenger.setName(input);

			do ///passenger address
			{
				setrgb(questcol);
				cout << "	What is the passenger's address?" <<endl;
				cout << "	Address: ";
				setrgb(inputcol);
				getline(cin, input);
				if(input.empty()){
					setrgb(replycol);
					cout << "ERROR! Empty string" <<endl;
					isProperAdd = false;
				}
				else
					isProperAdd = true;
			}while ( !isProperAdd);
			currentPassenger.setAddress(input);


			do ///passenger's telephone
			{
				setrgb(questcol);
				cout << "	What is the passenger's telephone?" <<endl;
				cout <<"	Telephone # (5141234567): ";
				setrgb(inputcol);
				getline(cin, input);

				if (input.size() == 10) ///1 char + 10 numbers
				{
					if ( isInputDigit(input) == true)
						isProperTelephone = true;
					else{
						setrgb(replycol);
						cout << "ERROR! Not a valid entry."<<endl;
					}
				}
				else
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect telephone format. 10 digits please." <<endl;
				}

			}while ( !isProperTelephone);


			temp = atoi(input.c_str());

			currentPassenger.setTelephone(temp);

			///cout << "Sucess!" <<endl;

			/// entering flight number..........i think we need the flight num as well....coz there can be multiple fligths on the same date

			showAllFlights();
			do{
				setrgb(questcol);
				cout << "	Enter the Flight # the passenger wants to travel with: ";
				setrgb(inputcol);
				getline(cin,input);
				if ( isInputDigit(input) )
				{
					fnum = atoi(input.c_str());
					///if (checkFlightNumber(fnum))
					///{

					///compare the entered flight number with the existing ones.....



					for (int i=0; i< (int)schedList.size();i++)
					{
						if (schedList.at(i).getFlight().getFlightNumber() == fnum)
							foundi = i;
					}

					if(foundi!=-1)
						isProperFlightNumber = true;
					///}


				}
				else{
					isProperFlightNumber = false;
				}

				if (isProperFlightNumber == false)
				{
					setrgb(replycol);
					cout << "	Flight does not exist. Try again." << endl ;
				}

				if (schedList.at(foundi).isPlanFull()){
					setrgb(replycol);
					cout << "Plane full!!. Please select another flight." <<endl;
					isProperFlightNumber = false;
				}
				else
					isProperFlightNumber = true;




			}while (!isProperFlightNumber);



			do{///keep entering date till we find that the flight exists on that date
				/// enter the year that the passenger wants to travel on
				do{
					setrgb(questcol);
					cout << "What is the year that the passenger wants to travel? ";
					setrgb(inputcol);
					getline( cin, input);
					///cin >> temp;cin >>temp;
					if ( isInputDigit(input) ){
						year = (int) atoi(input.c_str());
						if (checkYear(year)){						
							isProperDate=true;
						}

					}
					else
						isProperDate = false;

					if (isProperDate == false)
					{
						setrgb(replycol);
						cout << "ERROR! Incorrect input" <<endl;
					}

				}while(!isProperDate);
				/// enter the month that the passenger wants to travel on
				do{
					setrgb(questcol);
					cout << "What is the month that the passenger wants to travel? ";
					setrgb(inputcol);
					getline( cin, input);
					///cin >> temp;cin >>temp;
					if ( isInputDigit(input) ){
						month = (int) atoi(input.c_str());
						cout << " " <<month <<endl;
						if (month <13)		
							if ( month >0)
								isProperDate=true;
							else
								isProperDate=false;
						else
							isProperDate=false;

					}
					else
						isProperDate = false;

					if (isProperDate == false)
					{
						setrgb(replycol);
						cout << "ERROR! Incorrect input" <<endl;

					}
				}while(!isProperDate);
				isProperDate = false;

				/// enter the date that the passenger wants to travel on
				do{
					setrgb(questcol);
					cout << "What is the date that the passenger wants to travel? ";
					setrgb(inputcol);
					getline( cin, input);
					///cin >> temp;cin >>temp;
					if ( isInputDigit(input) ){
						date = (int) atoi(input.c_str());
						if (checkDate(date, month,year)){						
							isProperDate=true;
						}

					}
					else
						isProperDate = false;

					if (isProperDate == false)
					{
						setrgb(replycol);
						cout << "ERROR! Date doesn't exist!" <<endl;
					}

				}while(!isProperDate);

				isProperDate = false;


				flightExist= doesFlightExistOn(year,month,date,fnum);/// check to see if that flight exists on that date

				///check if flight is full
				///check for existing booking db
				vector<flightManifest> test = schedList.at(foundi).getBookingDB();

				/*for (int y=0; y < test.size();y++){
				if (test.at(y).getDate() == date)
				if (test.at(y).getMonth() == month)
				if (test.at(y).getYear() == year)
				if (test.at(y).isFull() == false){
				foundExistingBooking = y;
				break;
				}
				else
				foundExistingBooking = -1;
				else
				foundExistingBooking = -1;
				else
				foundExistingBooking = -1;
				else
				foundExistingBooking = -1;

				}
				if (foundExistingBooking !=-1){
				if (!test.at(foundExistingBooking).isFull() ){
				flightExist = true;
				///break;
				}
				else{
				cout << "Booking is full. Try another date." <<endl;
				flightExist = false;

				}
				}*/




			}while(!flightExist);

			do ///seat 
			{
				do{///row
					setrgb(questcol);
					cout << "	Enter the row that the passenger wants a seat on : " <<endl;
					setrgb(inputcol);
					getline(cin, input);

					if ( isInputDigit(input) == true){

						row =(int) atoi(input.c_str()); 

						if(row>0 && row<21) 
							isProperRow = true;
						else
							isProperRow = false;
					}
					else {
						isProperRow = false;
						setrgb(replycol);
						cout << "Please input the correct Row from 0-20."<<endl;
					}
				}while(!isProperRow);

				do{///letter
					setrgb(questcol);
					cout << "	Enter the letter that the passenger wants a seat on : " <<endl;
					setrgb(inputcol);
					getline(cin, input);


					if ( isInputDigit(input) == false){
						letter = input.at(0);
						if(letter == "a" || letter=="b" || letter=="c" || letter=="d" || letter == "A" ||  letter == "B" || letter == "C" || letter == "D")	
							isProperLetter = true;
						else
							isProperLetter = false;
					}
					else{
						isProperLetter = false;
						setrgb(replycol);
						cout << "ERROR! Incorrect letter format (A,B,C or D)." <<endl;
					}
				}while(!isProperLetter);


				/*
				for (int i=0; i< (int)schedList.at(foundi).getBookingDB().size();i++)
				{
				if((schedList.at(foundi).getBookingDB().at(i).getDate()==date)&&(schedList.at(foundi).getBookingDB().at(i).getMonth()==month)&&(schedList.at(foundi).getBookingDB().at(i).getYear()==year))
				isProperSeat = schedList.at(foundi).getBookingDB().at(i).isSeatRowLetterAvailable(row,letter);
				else
				cout<<" No record for this date."<<endl;

				}
				*/

				///check if seat is taken

				tempBookList = schedList.at(foundi).getBook();
				isProperSeat = true;
				///bool taken = false;
				for (int y =0; y < tempBookList.size(); y++){
					if (tempBookList.at(y).getSeatRow() == row)
						if (tempBookList.at(y).getSeatLetter() == letter){
							isProperSeat = false;
							setrgb(replycol);
							cout << "Seat taken." <<endl;							
						}
						else{
							isProperSeat = true;							
						}
					else 
						isProperSeat = true;
				}
			}while ( !isProperSeat);


			isProperSeat = false;
			if (tempBookList.size() == 80)
				schedList.at(foundi).setPlaneFull(true);
			else
				schedList.at(foundi).setPlaneFull(false);



			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);


			tempBookList = schedList.at(foundi).getBook();
			tempBookList.push_back(currentPassengerBooking);
			schedList.at(foundi).setBook(tempBookList);


			///			schedList.at(foundi).getBookDB().pushBooking(currentPassengerBooking);
			///			schedList.at(foundi).getBookDB().setDMY(date, month,year);
			///update db
			/*			vector<flightManifest> test = schedList.at(foundi).getBookingDB();

			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);

			///if (test.at(i)
			///test.at(foundExistingBooking).getBooking().at(i).setPassenger(currentPassenger);
			if (foundExistingBooking != -1)
			{///test.at(foundExistingBooking).pushBooking(currentPassengerBooking); ///year should already be set!

			schedList.at(foundi).getBookingDB().at(foundExistingBooking).pushBooking(currentPassengerBooking);
			}
			else{

			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);
			current.pushBooking(currentPassengerBooking);
			current.setDMY(date,month,year);
			vector<flightManifest> temp;
			temp.push_back(current);
			///test.at(foundE	xistingBooking).pushBooking(currentPassengerBooking);
			///test.at(foundExistingBooking).setDMY(date, month, year);
			///test.push_back(current);
			schedList.at(foundi).setBookingDB(temp);
			}*/


			///foundi = 0;

			/*
			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);
			current.pushBooking(currentPassengerBooking);
			current.setDMY(date,month,year);
			*/

			/*vector<flightManifest> currentList = schedList.at(foundi).getBookingDB(); ///this is done so we don't destroy original data

			int foundBook =0;
			bool exists = false;
			for (int i =0; i < currentList.size(); i++){
			if (currentList.at(i).getYear() == year)
			if (currentList.at(i).getMonth() == month)
			if (currentList.at(i).getDate() == date) {
			foundBook = i;
			break;}
			else
			exists = false;
			else
			exists = false;
			else
			exists = false;

			}

			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);


			if (exists == false){ ///if doesn't exist, create new

			current.pushBooking(currentPassengerBooking);
			current.setDMY(date,month,year);
			currentList.push_back(current);
			}
			else {
			///current = currentList.at(foundBook).getBooking();
			///current.pushBooking(currentPassengerBooking);
			///currentList.at(foundBook) = current;
			currentList.at(foundBook).pushBooking(currentPassengerBooking);
			}
			schedList.at(foundi).setBookingDB(currentList);
			*/
			/*
			currentList = schedList.at(foundi).getBookingDB();

			cout << currentList.front().getDate() <<endl;
			cout << currentList.front().getBooking().front().getSeatLetter() <<endl;
			cout << currentList.front().getBooking().front().getPassenger().getName() <<endl;
			*/


		}
		///AirlineAgents();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///update passenger personal info
	void optionUPI() ////User uses this function to update passenger personal information.
	{
		string input;
		bool isProperPassport = false;
		bool isProperTelephone = false;
		bool isProperName = false;
		bool isProperFlightNumber = false;
		bool isProperAdd = false;
		bool isProperDate = false;
		bool isProperRow = false;
		bool isProperLetter = false;
		bool isProperSeat = false;
		string test;
		int temp;
		int foundi =-1;
		int foundpassport =-1;
		int date,month, year;
		int fnum;
		int row;
		string letter;
		bool flightExist= false;
		passenger currentPassenger;
		bookingInfo currentPassengerBooking;
		flightManifest current;
		int foundExistingBooking =-1;
		vector<bookingInfo> tempBookList;

		setrgb(questcol);
		cout << "	Update a Passenger's Information:" << endl;

		if (flightNumbers.empty() == true)
		{
			setrgb(replycol);
			cout << "ERROR! No flights exist! We cannot book anyone at the moment." << endl;
		}
		else
		{

			do{
				setrgb(questcol);
				cout << "	Enter the Flight # the passenger wants to update the booking with: ";
				setrgb(inputcol);
				getline(cin,input);
				if ( isInputDigit(input) )
				{
					fnum = atoi(input.c_str());
					///if (checkFlightNumber(fnum))
					///{

					///compare the entered flight number with the existing ones.....



					for (int i=0; i< (int)schedList.size();i++)
					{
						if (schedList.at(i).getFlight().getFlightNumber() == fnum)
							foundi = i;
					}

					if(foundi!=-1)
						isProperFlightNumber = true;
					///}


				}
				else{
					isProperFlightNumber = false;
				}

				if (isProperFlightNumber == false)
				{		
					setrgb(replycol);				
					cout << "	Flight does not exist. Try again." << endl ;
				}


			}while (!isProperFlightNumber);

			tempBookList = schedList.at(foundi).getBook();




			do ///get passport number
			{
				setrgb(questcol);
				cout << "	What is the passport info of the passenger whose information is being updated?" <<endl;
				cout <<"	Passport #: ";
				setrgb(inputcol);
				getline(cin, input);

				if (input.size() == 11) ///1 char + 10 numbers
				{
					test = input.at(0);
					if ( isInputDigit(test) == false)
						isProperPassport = true;
					else
					{
						setrgb(replycol);					
						cout << "ERROR! First alphanumeric character is not an alphabet character!" <<endl;
					}
				}
				else{
					setrgb(replycol);
					cout << "ERROR! Incorrect passport format. 1 letter then 10 digits please." <<endl;
				}
			}while ( !isProperPassport);


			for (int i=0; i< (int)tempBookList.size();i++)
			{
				if (tempBookList.at(i).getPassenger().getPassportNum() == input)
					foundpassport = i;
			}
			currentPassengerBooking = tempBookList.at(foundpassport);
			currentPassenger = tempBookList.at(foundpassport).getPassenger();

			do ///get new passport number
			{
				setrgb(questcol);
				cout << "	What is the new passport info of the passenger whose information is being updated?" <<endl;
				cout <<"	Passport # (CAP SENSITIVE): ";
				setrgb(inputcol);
				getline(cin, input);

				if (input.size() == 11) ///1 char + 10 numbers
				{
					test = input.at(0);
					if ( isInputDigit(test) == false)
						isProperPassport = true;
					else
					{
						setrgb(replycol);
						cout << "ERROR! First alphanumeric character is not an alphabet character!" <<endl;
					}
				}
				else{
					setrgb(replycol);
					cout << "ERROR! Incorrect passport format. 1 letter then 10 digits please." <<endl;
				}
			}while ( !isProperPassport);

			currentPassenger.setPassportNum(input);


			do ///passenger name
			{
				setrgb(questcol);
				cout << "	What is the new Full Name of the passenger ?" <<endl;
				cout << "	Name: ";
				setrgb(inputcol);
				getline(cin, input);
				if(input.size()<50)
				{
					if ( isInputDigit(input) == false)
						isProperName = true;
					else{
						setrgb(replycol);
						cout << "ERROR! Name should be characters and not numbers!" <<endl;
					}
				}
				else{
					setrgb(replycol);
					cout << "ERROR! Incorrect name format. Name should be less than 50 characters." <<endl;
				}
			}while ( !isProperName);
			currentPassenger.setName(input);

			do ///passenger address
			{
				setrgb(questcol);
				cout << "	What is the new address of the passenger ?" <<endl;
				cout << "	Address: ";
				setrgb(inputcol);
				getline(cin, input);
				if(input.empty()){
					setrgb(replycol);
					cout << "ERROR! Empty string" <<endl;
					isProperAdd = false;
				}
				else
					isProperAdd = true;
			}while ( !isProperAdd);
			currentPassenger.setAddress(input);


			do ///passenger's telephone
			{
				setrgb(questcol);
				cout << "	What is the new telephone of the passenger ?" <<endl;
				cout <<"	Telephone # (5141234567): ";
				setrgb(inputcol);
				getline(cin, input);

				if (input.size() == 10) ///1 char + 10 numbers
				{
					if ( isInputDigit(input) == true)
						isProperTelephone = true;
					else
					{
						setrgb(replycol);
						cout << "ERROR! Not a valid entry."<<endl;
					}
				}
				else
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect telephone format. 10 digits please." <<endl;
				}
			}while ( !isProperTelephone);


			temp = atoi(input.c_str());

			currentPassenger.setTelephone(temp);


			do ///seat 
			{
				do{///row
					setrgb(questcol);
					cout << "	Enter the new row that the passenger wants a seat on : ";
					setrgb(inputcol);
					getline(cin, input);

					if ( isInputDigit(input) == true){

						row =(int) atoi(input.c_str()); 

						if(row>0 && row<21) 
							isProperRow = true;
						else
							isProperRow = false;
					}
					else {
						isProperRow = false;
						setrgb(replycol);
						cout << "Please input the correct Row from 0-20."<<endl;
					}
				}while(!isProperRow);

				do{///letter
					setrgb(questcol);
					cout << "	Enter the new letter that the passenger wants a seat on : ";
					setrgb(inputcol);
					getline(cin, input);


					if ( isInputDigit(input) == false){
						letter = input.at(0);
						if(letter == "a" || letter=="b" || letter=="c" || letter=="d")	
							isProperLetter = true;
						else
							isProperLetter = false;
					}
					else{
						isProperLetter = false;
						setrgb(replycol);
						cout << "ERROR! Incorrect letter format (a,b,c or d)." <<endl;
					}
				}while(!isProperLetter);



				///check if seat is taken

				tempBookList = schedList.at(foundi).getBook();
				isProperSeat = true;
				///bool taken = false;
				for (int y =0; y < tempBookList.size(); y++){
					if (tempBookList.at(y).getSeatRow() == row)
						if (tempBookList.at(y).getSeatLetter() == letter){
							isProperSeat = false;
							setrgb(replycol);
							cout << "Seat taken." <<endl;							
						}
						else{
							isProperSeat = true;							
						}
					else 
						isProperSeat = true;
				}
			}while ( !isProperSeat);


			isProperSeat = false;
			if (tempBookList.size() == 80)
				schedList.at(foundi).setPlaneFull(true);
			else
				schedList.at(foundi).setPlaneFull(false);



			currentPassengerBooking.setPassenger(currentPassenger);
			currentPassengerBooking.setSeatLetter(letter);
			currentPassengerBooking.setSeatRow(row);


			tempBookList = schedList.at(foundi).getBook();
			tempBookList.at(foundpassport) = currentPassengerBooking;
			schedList.at(foundi).setBook(tempBookList);


		}

		///AirlineAgents();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///******** merged this function with the optionPI()......no need to use it
	///booking passenger on a flight
	void optionBPF() ////User uses this function to book passenger on a flight.
	{
		setrgb(questcol);
		cout << "	Book a Passenger on a Flight:" << endl;
		cout << "	Enter Passenger's : ";



		///AirlineAgents();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///cancel passenger booking 
	void cancelBooking() //// Cancels a Passenger's Booking.
	{
		string input;
		///int data;

		vector<bookingInfo> tempBookList;
		int foundi;
		int flightnum;
		int row;
		string letter;
		
		setrgb(questcol);
		cout << "	Cancel a Booking:" << endl;
		cout << "	Enter flight number : ";
		setrgb(inputcol);
		getline(cin, input);

		flightnum = atoi(input.c_str());

		setrgb(questcol);
		cout << "	Enter seat row number : ";
		setrgb(inputcol);
		getline(cin, input);

		row =  atoi(input.c_str());

		setrgb(questcol);
		cout << "	Enter seat letter: ";
		setrgb(inputcol);
		getline(cin, input);

		letter = input;

		for (int i=0; i< (int)schedList.size();i++)
		{
			if (schedList.at(i).getFlight().getFlightNumber() == flightnum){
				foundi = i;
				tempBookList = schedList.at(foundi).getBook();

				for (int y =0; y < tempBookList.size(); y++){
					if (tempBookList.at(y).getSeatRow() == row)
						if (tempBookList.at(y).getSeatLetter() == letter){
							setrgb(replycol);
							cout << "Passenger " << tempBookList.at(y).getPassenger().getName() << " is being removed from flight #" << schedList.at(i).getFlight().getFlightNumber() << "."<<endl;
							tempBookList.erase( tempBookList.begin() + (int)y);	 
							schedList.at(i).setBook(tempBookList);

							break;
						}
						else
						{
							setrgb(inputcol);
							cout << "Seat not taken."<<endl;
						}
					else{
						setrgb(inputcol);
						cout << "Seat not taken." <<endl;
					}
				}
			}
			///else
			///	cout << "Flight doesn't exist!" <<endl;
		}


		///AirlineAgents();

	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///show last passenger info
	void optionDPI() ////shows the master list of passenger informations.
	{
		///	showAllPassengers(); /// not implemented yet
		///AirlineAgents();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///show update flight info
	void optionU() ////User uses this function to update flight/schedule information
	{
		int err = 0; ///error codes
		string temp;
		flight flighttemp;

		schedule current;

		///Update a flight number
		///does not check for duplicate 
		///cin >> temp;
		setrgb(questcol);
		cout << "	Update a flight:" << endl;
		///



		///flightNumbers.at(0)= 1234;
		///current = schedList.at(0);

		setrgb(questcol);
		cout << "Enter Flight Number: " ;
		setrgb(inputcol);
		err = 0;
		int fnumber;
		///getline( cin, temp);
		do{
			err = 0;
			getline( cin, temp);

			if (isInputDigit(temp.c_str()))
				fnumber = atoi(temp.c_str());
			else{
				err = 1;
				setrgb(replycol);
				cout << "Not a number" <<endl;
			}
		}while (err==1);

		///flighttemp.getFlightNumber(fnumber);

		int foundi =-1;
		for (int i=0; i< (int)schedList.size();i++){
			///cout << fnumber;
			///cout << " F " << schedList.at(i).getFlight().getFlightNumber()  <<endl;
			if (schedList.at(i).getFlight().getFlightNumber() == fnumber)
				foundi = i;

		}


		if ( foundi !=-1){
			setrgb(questcol);
			cout << "You are now modifying flight number: " << fnumber <<"'s information." <<endl;
			current = schedList.at(foundi);
			flighttemp.setFlightNumber ( schedList.at(foundi).getFlight().getFlightNumber() );

			///ask for airline name
			setrgb(questcol);
			cout << "	Enter New Airline: (" << current.getFlight().getAirline() << ") ";
			setrgb(inputcol);
			getline( cin, temp);
			flighttemp.setAirline(temp);

			///ask for departure city name
			setrgb(questcol);
			cout << "	Enter New Departure City: (" << current.getFlight().getDepCity() << ") ";
			setrgb(inputcol);
			getline( cin, temp);
			flighttemp.setDepCity(temp);

			///ask for departure airport name
			setrgb(questcol);
			cout << "	Enter New Departure Airport: (" << current.getFlight().getDepAirport() << ") ";
			setrgb(inputcol);
			getline( cin, temp);
			flighttemp.setDepAirport(temp);

			///ask for destination city name
			setrgb(questcol);
			cout << "	Enter New Destination City: (" << current.getFlight().getArrivalCity() << ") ";
			setrgb(inputcol);
			getline( cin, temp);
			flighttemp.setArrivalCity (temp);

			///ask for destination airport name
			setrgb(questcol);
			cout << "	Enter New Arrival Airport: (" << current.getFlight().getArrivalAirport() << ") ";
			setrgb(inputcol);
			getline( cin, temp);
			flighttemp.setArrivalAirport(temp);
			cout << endl << endl; 

			///push the flight into the database.
			///probably not needed

			///flightList.push_back(flighttemp);


			///Scheduling
			schedule s1;
			bool isNumber = false;
			int data;
			temp ="a";
			///schedule an hour
			do{
				isNumber = true;
				setrgb(questcol);
				cout << "What hour is the new flight at? (" << current.getdepHour() << ") ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;

				if (isInputDigit(temp)){
					data = atoi(temp.c_str());
					if (!checkHour(data)){
						setrgb(replycol);
						cout << "ERROR: Not valid hour!" <<endl;
						isNumber = false;
					}
					else 
						isNumber = true;
				}
				else
					isNumber = false;



			}while(isNumber == false);

			s1.setdepHour(data);


			///schedule a min
			do{
				isNumber = true;
				setrgb(questcol);
				cout << "What minute is the new flight at? (" << current.getdepMin() << ") ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;

				if (isInputDigit(temp)){
					data = atoi(temp.c_str());
					if (!checkMin(data)){
						setrgb(replycol);
						cout << "ERROR: Not valid minute!" <<endl;
						isNumber = false;
					}
					else 
						isNumber = true;
				}
				else
					isNumber = false;



			}while(isNumber == false);

			s1.setdepMin(data);

			///How long is the flight supposed to be
			do{
				isNumber = true;
				setrgb(questcol);
				cout << "How long is the new flight in minutes? (" << current.getFlightLength() << ") ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;

				if (isInputDigit(temp)){
					data = atoi(temp.c_str());
					if (data <1){
						setrgb(replycol);
						cout << "ERROR: Not valid time frame!" <<endl;
						isNumber = false;
					}
					else 
						isNumber = true;
				}
				else
					isNumber = false;



			}while(isNumber == false);

			s1.setFlightLength(data);


			///schedule a day
			day t1;
			bool yorn =false;
			setrgb(questcol);
			cout << "What days is the new flight scheduled for? yes (y) or no (n) " <<endl;
			do{ ///mondays
				yorn = true;
				setrgb(questcol);
				cout <<"Monday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;	
				cout << endl;

				if (temp == "y")
					t1.monday = true;
				else if (temp == "n")
					t1.monday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			yorn = false;

			do{ ///tuesday
				yorn = true;
				setrgb(questcol);
				cout <<"Tuesday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;	
				cout << endl;

				if (temp == "y")
					t1.tuesday = true;
				else if (temp == "n")
					t1.tuesday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			yorn = false;

			do{ ///wednesday
				yorn = true;
				setrgb(questcol);
				cout <<"Wednesday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;
				cout << endl;

				if (temp == "y")
					t1.wednesday = true;
				else if (temp == "n")
					t1.wednesday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			yorn = false;

			do{ ///thursday
				yorn = true;
				setrgb(questcol);
				cout <<"Thursday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;
				cout << endl;

				if (temp == "y")
					t1.thursday = true;
				else if (temp == "n")
					t1.thursday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);


			yorn = false;

			do{ ///friday
				yorn = true;
				setrgb(questcol);
				cout <<"Friday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;
				cout << endl;

				if (temp == "y")
					t1.friday = true;
				else if (temp == "n")
					t1.friday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			yorn = false;

			do{ ///saturday
				yorn = true;
				setrgb(questcol);
				cout <<"Saturday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;
				cout << endl;

				if (temp == "y")
					t1.saturday = true;
				else if (temp == "n")
					t1.saturday = false;
				else {
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			do{ ///sunday
				yorn = true;
				setrgb(questcol);
				cout <<"Sunday? ";
				setrgb(inputcol);
				getline( cin, temp);///cin >> temp;
				cout << endl;

				if (temp == "y")
					t1.sunday = true;
				else if (temp == "n")
					t1.sunday = false;
				else {
					setrgb(replycol);
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}

			}while(yorn == false);

			s1.setDay(t1);		

			///does this repeat every week?
			setrgb(questcol);
			cout << "Does this schedule repeat everyweek? Yes (y) or No (n) ";
			setrgb(inputcol);
			getline( cin, temp);///cin >> temp;
			cout << endl;
			do{ ///every week?
				yorn = true;
				if (temp == "y")
					s1.setRepeat(true);
				else if (temp == "n")
					s1.setRepeat(false);
				else{
					setrgb(replycol);
					cout <<"ERROR! Incorrect Input" <<endl;
					yorn = false;
				}
			}while(yorn == false);

			///if it does not repeat, ask for the date it will happen.
			///NEED TO ADD MONTH AND YEAR
			int date =-1;
			s1.setdepDate(date);
			if (temp == "n"){


				yorn = false;
				do{
					yorn = true;
					setrgb(questcol);
					cout << "What is the date of the month this flight will take off? ";
					setrgb(inputcol);
					getline( cin, temp);///cin >>temp;
					if ( isInputDigit(temp) ){
						date = (int) atoi(temp.c_str());
						if (checkDate(date)){						
							s1.setdepDate(date);
						}
						else
							yorn = false;
					}
					else
						yorn = false;

					if (yorn == false)
					{
						setrgb(replycol);
						cout << "ERROR! Incorrect input" <<endl;
					}

				}while(yorn == false);

			}


			///insert into database
			s1.setFlight(flighttemp);			
			///schedList.push_back(s1);
			///if ( foundi >=0)
			schedList.at(foundi) = s1;

			OperationManagers();
		}
		else
		{
			setrgb(replycol);
			cout << "No flight with that number!" <<endl;
		}
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///show last flight info
	void optionD() ////shows the master list of flights/schedules. Was original a different function. 
	{
		showAllFlights();
		///Menu();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///show all schedule flights
	void showAllFlights()////shows the master list of flights/schedules.
	{
		if (!schedList.empty())
		{////shows only today's flights
			///flight current = flightList.front();

			schedule current;
			int size = schedList.size();
			for (int i =0; i<size;i++){
				current = schedList.at(i);
				setrgb(replycol);
				cout << "	Flight Number: " << current.getFlight().getFlightNumber() <<endl;
				cout << "	Flight Airline: " << current.getFlight().getAirline() <<endl;
				cout << "	Departure City: " << current.getFlight().getDepCity() <<endl;
				cout << "	Departure Airport: " << current.getFlight().getDepAirport() <<endl;
				cout << "	Arrival City: " << current.getFlight().getArrivalCity() <<endl;
				cout << "	Arrival Airport: " << current.getFlight().getArrivalAirport() <<endl;
				///cout << "	Departure Year: " << current.getdepYear() <<endl;
				cout << "	Departure Time: " << current.getdepHour() <<":"<<current.getdepMin() << endl;
				///cout << "	Departure Date: " << current.getdepDate() <<endl;
				///cout << "	Departure Month: " << current.getdepMonth() <<endl;
				cout << "	Flight Length: " << current.getFlightLength() <<endl;
				cout << "	Flight Arrival time: " << (current.getdepHour()+(current.getFlightLength()/60))%24 << ":" <<(current.getdepMin()+current.getFlightLength())%60 << " (" << (current.getdepHour()+(current.getFlightLength()/60))/24 << " days later)" << endl;
				cout << "	Repeat: ";
				if (current.getRepeat())
					cout << "Yes" <<endl;
				else {
					setrgb(replycol);
					cout <<"No" <<endl;
					cout << "	Departure Year: " << current.getdepYear() <<endl;
					cout << "	Departure Month: " << current.getdepMonth() <<endl;
					cout << "	Departure Date: " << current.getdepDate() <<endl;
					cout << "	Departure Time: " << current.getdepHour() <<":"<<current.getdepMin() << endl;
				}
				setrgb(replycol);
				cout << "	Days: ";
				if (current.getDay().monday)
					cout <<" Monday ";
				if (current.getDay().tuesday)
					cout <<" Tuesday ";
				if (current.getDay().wednesday)
					cout <<" Wednesday ";
				if (current.getDay().thursday)
					cout <<" Thursday ";
				if (current.getDay().friday)
					cout <<" Friday ";
				if (current.getDay().saturday)
					cout <<"Saturday ";
				if (current.getDay().sunday)
					cout <<"Sunday ";

				cout <<endl <<endl;

			}
		}
		else
			cout << "No flights have been scheduled!" <<endl;

		///Menu();
	}
	///--------------------------------------------------------------------------------
	///show flights that are for today
	void showFlyingTodayList()
	{

		manager.push(schedList);
		flyingList = manager.getFlyingTodayList();
		///flyingList = manager.getCurrentlyFlyingList();
		if (!flyingList.empty()){
			///flight current = flightList.front();
			schedule current;
			int size = flyingList.size();	
			for (int i =0; i<size;i++){
				current = flyingList.at(i);
				setrgb(replycol);
				cout << "	Flight Number: " << current.getFlight().getFlightNumber() <<endl;
				cout << "	Flight Airline: " << current.getFlight().getAirline() <<endl;
				cout << "	Departure City: " << current.getFlight().getDepCity() <<endl;
				cout << "	Departure Airport: " << current.getFlight().getDepAirport() <<endl;
				cout << "	Arrival City: " << current.getFlight().getArrivalCity() <<endl;
				cout << "	Arrival Airport: " << current.getFlight().getArrivalAirport() <<endl;
				///cout << "	Departure Month: " << current.getdepMonth() <<endl;
				///cout << "	Departure Year: " << current.getdepYear() <<endl;
				///cout << "	Departure Time: " << current.getdepHour() <<":"<<current.getdepMin() << endl;
				///cout << "	Departure Date: " << current.getdepDate() <<endl;
				cout << "	Flight Length: " << current.getFlightLength() <<endl;
				cout << "	Flight Arrival time: " << (current.getdepHour()+(current.getFlightLength()/60))%24 << ":" <<(current.getdepMin()+current.getFlightLength())%60 << " (" << (current.getdepHour()+(current.getFlightLength()/60))/24 << " days later)" << endl;

				cout << "	Repeat: ";
				if (current.getRepeat())
				{
					setrgb(replycol);
					cout << "Yes" <<endl;
				}
				else {
					setrgb(replycol);
					cout <<"No" <<endl;
					cout << "	Departure Month: " << current.getdepMonth() <<endl;
					cout << "	Departure Year: " << current.getdepYear() <<endl;
					cout << "	Departure Time: " << current.getdepHour() <<":"<<current.getdepMin() << endl;
					cout << "	Departure Date: " << current.getdepDate() <<endl;
				}

				setrgb(replycol);
				cout << "	Days: ";
				if (current.getDay().monday)
					cout <<" M  ";
				if (current.getDay().tuesday)
					cout <<" Tu ";
				if (current.getDay().wednesday)
					cout <<" W  ";
				if (current.getDay().thursday)
					cout <<" Th ";
				if (current.getDay().friday)
					cout <<" F  ";
				if (current.getDay().saturday)
					cout <<" Sa ";
				if (current.getDay().sunday)
					cout <<" Su ";

				cout <<endl <<endl;

			}
		}
		else
		{
			setrgb(replycol);
			cout << "No flights have been scheduled for today!" <<endl;
		}

		///Menu();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///set flight schedule
	void optionS() ////function to create flight/schedule
	{
		int flightnum;
		int err = 0; ///error codes
		int date;
		string temp;
		flight flighttemp;

		///Create a flight number
		///does not check for duplicate 
		///cin >> temp;
		setrgb(questcol);
		cout << "	Schedule a Flight:" << endl;
		///getline(cin,temp);
		do{
			setrgb(questcol);
			cout << "	Enter Flight #: ";
			setrgb(inputcol);
			getline(cin,temp);///flightnum;
			if ( isInputDigit(temp) ) {
				flightnum = atoi(temp.c_str());
				if (checkFlightNumber(flightnum)){
					flighttemp.setFlightNumber(flightnum);
					flightNumbers.push_back(flightnum);
					err = 0;
				}
				else
					err = 1;

			}
			else{
				err = 1; ///error 1 for bad flight number
			}

			if (err ==1)
			{
				setrgb(replycol);
				cout << "Flight number needs to be 4 digits long." << endl 
					<< "No duplicates allowed!" <<endl;
			}

			///cout << "Error: " << temp;
		}while (err != 0);

		///ask for airline name
		setrgb(questcol);
		cout << "	Enter Airline: ";
		setrgb(inputcol);
		getline( cin, temp);
		flighttemp.setAirline(temp);

		///ask for departure city name
		setrgb(questcol);
		cout << "	Enter Departure City: ";
		setrgb(inputcol);
		getline( cin, temp);
		flighttemp.setDepCity(temp);

		///ask for departure airport name
		setrgb(questcol);
		cout << "	Enter Departure Airport: ";
		setrgb(inputcol);
		getline( cin, temp);
		flighttemp.setDepAirport(temp);

		///ask for destination city name
		setrgb(questcol);
		cout << "	Enter Destination City: ";
		setrgb(inputcol);
		getline( cin, temp);
		flighttemp.setArrivalCity (temp);

		///ask for destination airport name
		setrgb(questcol);
		cout << "	Enter Arrival Airport: ";
		setrgb(inputcol);
		getline( cin, temp);
		flighttemp.setArrivalAirport(temp);
		cout << endl << endl; 

		///push the flight into the database.
		///probably not needed

		///flightList.push_back(flighttemp);


		///Scheduling
		schedule s1;
		bool isNumber = false;
		bool yorn = false;
		int data;
		temp ="a";
		///schedule an hour
		do{
			isNumber = true;
			setrgb(questcol);
			cout << "What hour is the flight at?" <<endl;
			setrgb(inputcol);
			getline( cin, temp);
			///cin >> temp;

			if (isInputDigit(temp)){
				data = atoi(temp.c_str());
				if (!checkHour(data)){
					setrgb(replycol);
					cout << "ERROR: Not valid hour!" <<endl;
					isNumber = false;
				}
				else 
					isNumber = true;
			}
			else
				isNumber = false;



		}while(isNumber == false);

		s1.setdepHour(data);


		///schedule a min
		do{
			isNumber = true;
			setrgb(questcol);
			cout << "What minute is the flight at? " <<endl;
			setrgb(inputcol);
			getline( cin, temp);
			///cin >> temp;

			if (isInputDigit(temp)){
				data = atoi(temp.c_str());
				if (!checkMin(data)){
					setrgb(replycol);
					cout << "ERROR: Not valid minute!" <<endl;
					isNumber = false;
				}
				else 
					isNumber = true;
			}
			else
				isNumber = false;



		}while(isNumber == false);

		s1.setdepMin(data);

		///How long is the flight supposed to be
		do{
			isNumber = true;
			setrgb(questcol);
			cout << "How long is the flight in minutes? " <<endl;
			setrgb(inputcol);
			getline( cin, temp);
			///cin >> temp;

			if (isInputDigit(temp)){
				data = atoi(temp.c_str());
				if (data <1){
					setrgb(replycol);
					cout << "ERROR: Not valid time frame!" <<endl;
					isNumber = false;
				}
				else 
					isNumber = true;
			}
			else
				isNumber = false;



		}while(isNumber == false);

		s1.setFlightLength(data);


		///does this repeat every week?
		setrgb(questcol);
		cout << "Does this schedule repeat everyweek? Yes (y) or No (n)";

		do{ ///every week?
			setrgb(inputcol);
			getline( cin, temp);
			///cin >> temp;cin >> temp;
			cout << endl;
			yorn = true;
			if (temp == "y")
				s1.setRepeat(true);
			else if (temp == "n")
				s1.setRepeat(false);
			else{
				setrgb(replycol);
				cout <<"ERROR! Incorrect Input" <<endl;
				yorn = false;
			}
		}while(yorn == false);

		if (s1.getRepeat() == false){
			yorn = false;
			do{
				yorn = true;
				setrgb(questcol);
				cout << "What is the Year this flight will take off? ";
				setrgb(inputcol);
				getline( cin, temp);
				///cin >> temp;cin >>temp;
				if ( isInputDigit(temp) ){
					date = (int) atoi(temp.c_str());
					if (checkYear(date)){						
						s1.setdepYear(date);
					}
					else
						yorn = false;
				}
				else
					yorn = false;

				if (yorn == false)
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect input" <<endl;
				}

			}while(yorn == false);
			yorn = false;
			do{
				yorn = true;
				setrgb(questcol);
				cout << "What is the month this flight will take off? ";
				setrgb(inputcol);
				getline( cin, temp);
				///cin >> temp;cin >>temp;
				if ( isInputDigit(temp) ){
					date = (int) atoi(temp.c_str());
					if (checkMonth(date)){						
						s1.setdepMonth(date);
					}
					else
						yorn = false;
				}
				else
					yorn = false;

				if (yorn == false)
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect input" <<endl;
				}

			}while(yorn == false);
			yorn = false;
			do{
				yorn = true;
				setrgb(questcol);
				cout << "What is the date of the month this flight will take off? ";
				setrgb(inputcol);
				getline( cin, temp);
				///cin >> temp;cin >>temp;
				if ( isInputDigit(temp) ){
					date = (int) atoi(temp.c_str());
					if ( checkDate(date, s1.getdepMonth(), s1.getdepYear() ) ) {						
						s1.setdepDate(date);
					}
					else
						yorn = false;
				}
				else
					yorn = false;

				if (yorn == false)
				{
					setrgb(replycol);
					cout << "ERROR! Incorrect input" <<endl;
				}

			}while(yorn == false);
		}

		///if it does not repeat, ask for the date it will happen.
		///NEED TO ADD MONTH AND YEAR
		if (s1.getRepeat() == true ){
			int date =-1;
			s1.setdepDate(date);
			temp = "n";
			if (temp == "n"){

				///schedule a day
				if (s1.getRepeat() == true) {
					day t1;
					bool yorn =false;
					setrgb(questcol);
					cout << "What days is the flight scheduled for? yes (y) or no (n)" <<endl;
					do{ ///mondays
						yorn = true;
						setrgb(questcol);
						cout <<"Mondays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;	
						cout << endl;

						if (temp == "y")
							t1.monday = true;
						else if (temp == "n")
							t1.monday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					yorn = false;


					do{ ///tuesday
						yorn = true;
						setrgb(questcol);
						cout <<"Tuesdays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;	
						cout << endl;

						if (temp == "y")
							t1.tuesday = true;
						else if (temp == "n")
							t1.tuesday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					yorn = false;

					do{ ///wednesday
						yorn = true;
						setrgb(questcol);
						cout <<"Wednesdays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;
						cout << endl;

						if (temp == "y")
							t1.wednesday = true;
						else if (temp == "n")
							t1.wednesday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					yorn = false;

					do{ ///thursday
						yorn = true;
						setrgb(questcol);
						cout <<"Thursdays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;cin >> temp;
						cout << endl;

						if (temp == "y")
							t1.thursday = true;
						else if (temp == "n")
							t1.thursday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);


					yorn = false;

					do{ ///friday
						yorn = true;
						setrgb(questcol);
						cout <<"Fridays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;cin >> temp;
						cout << endl;

						if (temp == "y")
							t1.friday = true;
						else if (temp == "n")
							t1.friday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					yorn = false;

					do{ ///saturday
						yorn = true;
						setrgb(questcol);
						cout <<"Saturdays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;cin >> temp;
						cout << endl;

						if (temp == "y")
							t1.saturday = true;
						else if (temp == "n")
							t1.saturday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					do{ ///sunday
						yorn = true;
						setrgb(questcol);
						cout <<"Sundays? ";
						setrgb(inputcol);
						getline( cin, temp);
						///cin >> temp;cin >> temp;
						cout << endl;

						if (temp == "y")
							t1.sunday = true;
						else if (temp == "n")
							t1.sunday = false;
						else {
							setrgb(replycol);
							cout <<"ERROR! Incorrect Input" <<endl;
							yorn = false;
						}

					}while(yorn == false);

					s1.setDay(t1);	
				}}}





		///insert into database
		s1.setFlight(flighttemp);			
		schedList.push_back(s1);

		////		cout << s1.getdepHour() <<endl;
		///		cout << s1.getdepMin() <<endl;

		///		schedule ty;
		///		ty = schedList.at(0);
		///		cout << ty.getdepMin() <<endl;


		/*
		cout << "JOE TEST FLIGHT OUPUTS: " << endl;
		flight current = flightList.top();
		cout << "	You have just scheduled flight #" << current.getFlightNumber() << " with " << current.getAirline() << endl 
		<< "	from " << current.getDepCity() << " at " << 1500 << " in " << current.getDepAirport() << endl
		<< "	and heading to " << current.getArrivalCity() << " at " << 1600 << " in " << current.getArrivalAirport() << endl;
		*/

		///OperationManagers();
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///airline agent todo
	void AirlineAgents() ////agent function. 
	{
		///cout << "Coming Soon!!! " << endl << endl << "Booking passengers on a flight due on Friday November 20, 2009." << endl << endl; 		cout << endl;
		setrgb(menucol);
		cout << "Menu options for Airline Agents:" << endl; 
		cout << "   Enter:  '1' to Enter Passenger Info (create new) & book him/her on a flight" << endl;
		cout << "           '2' to Update Passenger Info" << endl;
		cout << "           '3' to Cancel Booking" << endl;
		cout << "           '4' to Query Bookings" << endl;
		cout << "           '5' to Display Boarding Pass" << endl;
		cout << "           '6' to Return to Main Menu" << endl;
		cout << "Choice: ";
		setrgb(inputcol);
		getline (cin, agentchoice);
		if ( (int)agentchoice.size() == 1)
		{

			switch(agentchoice[0]){
case '1': 
	optionPI(); /// not implemented yet
	break;
case '2':
	optionUPI(); /// not implemented yet
	break;
case '3':
	cancelBooking(); /// not implemented yet
	break;
case '4':
	///optionDPI(); /// not implemented yet
	///displayFlightManifest( 2008, 1, 11, 5321);
	queryBooking();
	break;
case '5':
	boardingPass();
	break;
case '6':
	Menu();
	break;
default:
	setrgb(replycol);
	cout << "You have entered the wrong choice!" <<endl;
	AirlineAgents();
	break;
			}
		}
		else
		{
			setrgb(replycol);
			cout << "You have entered the wrong choice!" <<endl;
		}
	}
	///----------------------------------------------------------------------------------------------------------------------------------------------
	///manager menu
	void OperationManagers() ////this asks the manager what he wants to do. 
	{
		cout << endl;
		setrgb(menucol);
		cout << "Menu options for Operations Manager:" << endl; 
		cout << "   Enter:  '1' to Schedule a Flight" << endl;
		cout << "           '2' to Update a Flight" << endl;
		cout << "           '3' to Cancel a Flight" << endl;
		cout << "           '4' to Return to Main Menu" << endl;
		cout << "Choice: ";
		///cin >> managerchoice;
		setrgb(inputcol);
		getline (cin, managerchoice);

		if ( (int)managerchoice.size() == 1){

			switch(managerchoice[0]){
case '1': 
	optionS();
	OperationManagers();
	break;
case '2':
	optionU();
	OperationManagers();
	break;
case '3':
	cancelFlight();
	OperationManagers();
	break;
case '4':
	Menu();
	OperationManagers();
	break;
default:
	setrgb(replycol);
	cout << "You have entered the wrong choice!" <<endl;
	OperationManagers();
	break;
			}
		}
		else
		{
			setrgb(replycol);		
			cout << "You have entered the wrong choice!" <<endl;
		}///OperationManagers();

	}

	///----------------------------------------------------------------------------------------------------------------------------------------------
	///Main Menu Entry


	void User() ////asks what kind of user are you. 
	{
		string temp;

		bool isNumber = true;
		setrgb(questcol);
		cout << "What type of user are you? " << endl 
			<< "(Enter '1' for Airline Agents or" << endl
			<< " enter '2' for Operations Manager): ";
		setrgb(inputcol);
		getline(cin,temp);///cin >> temp;
		cout << endl;


		for (int i =0; i < (int)temp.size() ; i++){
			if ( !isdigit(temp[i]) )
				isNumber = false;
		}
		if (isNumber == true)
			user = atoi(temp.c_str());
		else
			user = -1;
		///a switch is probably better than what we have below
		if (user == 1)
		{
			AirlineAgents();
			Menu();
		}

		if (user == 2)
		{
			OperationManagers();
			Menu();
		}

		else
		{
			setrgb(replycol);
			cout << "Invalid user type! " << endl;
			cout << "Try again..." << endl << endl;
			User();
		}


	}

	void Menu() ////the main menu. asks what the user would like to do. 
	{
		string temp;
		bool isNumber = true;
		fileops db;

		setrgb(menucol);
		cout << endl << endl;
		cout << "	#########   AIRLINE RESERVATION SYSTEM   #########" << endl;
		cout << "	#   Enter 1 to Login To Your User Type           #" << endl;
		cout << "	#   Enter 2 to Display Flight Schedules          #" << endl;
		cout << "	#   Enter 3 to Display Today's Flights           #" << endl;
		cout << "	#   Enter 4 to Write to File                     #" << endl;
		cout << "	#   Enter 5 to Read from File                    #" << endl;
		cout << "	#   Enter 6 to exit...                           #" << endl;
		cout << "	##################################################" << endl << endl;
		cout << "			Choice entered: ";
		setrgb(inputcol);
		///cin >> temp;
		getline(cin, temp);
		cout << endl << endl;


		for (int i =0; i < (int)temp.size() ; i++){
			if ( !isdigit(temp[i]) )
				isNumber = false;
		}
		if (isNumber == true)
			choice = atoi(temp.c_str());
		else
			choice = -1;

		switch (choice){
case 1:
	User();
	Menu();
	break;
case 2:
	showAllFlights();
	Menu();
	break;
case 3:

	showFlyingTodayList();

	Menu();
	break;
case 4:
	setrgb(replycol);
	db.writeToFile(schedList);
	Menu();
	break;
case 5:
	if (!db.fileExist()){
		if (db.hashCheck()){
			schedList.clear();
			schedList = db.ReadFromFile();
			/*hack*/
			flightNumbers.clear();
			for (int y=0;y < (int) schedList.size(); y++)
			{
				flightNumbers.push_back(schedList.at(y).getFlight().getFlightNumber());

			}
			setrgb(replycol);
			cout << "Application updated to database." <<endl;
		}
		else
		{
			setrgb(replycol);
			cout << "DB has been corrupted and we have recovered successfully." <<endl;
		}
	}
	else
	{
		setrgb(replycol);
		cout << "File does not exist." <<endl;
	}
	Menu();
	break;
	///INSERT MORE CASES HERE
case 6:
	setrgb(replycol);
	cout << "	Thank you for using Airline Reservation System" << endl;
	exit(1);
	break;
default:
	setrgb(replycol);
	cout << "Invalid selection." <<endl;
	///doesFlightExistOn(2009,11,16,1000);	/// for testing purposes only /// this line will be removed after
	Menu();
	break;
		}


	}

	void queryBooking(){

		string choice = "1";
		string input;
		bool isValid = false;
		int year, month, date, flightn;
		setrgb(questcol);
		cout << "Are you looking for a specific flight(1) or Passenger Passport(2) or Name(3)? ";
		///cout << "Passenger Not implemented yet" <<endl;
		setrgb(inputcol);
		getline(cin, choice);


		if (choice == "2"){
			setrgb(questcol);
			cout << "What is your passport number? ";
			setrgb(inputcol);
			getline(cin, input);

			vector<int> flights; ///contains all the flights this person is flying on.
			setrgb(replycol);
			cout << "The person is flying on the following flights." <<endl;

			for (int i=0; i < schedList.size();i++)
			{
				for (int y=0;y<schedList.at(i).getBook().size();y++)
				{
					if (schedList.at(i).getBook().at(y).getPassenger().getPassportNum() == input){
						///flights.push_back(schedList.at(i);
						setrgb(replycol);
						cout << "Flight Number: " << schedList.at(i).getFlight().getFlightNumber() << endl;
						cout << "Name : " << schedList.at(i).getBook().at(y).getPassenger().getName() <<endl;
						cout << "Passport : " << schedList.at(i).getBook().at(y).getPassenger().getPassportNum() <<endl;
						cout <<	"Seat : " << schedList.at(i).getBook().at(y).getSeatRow() << schedList.at(i).getBook().at(y).getSeatLetter() <<endl <<endl;
					}
				}
			}

		}
		if (choice == "3"){
			setrgb(questcol);
			cout << "What is your name? ";
			setrgb(inputcol);
			getline(cin, input);

			vector<int> flights; ///contains all the flights this person is flying on.
			setrgb(replycol);
			cout << "The person is flying on the following flights." <<endl;

			for (int i=0; i < schedList.size();i++)
			{
				for (int y=0;y<schedList.at(i).getBook().size();y++)
				{
					if (schedList.at(i).getBook().at(y).getPassenger().getName() == input){
						///flights.push_back(schedList.at(i);
						cout << "Flight Number: " << schedList.at(i).getFlight().getFlightNumber() << endl;
						cout << "Name : " << schedList.at(i).getBook().at(y).getPassenger().getName() <<endl;
						cout << "Passport : " << schedList.at(i).getBook().at(y).getPassenger().getPassportNum() <<endl;
						cout <<	"Seat : " << schedList.at(i).getBook().at(y).getSeatRow() << schedList.at(i).getBook().at(y).getSeatLetter() <<endl<<endl;
					}
				}
			}

		}

		else if (choice == "1"){
			///displayFlightManifest( 2008, 1, 11, 5321);
			cout << endl;
			setrgb(questcol);
			cout << "Flight #: ";
			setrgb(inputcol);
			getline(cin, input);
			flightn = atoi(input.c_str());
			setrgb(questcol);
			cout << "Year: ";
			setrgb(inputcol);
			getline(cin,input);
			year = atoi(input.c_str());
			setrgb(questcol);
			cout << "Month: ";
			setrgb(inputcol);
			getline(cin,input);
			month = atoi(input.c_str());
			setrgb(questcol);
			cout << "Date: ";
			setrgb(inputcol);
			getline(cin,input);
			date = atoi(input.c_str());


			displayFlightManifest( year, month, date, flightn);///<<endl;

			/*
			cout << "Flight #: ";
			getline(cin, input);
			if (isInputDigit(input)){
			flightn = atoi(input.c_str());
			}
			else{
			isValid = false;
			cout << "Not a valid flight number." <<endl; 
			break;
			}

			cout << "Year:";
			getline(cin,input);
			if (isInputDigit(input)){
			year = atoi(input.c_str());
			if (checkYear(year))
			isValid = true;
			}
			else{
			isValid = false;
			cout << "Not a valid year number." <<endl; 
			break;
			}
			*/

		}
		else
		{
			setrgb(replycol);
			cout << "Incorrect choice." <<endl;
		}
	}

	void displayFlightManifest( int year, int month, int date, int fnum){
		bool	flightExist= doesFlightExistOn(year,month,date,fnum);/// check to see if that flight exists on that date

		if (flightExist == false)
		{
			setrgb(replycol);
			cout << "No flights on this day" <<endl;
		}
		else
		{
			///check if flight is full
			///check for existing booking db
			///vector<flightManifest> test = schedList.at(foundi).getBookingDB();
			int foundi =0;
			///int foundExistingBooking=0;
			///bookingInfo booking;

			///vector<flightManifest> test;

			for (int i=0; i< (int)schedList.size();i++)
			{
				if (schedList.at(i).getFlight().getFlightNumber() == fnum)
					foundi = i;
			}
			/*			test = schedList.at(foundi).getBookingDB();
			if (test.size() !=0)

			for (int y=0; y < test.size();y++){
			if (test.at(y).getDate() == date)
			if (test.at(y).getMonth() == month)
			if (test.at(y).getYear() == year)
			foundExistingBooking = y;					
			else
			foundExistingBooking = 0;
			else
			foundExistingBooking = 0;
			else
			foundExistingBooking = 0;

			}*/

			///flightManifest test;
			///test = schedList.at(foundi).getBookDB();

			vector<bookingInfo> booking;
			booking = schedList.at(foundi).getBook();
			setrgb(replycol);
			if (booking.size() >0){
				for (int i = 0; i < booking.size();  i++){
					setrgb(replycol);
					cout << "Name: " << booking.at(i).getPassenger().getName() << endl;
					cout << "Passport: " << booking.at(i).getPassenger().getPassportNum() <<endl;
					cout << "Telephone: " << booking.at(i).getPassenger().getTelephone() <<endl;
					cout << "Address: " << booking.at(i).getPassenger().getAddress() <<endl;
					cout << "Seat: " << booking.at(i).getSeatRow() << booking.at(i).getSeatLetter() <<endl <<endl;
				}


			}
			else
			{
				setrgb(replycol);
				cout << "No bookings found for this flight."<<endl;
			}

			/*if (test.getBooking().size() >0){
			for (int i=0; i<test.getBooking().size(); i++)
			{
			booking = test.getBooking().at(i);/// test.at(i);

			cout << "Name: " << booking.getPassenger().getName() << endl;
			cout << "Passport: " << booking.getPassenger().getPassportNum() <<endl;
			cout << "Telephone: " << booking.getPassenger().getTelephone() <<endl;
			cout << "Address: " << booking.getPassenger().getAddress() <<endl;
			cout << "Seat: " << booking.getSeatRow() << booking.getSeatLetter() <<endl;

			}

			}
			else
			cout << "No bookings on this flight."<< endl;
			}*/
		}

	}



};

#endif