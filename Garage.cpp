#include <iostream>
#include "Garage.h"

using namespace std;
const int ufidLength = 8;

//check if the user input is an 8 digit string
bool Garage::checkUFID(const string& ufid) {
	if (ufid.length() != ufidLength || ufid.at(0) == '0') {
		return false;
	}
	for (auto it = ufid.cbegin(); it != ufid.cend(); it++) {
		if (!isdigit(*it)) {
			return false;
		}
	}
	return true;
}

/*
first, check if the user ufid is valid or not
second, use a switch case to return the floor number that the user can park his car
*/
int Garage::matchDecalType(const string& ufid) {
	int floorNum;
	int firstDigit = ufid.at(0) - '0';
	switch {
	case 1:
	case 2:
		floorNum = 1;
		break;
	case 3:
	case 4:
		floorNum = 2;
		break;
	case 5:
	case 6:
		floorNum = 3;
		break;
	case 7:
	case 8:
	case 9:
		floorNum = 4;
		break;
	}
	return floorNum;
}

/*
first, traverse the corresponding part of userlist and check if the user has already parked his car in the garage
second, while traversing the userlist mark the index of item that is free
third, after the iteration, if the user is in the list, give the information that he already parked his car there;
else, assign the user to the item that is free
*/
int Garage::assignSlot(const string& ufid, string* userList) {
	for (auto it = userList.begin(); it != userList.end(); it++) {
		if (!ufid.compare(userList[i])) {
			return -1;
		}
	}

	//another iteration to find the free slot
	for (int i = 0; i < userList.length(); i++) {
		if (userList[i].compare("free")) {
			return i;
		}
		if (i == userList.length()) {
			return -2;
		}
	}
}

static void Garage::getPosition(int &x, int&y)
{

}