#include "tools.hpp"
using namespace std;

class WORLD
{
	public:
	vector<string> player_objects, world_objects, mission, mission_done;
	map<string, string> description;
	
	bool describe(string), missions(), player_had;
	void execute(string, string), successful(string, string, bool), engine(string);
	map<string, int> actions;
	unsigned int mission_count, mission_size;
	map<string, string> responses;
	map<string, bool> item_state;
	
	WORLD();
};

WORLD::WORLD()
{
	mission_count =  0;
	player_had = false;
	mission_size = 0;
	
	ifstream readfile("world.txt");
	string temp, temp2;
	vector<string> file;
	
	while(readfile >> temp) file.push_back(temp);
	temp.erase();
	
	for(unsigned int i=0;i<file.size();i++)
	{
		//locate ##OBJECTS##
		//find : take one step back and store object, then continue to store description while ## is not found
		if(file[i] == "##OBJECTS##")
		{
			for(unsigned int j=i+1;j<file.size();j++)
			{
				if(file[j] == ":" || file[j] == ">")
				{
					if(file[j] == ":") world_objects.push_back(file[j-1]);
					else if(file[j] == ">") player_objects.push_back(file[j-1]);
					temp2 = file[j-1];
					for(unsigned int k=j+1;k<file.size();k++)
					{
						if(file[k] == "##")
						{
							description.insert(make_pair(temp2, temp));
							temp.erase();
							break;
						} else {
							if(!temp.empty()) temp += " ";
							temp += file[k];
						}
					}
				}
			}
		} else if(file[i] == "##MISSION##")
		{
			temp.erase();
			for(unsigned int j=i+1;j<file.size();j++) 
			{
				for(unsigned int k=j;file[k] != "##MISSIONEND##"; k++) 
				{
					if(file[k] == "##") 
					{
						mission.push_back(temp);
						temp.erase();
					}
					else 
					{
						if(temp.size() != 0) temp += " ";
						temp += file[k];
					}
				}
				break;
			}
		}
	}
	
	mission_size = mission.size();
	readfile.close();
	
	for(unsigned int i=0;i<mission.size();i++) 
	item_state.insert(make_pair(seperate(mission[i])[1], vectorFind(player_objects, seperate(mission[i])[1])));
	
	responses.insert(make_pair("take", "taken"));
	responses.insert(make_pair("pick", "picked"));
	responses.insert(make_pair("keep", "kept"));
	responses.insert(make_pair("put", "kept"));
	actions.insert(make_pair("describe", 4));
	
	actions.insert(make_pair("pick", 2));
	actions.insert(make_pair("take", 2));
	
	actions.insert(make_pair("keep", 1));
	actions.insert(make_pair("put", 1));
}

void WORLD::successful(string action, string object, bool success)
{
	if(success) 
	{
		cout << object << " " << responses[action] << " successfully..." << endl;
		switch(actions[action])
		{
			case 1:
			item_state[object] = false;
			break;
			
			case 2:
			item_state[object] = true;
			break;
			
			default:
			cout << "Error in determining item state..." << endl;
			break;
		}
	}
	else cout << object << " not " << responses[action] << endl;
}

bool WORLD::describe(string object)
{	
	if(description.find(object) != description.end()) 
	{
		cout << description[object] << endl;
		return true;
	}
	return false;
}

void WORLD::execute(string action, string object)
{
	if(action == "show")
	{
		if(object == "pocket" || object == "hands") 
		{
			string edited_object = "- " + object + " -";
			if(!player_objects.empty()) vectorDisplay(player_objects, edited_object, true);
			else cout << "No objects found in player's keep..." << endl;
		}
		else if(object == "world") 
		{
			if(!world_objects.empty()) vectorDisplay(world_objects, " - World - ", true);
			else cout << "No object found in world..." << endl;
		}
		else if(object == "mission")
		{
			if(!mission.empty()) vectorDisplay(mission, "~ mission ~", true);
			else cout << "All missions accomplished for this level..." << endl;
		}
		else cout << "Can't show that object..." << endl;
	}
	else switch(actions[action])
	{
		case 4:
		if(!describe(object)) cout << "Command can't be described!" << endl;
		break;
		
		case 2:
		if(remove_from(object, world_objects)) 
		{
			if(give_to(object, player_objects)) successful(action, object, true);
		}
		else cout << "There is no " << object << " in the world!" << endl;
		break;
		
		case 1:
		if(remove_from(object, player_objects)) 
		{
			if(give_to(object, world_objects)) successful(action, object, true);
		}
		else cout << "There is no " << object << " in players keep!" << endl;
		break;
		
		default:
		cout << "Command not understood..." << endl;
	}
}

void WORLD::engine(string input)
{
	cout << "Sims ~ Universe!!" << endl << endl;
	vector<string> command = seperate(input);
	vector<string> in_actions, in_objects;
	switch(command.size())
	{
		case 4:
		in_actions.push_back(command[2]);
		in_objects.push_back(command[3]);
		case 2:
		in_actions.push_back(command[0]);
		in_objects.push_back(command[1]);
		break;
		
		default:
		in_actions.push_back("describe");
		in_objects.push_back(command[0]);
		break;
	}
	
	for(unsigned int i=0;i<in_actions.size();i++) execute(in_actions[i], in_objects[i]);
}

bool WORLD::missions()
{
	//key words: take, player, objects
	for(unsigned int i=0;i<mission.size();i++)
	{
		vector<string> mission_temp = seperate(mission[i]);

		switch(actions[mission_temp[0]])
		{	
			case 1:
			if(!item_state[mission_temp[1]]) 
			{
				mission_count++;
				vectorRemoveOrAdd(mission[i], mission, true);
				i--;
			}
			break;
			
			case 2:
			if(item_state[mission_temp[1]]) 
			{
				mission_count++;
				vectorRemoveOrAdd(mission[i], mission, true);
				i--;
			}
			break;
		}
	}
	if(mission_count == mission_size) return true;
	
	return false;
}
