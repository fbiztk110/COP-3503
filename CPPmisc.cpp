



bool checkDecal(User* u)
{


}

void Garage::initialize()
{
	parkinglots = new Vector<Vector>(numbOfFloors);
	for (int i = 0; i < numbOfFloors; i++)
	{
		parkingLots.push_back(new Vector<User>(spacePerFloor));
		for (int j = 0; j < spacePerFloor; j++)
		{
			parkingLots[i][j] = 0;
		}
	}
}


//main function 

int main() {

	Garage Garage1(Garage1, 4, 200, red);
	Garage Garage2(Garage2, 3, 200, green);
	Garage Garage3(Garage3, 4, 200, orange);
	Garage Garage4(Garage4, 3, 150, business);

	char enterOrLeave = ' ';
	int UFID;

	cout << "Please enter E if you are entering the garage" << endl;
	cout << "Please enter L if you are leaving the garage" << endl;


	do {
		cin >> enterOrLeave;

		if (enterOrLeave == 'E' || 'e') {
			cout << "You are entering the garage" << endl;

			cout << "Please enter your 8 digit UF ID number" << endl;
			cin >> UFID;

			if (UFID >= 10000000 && UFID <= 99999999){
				// call decalType function

			}

			else {
				cout << "Error this UFID does not exist!" << endl;
			}


		}
		else if (enterOrLeave == 'L' || 'l')  {
			cout << "You are leaving the garage" << endl;

		}

		else {
			cout << "Invalid Argument! Please enter E or L" << endl;
		}

	} while (enterOrLeave != 'E' || 'L');



}