#include "AdvRoom.h"



AdvRoom::AdvRoom()
{

}

bool AdvRoom::readRoom(ifstream &roomFile)
{
	
}

vector<string> AdvRoom::getDescription()
{
	
}

string AdvRoom::getName()
{
	
}

void AdvRoom::addObject(AdvObject obj)
{
	// This function should add the obj to the room.
	// It however, should not add the object to the room
	// if the room already contains the object.
}

AdvObject AdvRoom::removeObject(string objName)
{
	// This function should remove the object with objName.

}

bool AdvRoom::containsObject(string objName)
{
	// Returns true if object with objName is in the room.
}

int AdvRoom::objectCount()
{
	
}

AdvObject AdvRoom::getObject(int index)
{
	
}

bool AdvRoom::hasBeenVisited()
{
	
}

void AdvRoom::setVisited(bool flag)
{
	
}

vector<AdvMotionTableEntry> AdvRoom::getMotionTable()
{
	
}


int AdvRoom::getRoomNumber()
{
	return rmNum;
}
