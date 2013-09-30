/** this is the file input and output class.
			  the application can store its data to a file 
			  and then reload the data from the file into applicaiton memory.

			  A neat trick is that I used a MD5 hash to discover database 
			  file corruption.
			  **/
#ifndef FILEOPS_H
#define FILEOPS_H

#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "flight.h"
#include "schedule.h"
#include "day.h"

#include <vector>
#include <string>
#include <limits>
#include "hashlib/hashlibpp.h" /**this does MD5 checksum. 
DO NOT DISTRIBUTE THE BINARY/LIBRARY W/OUT ITS LICENSE. **/

class fileops 
{
private:
	//flight flightInfo;

	string filename;

public:


	fileops(){
		filename = "airline.db" ; ///MODIFY THIS if you change the database location. 


	}///constructor
	bool hashCheck(){ ///checks if the database file has been corrupted. 

		hashwrapper *md5 = new md5wrapper();
		string hashFromFile;
		fstream hashfile;

		//hashFromFile = md5->getHashFromFile(filename.c_str());
		hashfile.open("md5",fstream::in);
		hashfile >> hashFromFile;
		hashfile.close();


		//create hash from file
		string hashGenerated;


		hashGenerated = md5->getHashFromFile(filename.c_str());

		delete md5;

		//cout << "Gen: " << hashGenerated <<endl;
		//cout << "hash: " << hashFromFile <<endl;



		if (hashGenerated != hashFromFile) {
			//cout << "Corrupted database" <<endl;
			return false;
		}
		else
			return true;


	}


	bool fileExist(){

		fstream file;
		file.open (filename.c_str(),fstream::in);
		if ( file.fail()){
			file.clear(ios::failbit);
			file.close();
			return true;
		}
		else{
			file.clear(ios::failbit);
			//file.close();
			return false;
		}
	}

	vector<schedule> ReadFromFile(){
		vector<schedule> schedList;

		fstream file;
		flight flightinfo;
		schedule sched;

		///algorithm
		//get hash from file md5
		file.open (filename.c_str(),fstream::in);


		string temp;
		while(!file.eof()){
			///flight
			getline(file,temp);	//airline
			flightinfo.setAirline(temp);

			getline(file,temp);	//arrival airport
			flightinfo.setArrivalAirport(temp);

			getline(file,temp);	//arrival city
			flightinfo.setArrivalCity(temp);

			getline(file,temp);	//dep airport
			flightinfo.setDepAirport(temp);

			getline(file,temp);	//dep city
			flightinfo.setDepCity(temp);

			getline(file,temp);	//flight number
			//cout << temp;
			int num;
			num = atoi(temp.c_str());
			//cout << num;
			flightinfo.setFlightNumber(num);


			///schedule

			int data;

			getline(file,temp);	//year
			data = atoi(temp.c_str());

			sched.setdepYear(data);

			getline(file,temp);	//month
			data = atoi(temp.c_str());

			sched.setdepMonth(data);

			getline(file,temp);	//date
			data = atoi(temp.c_str());

			sched.setdepDate(data);


			getline(file,temp);	//hour
			data = atoi(temp.c_str());

			sched.setdepHour(data);


			getline(file,temp);	//min
			data = atoi(temp.c_str());

			sched.setdepMin(data);

			getline(file,temp);	//length
			data = atoi(temp.c_str());

			sched.setFlightLength(data);

			//days of the week bools
			bool yesno;
			day dayTemp;
			getline(file,temp);	//monday
			if (temp == "y")
				dayTemp.monday = true;
			else
				dayTemp.monday = false;

			getline(file,temp);	//tuesday
			if (temp == "y")
				dayTemp.tuesday = true;
			else
				dayTemp.tuesday = false;

			getline(file,temp);	//wednesday
			if (temp == "y")
				dayTemp.wednesday = true;
			else
				dayTemp.wednesday = false;

			getline(file,temp);	//thursday
			if (temp == "y")
				dayTemp.thursday = true;
			else
				dayTemp.thursday = false;

			getline(file,temp);	//friday
			if (temp == "y")
				dayTemp.friday = true;
			else
				dayTemp.friday = false;

			getline(file,temp);	//saturday
			if (temp == "y")
				dayTemp.saturday = true;
			else
				dayTemp.saturday = false;

			getline(file,temp);	//sunday
			if (temp == "y")
				dayTemp.sunday = true;
			else
				dayTemp.sunday = false;

			sched.setDay(dayTemp);

			getline(file,temp);	//repeat
			if (temp == "y")
				sched.setRepeat(true);
			else
				sched.setRepeat(false);

			//get db

			bool done = false;
			vector<bookingInfo> book;
			bookingInfo tempInfo;
			passenger tempPassenger;
			do {
				getline(file,temp);
				
				if  (temp == "</booking>")
					done = true;
				else if (file.eof())
					done = true;
				else if (temp == " ")
					done = true;
				else{
					//get seat letter
					//getline(file,temp);
					tempInfo.setSeatLetter(temp);
					
					//get row
					getline(file,temp);
					data = atoi(temp.c_str());
					tempInfo.setSeatRow(data);
					
					//getpassport num
					getline(file,temp);
					tempPassenger.setPassportNum(temp);

					//getn name
					getline(file,temp);
					tempPassenger.setName(temp);

					//get tel
					getline(file,temp);
					data = atoi(temp.c_str());
					tempPassenger.setTelephone(data);

					//get add
					getline(file,temp);
					tempPassenger.setAddress(temp);

					//now combine and store
					tempInfo.setPassenger(tempPassenger);
					book.push_back(tempInfo);
					
					//done = true;
				}

			}while (!done);

			if ( book.size() >0) ///make sure we don't store unknowns into app. 
				sched.setBook(book);


			sched.setFlight(flightinfo);
			schedList.push_back(sched);





		}
		file.close();

		schedList.pop_back();
		return schedList;

	};

	int writeToFile( vector<schedule> list){

		int error =0;

		char buffer[99999];
		string temp;

		fstream file;
		if (!list.empty()){
			if ( !file.is_open() ){
				file.open (filename.c_str(),fstream::out | fstream::trunc);

				for ( int i=0; i < (int) list.size(); i++){

					///write the flight data for this schedule
					file.write(list.at(i).getFlight().getAirline().c_str(),list.at(i).getFlight().getAirline().size());
					file << endl;
					file.write(list.at(i).getFlight().getArrivalAirport().c_str(),list.at(i).getFlight().getArrivalAirport().size());
					file << endl;
					file.write(list.at(i).getFlight().getArrivalCity().c_str(),list.at(i).getFlight().getArrivalCity().size());
					file << endl;
					file.write(list.at(i).getFlight().getDepAirport().c_str(),list.at(i).getFlight().getDepAirport().size());
					file << endl;
					file.write(list.at(i).getFlight().getDepCity().c_str(),list.at(i).getFlight().getDepCity().size());
					file << endl;
					int number =list.at(i).getFlight().getFlightNumber();

					file << number<<endl;

					///write schedule data to file

					file << list.at(i).getdepYear() <<endl;
					file << list.at(i).getdepMonth() <<endl;
					file << list.at(i).getdepDate() << endl;
					file << list.at(i).getdepHour() << endl;
					file << list.at(i).getdepMin() << endl;
					file << list.at(i).getFlightLength() <<endl;

					//day bool to string
					string out;
					if (list.at(i).getDay().monday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().tuesday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().wednesday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().thursday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().friday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().saturday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;
					if (list.at(i).getDay().sunday == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;


					///write Repeat bool
					if (list.at(i).getRepeat() == true)
						out = "y";
					else 
						out = "n";
					file << out << endl;

					//write booking
					vector<bookingInfo> temp;
					temp = list.at(i).getBook();
					for (int i=0; i< temp.size(); i++){
						file << temp.at(i).getSeatLetter() << endl;
						file << temp.at(i).getSeatRow() << endl;
						file << temp.at(i).getPassenger().getPassportNum() << endl;
						file << temp.at(i).getPassenger().getName() << endl;
						file << temp.at(i).getPassenger().getTelephone() << endl;
						file << temp.at(i).getPassenger().getAddress() << endl;
					}
					file << "</booking>"<< endl;
					temp.clear();

					out.clear();	
				}
				file.close();

				//tamper proofing our file using md5 checksum
				//uses hashlib code
				//can be put into a function
				hashwrapper *md5 = new md5wrapper();
				string hash;
				fstream hashfile;

				hash = md5->getHashFromFile(filename.c_str());
				hashfile.open("md5",fstream::out | fstream::trunc);
				hashfile << hash;
				hashfile.close();
				delete md5;

				cout << "File written successfully." <<endl;
			}
			else{ 
				error = 1;
				cout << "Unable to write to file" <<endl;
			}
		}
		else{
			cout << "List is empty" <<endl;
			error = 2;
		}
		return error;
	}


};
#endif