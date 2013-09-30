#include<stdlib.h>
#include<time.h>


void SetRandom(){
	srand(time(NULL));
}




int get_rand(int min, int max)
{
	int x;
	
	if(min> max)
	{
	//	cout<<"\aERROR: Minimum value larger then maximum value!\n";
	//	cout<<"ERROR: Returning -1.";
		return -1;
	}

	x = rand() % (max+1 - min);

	return(x+min);
}