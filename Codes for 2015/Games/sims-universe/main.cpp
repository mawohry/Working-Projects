#include "world-beta.cpp"
using namespace std;

int main()
{
	WORLD world;
	string input;
	cout << "--------------------" << endl;
	cout << "|  Sims ~ Universe |" << endl;
	cout << "--------------------" << endl;
	cout << "       |            " << endl;
	cout << "       |            " << endl;
	cout << "       |            " << endl;
	cout << "      \\|/          " << endl;
	cout << "       |            " << endl;
	cout << "By: Sherlock" << endl;
	cout << "Text Based Simulation game" << endl;
	cout << "Code start year: 2015" << endl << endl;
	
	while(1)
	{
		cout << "Command: ";
		getline(cin, input);
		if(input == "exit") break;
		
		system("clear");
		world.engine(input);
		if(world.missions()) 
		{
			world.mission_count = RESET;
			cout << endl << "Level Completed!!!" << endl;
		}
		
		cout << endl;
	}
	
	cout << "Bye Bye..." << endl;
	return 0;
}

