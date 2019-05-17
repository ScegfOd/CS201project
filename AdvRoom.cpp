#include "AdvRoom.h"



AdvRoom::AdvRoom()
{
}

bool AdvRoom::readRoom(ifstream &roomFile)
{
	has_been_visited = false;
	description.clear();
	number = 0;
	roomFile >> number;	//first get the room number
	if(number == 0){
		return false;
	}
	roomFile.ignore();	//then remove the dangling new line
	getline(roomFile, name); //get the name of the room
	do{//get description until the guard code
		description.push_back(string());
		getline(roomFile,description.back());
	}while(description.back() != "-----");
	description.pop_back();//then remove the guard code from the description

	stringstream move_line;
	string direction, keyname;
	int destination_number;
    getline(roomFile, direction);
    if(roomFile.eof())
        return false;
	do{
        move_line.clear();
		move_line.str(direction);
		keyname = "";//if the key isn't there, keyname will be reset to ""
		direction = "";
		move_line >> direction >> destination_number >> keyname;
		possible_moves.push_back(AdvMotionTableEntry(direction, destination_number, keyname));

        getline(roomFile, direction);
	}while(direction != "");//if the line is empty, direction will be the empty string
	return possible_moves.size() > 0;//failed read if it's the end of the file!
}

vector<string> AdvRoom::getDescription()
{
	return description;
}

string AdvRoom::getName()
{
	return name;
}

void AdvRoom::addObject(AdvObject obj)
{
	// This function should add the obj to the room.
	// It however, should not add the object to the room
	// if the room already contains the object.
	if(!containsObject(obj.getName()))
		items.push_back(obj);
}

AdvObject AdvRoom::removeObject(string objName)
{
	// This function should remove the object with objName.
	int i, max = items.size();
	for(i = 0; i < max; i++){
		if(objName == items.at(i).getName()){
			break;
		}
	}
	if(i == max)
		throw string("Error: cannot remove an item from a room that doesn't have said item.");
	AdvObject the_thing = items.at(i);
	//the erase method hates me, so
	items.at(i) = items.back();	//I'll shuffle the removed item to the now empty spot
	items.pop_back();			//and pop the last item off instead!
	return the_thing;
}

bool AdvRoom::containsObject(string objName)
{
	// Returns true if object with objName is in the room.
	for(auto item : items){
		if(objName == item.getName()){
			return true;
		}
	}
	return false;
}

int AdvRoom::objectCount()
{
	return items.size();
}

AdvObject AdvRoom::getObject(int index)
{
	return items[index];
}

bool AdvRoom::hasBeenVisited()
{
	return has_been_visited;
}

void AdvRoom::setVisited(bool flag)
{
	has_been_visited = flag;
}

vector<AdvMotionTableEntry> AdvRoom::getMotionTable()
{
	return possible_moves;
}


int AdvRoom::getRoomNumber()
{
	return number;
}
