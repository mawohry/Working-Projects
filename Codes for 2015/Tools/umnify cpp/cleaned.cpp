#include <iostream> 
#include <fstream> 
#include <unistd.h> 
#include <vector> 
using namespace std; 
bool isHeader(string input) 
{
	if(input == "#include") return true; 
	return false; 
}

string tab(int spacing) 
{
	string temp = ""; 
	for(int i=0;i<spacing;i++) temp += "\t"; 
	return temp; 
}

int main(int argc, char** argv) 
{
	cout << "-----------------------" << endl; 
	cout << "----- Uminify cpp -----" << endl; 
	cout << "-----------------------" << endl; 
	cout << "By: 
	Wisdom Nji..." << endl << endl; 
	string filename, outputFile; 
	int braceMap = 0, run = 0; 
	bool sameLine = true, push = false, boolFile = false, boolOut = false, error = false; 
	if(argc > 1) 
	{
		for(int i=1;i<argc;i++) 
		{
			string temp = argv[i]; 
			if(temp == "--help") 
			{
				cout << "Uminify help..." << endl; 
				cout << "Usage: 
				" << endl; 
				cout << "uminify [option] [filename]" << endl << endl; 
				cout << "-o \t output filename" << endl; 
				cout << "-f \t input filename" << endl; 
				cout << "-of \t mixture of two commands" << endl << endl; 
				return 0; 
			}

			if(temp == "-f" && argv[i+1] != "\0") 
			{
				filename = argv[i+1]; 
				boolFile = true; 
			}

			else if(temp == "-o" && argv[i+1] != "\0") 
			{
				outputFile = argv[i+1]; 
				boolOut = true; 
			}

			else if(temp == "-fo" && argv[i+1] != "\0" && argv[i+2] != "\0") 
			{
				filename = argv[i+1]; 
				outputFile = argv[i+2]; 
				boolFile = true; 
				boolOut = true; 
			}

			else if(temp == "-of" && argv[i+1] != "\0" && argv[i+2] != "\0") 
			{
				outputFile = argv[i+1]; 
				filename = argv[i+2]; 
				boolFile = true; 
				boolOut = true; 
			}

		}

		if(!boolFile) 
		{
			cout << "No input file..." << endl; 
			error = true; 
		}

		if(!boolOut) 
		{
			cout << "No output file..." << endl; 
			error = true; 
		}

		if(error) return 0; 
	}

	else 
	{
		cout << "Error... Little or no arguments" << endl; 
		cout << "Run --help for input functions" << endl; 
		return 0; 
	}

	//store file in vector vector<string> file; 
	string temp; 
	ifstream read(filename.c_str()); 
	read >> temp; 
	while(read) 
	{
		file.push_back(temp); 
		read >> temp; 
	}

	//write to file ofstream write(outputFile.c_str()); 
	for(unsigned int i=0;i<file.size();i++) 
	{
		int k; 
		bool ripped = false; 
		if(file[i].size() == 2) if(file[i][0] == '}' && file[i][1] == ';') 
		{
			ripped = true; 
			file[i] = file[i][0]; 
		}

		switch(file[i][0]) 
		{
			case '#': 
			if(isHeader(file[i])) 
			{
				k = i; 
				vector<string> temp; 
				do 
				{
					if(file[k][file[k].size() -1] != '>' && file[k][file[k].size() -1] != '\"') temp.push_back(file[k]); 
					else 
					{
						temp.push_back(file[k]); 
						break; 
					}

				}

				while(++k); 
				for(unsigned int j=0;j<temp.size();j++) write << temp[j] + " "; 
				write << endl; 
				i = k; 
			}

			break; 
			case '{': 
			if(file[i].size() > 1) write << file[i] << endl; 
			else 
			{
				write << endl << tab(braceMap) << file[i] << endl; 
				braceMap++; 
			}

			push = true; 
			break; 
			case '}': 
			braceMap--; 
			if(ripped) file[i] += ';'; 
			write << tab(braceMap) << file[i] << endl << endl; 
			break; 
			default: 
			if(push) 
			{
				write << tab(braceMap) << file[i] << " "; 
				push = false; 
			}

			else if(sameLine) write << file[i] << " "; 
			else 
			{
				write << tab(braceMap) << file[i] << " "; 
				sameLine = true; 
			}

			run++; 
			break; 
		}

		if(file[i][file[i].size() -1] == ';' || file[i][file[i].size() -1] == ':') 
		{
			write << endl; 
			sameLine = false; 
		}

	}

	read.close(); 
	write.close(); 
	return 0; 
}

