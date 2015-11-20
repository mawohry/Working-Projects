#ifndef TOOLS_H_INCLUDED_
#define TOOLS_H_INCLUDED_
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#define RESET 0
using namespace std;

template<typename I> bool vectorFind(vector<I> input, I input2)
{
	for(unsigned int i=0;i<input.size();i++) if(input[i] == input2) return true;
	return false;
}

void vectorDisplay(vector<string> input, string title = "", bool space = false)
{
	cout << title << endl;
	for(unsigned int i=0;i<input.size();i++) cout << i+1 << ": " << input[i] << endl;
	if(space) cout << endl;
}

void vectorRemoveOrAdd(string object, vector<string>& _vector, bool remove)
{
	vector<string> new_vector;
	switch(remove)
	{
		case true:
		for(unsigned int i=0;i<_vector.size();i++) if(_vector[i] != object) new_vector.push_back(_vector[i]);
		_vector = new_vector;
		break;
		
		case false:
		_vector.push_back(object);
		break;
	}
}

bool remove_from(string value, vector<string>& vector_input)
{
	vector<string> newHold;
	bool retFlag = false;
	for(unsigned int i=0;i<vector_input.size();i++) 
	{
		if(vector_input[i] != value) newHold.push_back(vector_input[i]);
		else retFlag = true;
	}
	if(retFlag) vector_input = newHold;
	return retFlag;
}

bool give_to(string value, vector<string>& vector_input)
{
	short unsigned int oldsize = vector_input.size();
	vector_input.push_back(value);
	
	if(oldsize != vector_input.size()) return true;
	return false;
}

vector<string> seperate(string input, bool show = false)
{
	string temp;
	vector<string> ret;
	for(unsigned int i=0;i<input.size();i++)
	{
		if(input[i] == ' ')
		{
			ret.push_back(temp);
			temp.erase();
		} else temp += input[i];
	} ret.push_back(temp);
	
	if(show) cout << "Seperating: " << input << endl;
	return ret;
}

string to_lower(string input)
{
	string temp;
	for(unsigned int i=0;i<input.size();i++)
	{
		temp += tolower(input[i]);
	}
	return temp;
}

const int numEqui(string input)
{
	int wordNum = 0;
	for(unsigned int i=0;i<input.size();i++) wordNum += input[i];
	return wordNum;
}


#endif
