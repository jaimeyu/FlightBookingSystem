/** This is an application that tracks airline flights. 
 *Creators' contact: coen-345@googlegroups.com
**/
///\brief The main doesn't actually do anything except launch the GUI. If anything, we can use the main to catch errors and restart the application. 
/* 
 * File:   main.cpp
 * Author: jaime
 *
 * Created on September 30, 2009, 3:59 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>
#include <string>
#include <ctype.h>
#include <iomanip>
#include "flight.h"
#include "schedule.h"
#include "passenger.h"
#include "bookingInfo.h"
#include "gui.h"
//----------------------------------------------------------------------------------------------------------------------------------------------
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char** argv) { 

	cout << "	Welcome The Airline Reservation System choose an" << endl << "		option from the following menu:" << endl;
	
	gui GUI;
	GUI.Menu();


	return (EXIT_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------------------------------
