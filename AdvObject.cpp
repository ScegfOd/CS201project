#include "AdvObject.h"

AdvObject::AdvObject()
{
}

AdvObject::AdvObject(string objName, string objDes, int loc)
{
	name = objName;
	description = objDes;
	initial_room_number = loc;
}

bool AdvObject::readObject(ifstream &objFile)
{
	// True if able to read name,
	// description, and initial location.
	// Otherwise returns false.
	name = "";
	objFile >> name;
	objFile.ignore();
	getline(objFile, description);
	objFile >> initial_room_number;
	return name != "";
}

string AdvObject::getName()
{
	return name;
}

string AdvObject::getDescription()
{
	return description;
}

int AdvObject::getInitialLocation()
{
	return initial_room_number;
}
