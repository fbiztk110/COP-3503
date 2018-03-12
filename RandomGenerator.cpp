#include "RandomGenerator.h"

int randomID()  // random parking (generate ufid)
{
	int min = 10000000;
	int max = 99999999;
	int id = (rand() % (max - min + 1) + min);
	return id;

}

int randomTime()   //parking time for random parking
{
	int mintime = 10;  //minutes, but actually used as seconds
	int maxtime = 120;  // minutes, but actually used as seconds
	int time = (rand() % (maxtime - mintime + 1) + mintime);
	return time;
}

int randomNum(int gap)
{
	return (rand() % (gap + 1));
}

int *initialparking(int size)
//initial parking (generate ufid)  and the number of size must be ending with zero such as 10,20, 50, 100, 70,110
{

	int *existparking;
	existparking = new int[size];
	int sizeoforange = size*0.1;
	int sizeofred = size*0.4;
	int sizeofgreen = size;
	for (int i = 0; i<sizeoforange; i++) //orange
	{
		int min1 = 10000000;
		int max1 = 29999999;
		existparking[i] = (rand() % (max1 - min1 + 1) + min1);
		std::cout << existparking[i] << std::endl;

	}
	for (int i = sizeoforange; i<sizeofred; i++) //red
	{
		int min2 = 30000000;
		int max2 = 69999999;
		existparking[i] = (rand() % (max2 - min2 + 1) + min2);

	}
	for (int i = sizeofred; i<sizeofgreen; i++) //green
	{
		int min3 = 70000000;
		int max3 = 99999999;
		existparking[i] = (rand() % (max3 - min3 + 1) + min3);

	}

	for (int i = 0; i<size; i++)
	{
		std::cout << existparking[i] << std::endl;
	}
	return existparking;
}

int *timeforintialparking(int size)    // parking time for every initial parking 
{
	int *timeforparking;
	timeforparking = new int[size];
	for (int i = 0; i<size; i++)
	{
		int mintime = 10;  // minutes
		int maxtime = 100;  // minutes
		timeforparking[i] = (rand() % (maxtime - mintime + 1) + mintime);

	}
	return timeforparking;
}

/*
UFID:
1000,0000 - 2999,9999 1 decal type orange   %10
3000,0000 - 6999,9999 2 decal type red      %30
7000,0000 - 9999,9999 3 decal type green    %60
*/