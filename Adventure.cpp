#include "Adventure.h"
#include <sstream>
/*
* File: Adventure.cpp
* --------------------
* This program plays the Adventure game.
*/

Adventure::Adventure()
{
	Setup();
}

Adventure::Adventure(string objfile, string rmfile, string cmdfile){
	// Setup of the Adventure game using some files.
	Setup();
	//cout<<"the constructor was called\n";
	LoadRooms(rmfile);
	//cout<<"well, the rooms loaded\n";
	LoadObjects(objfile);
	//cout<<"well, the objects loaded\n";
	LoadSynonyms(cmdfile);
	//cout<<"well, the synonyms loaded\n";
}

void Adventure::Setup(){
    current_room = 1;
	rooms.push_back(AdvRoom());//room 0, the winnin' room and backpack!
}

void Adventure::Play(){
	string cmd, objName;
	bool print_room = true;
	while (current_room != 0) {
        if(print_room){
            if(rooms.at(current_room).hasBeenVisited()){
                cout << rooms[current_room].getName() << endl;
            }else{
                PrintRoom();
            }
        }
		if(IsForced()){
			rooms.at(current_room).setVisited(false);
			print_room = MotionCmd("FORCED");
			continue;
		}

		GetUserCmd(cmd, objName);
		print_room = false;
		if ("QUIT" == cmd) {
			QuitCmd();
			cout << "Goodbye!" << endl;
			return;
		}else if ("HELP" == cmd){
			HelpCmd();
		}else if ("INVENTORY" == cmd){
			Inventory();
		}else if ("LOOK" == cmd){
			rooms.at(current_room).setVisited(false);
			print_room = true;
		}else if ("TAKE" == cmd){
			Take(objName);
		}else if ("DROP" == cmd){
			Drop(objName);
		}else{//some kind of movement!?
			print_room = MotionCmd(cmd);
		}
	}

	cout << "Goodbye!" << endl;
}


void Adventure::Inventory(){
	cout << "In your backpack, you have:\n";
	int i = rooms.at(0).objectCount();
	if(i){
		while(i > 0)
			cout << rooms.at(0).getObject(--i).getDescription() << ", ";
		cout <<"and nothing else.\n";
	}
	else
		cout << "Nothing at all! You're supposed to be a kleptomaniac! Get to it!\n";
}
void Adventure::Take(string item){
    if(rooms.at(current_room).containsObject(item)){
        rooms.at(0).addObject( rooms.at(current_room).removeObject(item) );
		cout << "You've taken the " << item << ".\n";
    }else{
        cout << "Are you sure that this room has " << item << "?\n(try \"LOOK\" command)\n";
	}
}
void Adventure::Drop(string item){
    if(rooms.at(0).containsObject(item)){//then move the item!
        rooms.at(current_room).addObject( rooms.at(0).removeObject(item) );
		cout << "You've dropped the " << item << ".\n";
    }else{
		cout << "Are you sure you have any " << item << " in your inventory?\n(try \"INVENTORY\" command)\n";
	}
}

void Adventure::GetUserCmd(string &verb, string &obj){
	cout << "> ";
	string line;
	getline(cin, line);
	stringstream a_stream(line);
	a_stream >> verb;

	// Add code here to figure out the verb and object from the line
	verb = GetSynonym(verb);
	a_stream >> obj;
	obj = GetSynonym(obj);
}


bool Adventure::IsForced(){
	for(auto entry : rooms.at(current_room).getMotionTable()){
		if("FORCED" == entry.getDirection()){
			return true;
		}
	}
	return false;
}

void Adventure::PrintRoom(){
	//print out the room descripton
	for(string a_line : rooms[current_room].getDescription()){
		cout << a_line << endl;
	}
	//check for items and print those out too
	for(int i = rooms.at(current_room).objectCount(); i > 0; ){
		cout << "There is " << rooms.at(current_room).getObject(--i).getDescription() << endl;
	}
	rooms[current_room].setVisited(true);
}

bool Adventure::MotionCmd(string motion){
	// Get the motion table of the room number where the player is currently.
	// For each table entry, check to see if there is an entry that matches
	// "motion".  If the entry matches, check if the motion requires
	// a key and if the player has the has the key. A successful match
	// moves the player into the destination room.
	bool motion_found = false;
	string key;
	for(AdvMotionTableEntry motion_table_entry : rooms.at(current_room).getMotionTable()){
		if(motion_table_entry.getDirection() == motion){
			key = motion_table_entry.getKeyName();
			motion_found = (key == "" || rooms.at(0).containsObject(key));
			if(motion_found){
				current_room = motion_table_entry.getDestinationRoom();
				break;
			}
		}
	}
	if(!motion_found){
		cout << "Does \"" << motion << "\" really make sense in this room?\n(type \"HELP\" without quotes for help)\n";
	}
	return motion_found;
}

void Adventure::LoadObjects(string filename){
	// Should load all the objects from a file.
	ifstream data_file;
	data_file.open(filename);
	if(!data_file.is_open()){
		string angry_red_text = "Error: the " + filename + " file didn't open! AT ALL!\n";
		cout << angry_red_text;
		cerr << angry_red_text;
        throw angry_red_text;
	}
	AdvObject *an_object = new AdvObject();
	while (an_object->readObject(data_file)) {
		rooms.at(an_object->getInitialLocation()).addObject(*an_object);  // Add to vector
		delete an_object;
		an_object = new AdvObject();
	}
	delete an_object;
    data_file.close();//closes when it goes out of scope, but w/e

}

void Adventure::LoadRooms(string filename){
	// Should load all rooms from a file
	ifstream data_file;
	data_file.open(filename);
	if(!data_file.is_open()){
		string angry_red_text = "Error: the " + filename + " file didn't open! AT ALL!\n";
		cout << angry_red_text;
		cerr << angry_red_text;
        throw angry_red_text;
	}
	AdvRoom *a_room = new AdvRoom();
	while (a_room->readRoom(data_file)) {
		rooms.push_back(*a_room);  // Add to vector
		delete a_room;
		a_room = new AdvRoom();
	}
	delete a_room;
    data_file.close();//closes when it goes out of scope, but w/e
}

void Adventure::LoadSynonyms(string filename){
	// Should load all synonyms from a file.
	ifstream data_file;
	data_file.open(filename);
	if(!data_file.is_open()){
		string angry_red_text = "Error: the " + filename + " file didn't open! AT ALL!\n";
		cout << angry_red_text;
		cerr << angry_red_text;
        throw angry_red_text;
	}
    Synonym a_word_pair;
	while (data_file >> a_word_pair.synonym >> a_word_pair.word) {
		synonyms.push_back(a_word_pair);  // Add to vector
	}
    data_file.close();//closes when it goes out of scope, but w/e
}

/*
 * Returns a synonym if one exists.  Otherwise returns original word.
 */
string Adventure::GetSynonym(string word){
	ConvertToUpper(word);
	for(auto syn : synonyms){
		if(syn.synonym == word)
			return syn.word;
	}
	return word;
}


void Adventure::QuitCmd(){
	// Ask if the uses would like to quit.  Should only take a yes or no.
	while (true) {
		string ans;
		cout << "Are you sure you want to quit now? ";
		getline(cin, ans);
		ConvertToUpper(ans);
		if (ans == "Y" || ans == "YES") {
			current_room = 0;
			break;
		}
		if (ans == "N" || ans == "NO") {
			break;
		}
		cout << "Please answer yes or no." << endl;
	}
}

void Adventure::HelpCmd(){
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
