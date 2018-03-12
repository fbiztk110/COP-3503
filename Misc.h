#include <string>
#include <vector>
using namespace::std;

class Garage
{
private:
	string name;
	int numbOfFloors;
	int spacePerFloor;
	vector<vector> parkingLots;
	vector<User> userLists;
public:

	//constructor
	Garage(string garageName, int floors, int space, string decal)
	{
		name = garageName;
		numOfFloors = floors;
		spacePerFloor = space;
		decalType = decal;
	}
	void initialize();
	bool checkDecal();
}

class User
{
private:
	string UFID;
	string nameOfGarage;
	string userUFID;
	Time timer; //don¡¯t delete this
	vector <>;

public:
	User(string UFID)
	{
		return UFID;
	}
	string getUserUFID(string userUFID)
	{
		return userUFID;
		{
			Garage* setGarage(string GarageNames)
			{
				nameOfGarage = GarageNames;
			}
			void parking(Garage* targetGarage)
			{
				targetGarage
			}
			bool freeParking(Garage* targetGarage)
			{

			}

		}