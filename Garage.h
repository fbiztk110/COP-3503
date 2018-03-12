class Garage{
private:
	int numOfFloors;
	Floor* floor;
	//vector<Floor> floorList;
	string* firstFloor[300];
	string* secondFloor[400];
	string* thirdFloor[400];
	string* fourthFloor[400];

	vector<User> userList;

public:
	Garage() {}
	bool checkUFID(const string& ufid);
	int matchDecalType(const string& ufid);
	int assignSlot(const string& ufid, string* userList);
	void parking(vector<User> *userList, User* user);
	static void getPosition(int& x, int& y);
}