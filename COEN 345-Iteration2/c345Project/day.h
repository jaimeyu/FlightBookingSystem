/***The Day class was originally a struct. Hence its simplicity.
			It contains 7 booleans, each representing a day of the week.
			It should probably be rewritten so its variables are not public. 
			***/
#ifndef DAY_H
#define DAY_H

class day{	
public:
		bool sunday;
		bool monday;
		bool tuesday;
		bool wednesday;
		bool thursday;
		bool friday;
		bool saturday;

		day(){};
	};

#endif