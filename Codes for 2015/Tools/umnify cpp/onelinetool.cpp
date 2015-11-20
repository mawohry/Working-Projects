#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	cout << "Input: ";
	string input;
	getline(cin, input);
	
	ifstream readfile(input.c_str());
	vector<string> file;
	readfile >> input;
	
	while(readfile)
	{
		file.push_back(input);
		readfile >> input;
	}
	
	ofstream writefile("output.txt", ios::app);
	
	for(unsigned int i=0;i<file.size();i++)
	{
		writefile << file[i] << " ";	
	}
	
	return 0;
}
