#include "Adventure.h"

/*
* File: Adventure.cpp
* --------------------
* This program plays the Adventure game.
*/

Adventure::Adventure()
{

}

Adventure::Adventure(string objfile, string rmfile, string cmdfile)
{
	// Setup of the Adventure game using some files.

}

void Adventure::Play()
{

	while (currRoomInd != 0) {
		string cmd, objName;
		GetUserCmd(cmd, objName);
		if (cmd == "QUIT") {
			QuitCmd();
			cout << "Goodbye!" << endl;
			return;
		}
		else if (cmd == "HELP") {
			HelpCmd();
		}
		// The rest of the commands go here.
	}

	cout << "Goodbye!" << endl;
}


void Adventure::GetUserCmd(string &verb, string &obj)
{
	string cmdOrg = verb;
	
	cout << "> ";
	string line;
	getline(cin, line);
	
	// Add code here to figure out the verb and object from the line

}

int Adventure::MotionCmd(string motion)
{
	// Get the motion table of the room number where the player is currently.
	// For each table entry, check to see if there is an entry that matches
	// "motion".  If the entry matches, check if the motion requires
	// a key and if the player has the has the key. A successful match
	// moves the player into the destination room.
	
	return -1;
}

void Adventure::LoadObjects(string filename)
{
	// Should load all the objects from a file.

}

void Adventure::LoadRooms(string filename)
{
	// Should load all rooms from a file

}

void Adventure::LoadSynonyms(string filename)
{
	// Should load all synonyms from a file.

}

/*
 * Returns a synonym if one exists.  Otherwise returns original word.
 */
string Adventure::GetSynonym(string word)
{
	ConvertToUpper(word);


	return word;
}


void Adventure::QuitCmd()
{
	// Ask if the uses would like to quit.  Should only take a yes or no.
	while (true) {
		string ans;
		cout << "Are you sure you want to quit now? ";
		getline(cin, ans);
		ConvertToUpper(ans);
		if (ans == "Y" || ans == "YES") {
			currRoomInd = 0;
			break;
		}
		if (ans == "N" || ans == "NO") {
			break;
		}
		cout << "Please answer yes or no." << endl;
	}
}

void Adventure::HelpCmd()
{
	cout << "Welcome to Adventure!" << endl;
	cout << "Somewhere nearby is Colossal Cave, where others have found fortunes in" << endl;
	cout << "treasure and gold, though it is rumored that some who enter are never" << endl;
	cout << "seen again. Magic is said to work in the cave.I will be your eyes" << endl;
	cout << "and hands. Direct me with natural English commands; I don't understand" << endl;
	cout << "all of the English language, but I do a pretty good job." << endl << endl;

	cout << "It's important to remember that cave passages turn a lot, and that" << endl;
	cout << "leaving a room to the north does not guarantee entering the next from" << endl;
	cout << "the south, although it often works out that way. You'd best make yourself" << endl;
	cout << "a map as you go along." << endl << endl;

	cout << "Much of my vocabulary describes places and is used to move you there." << endl;
	cout << "To move, try words like IN, OUT, EAST, WEST, NORTH, SOUTH, UP, or DOWN." << endl;
	cout << "I also know about a number of objects hidden within the cave which you" << endl;
	cout << "can TAKE or DROP.To see what objects you're carrying, say INVENTORY." << endl;
	cout << "To reprint the detailed description of where you are, say LOOK.If you" << endl;
	cout << "want to end your adventure, say QUIT." << endl;
}