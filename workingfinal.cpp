// final.cpp
// Austin Horn, CISP 360
// 5/??/23

#include <iostream>
#include <string>
#include <limits> // for numeric_limits in the cin.ingore parameters

using namespace std;

void pause();
string getname();
void ProgramGreeting();
void story(string);

struct InteractableNoun {
	string name; 
	string description;

	//default constructor
	InteractableNoun() {
		name = "";
		description = "";
	}

	//parameterized constructor
	InteractableNoun(const string& objName, const string& desc) {
		name = objName;
		description = desc;
	}
};

struct Room {
	//using the name as the id, reduces code
	string name;
	string description;
	InteractableNoun* objs; //after this is functional, can copy to make dynamic monsters, and dy
	int numObjs;
	//using pointers to connected rooms
	Room* north;
	Room* south;
	Room* east;
	Room* west;
	//spawn a monster if room is occupied and not visited
	bool visited;
	bool occupied;
	bool northLocked;
	bool southLocked;
	bool eastLocked;
	bool westLocked;
	//constructor
	Room(const string& roomName, const string& desc) {
		name = roomName;
		description = desc;
		north = nullptr;
		south = nullptr;
		east = nullptr;
		west = nullptr;
		objs =  nullptr;
		numObjs = 0;
		visited = false;
		occupied = false;
		northLocked = false;
		southLocked = false;
		eastLocked = false;
		westLocked = false;
	}
};

/* add later
struct Player {
	string name;
	InteractableNoun* obj;
	int numObjs;
};
*/

void roomConnect(Room*, Room*, char, bool);
void setLockStatus(Room*, char, bool);
void displayRoomInfo(Room*);

void addObjToRoom(Room*, const InteractableNoun&);
/* to add
void removeObjFromRoom;
void addObjToPlayer;
void removeObjFromPlayer;
*/
int main() {
	
	//greeting and getting users name
	ProgramGreeting();
	string name = getname();
	story(name);

	//making rooms
	Room* RoomOne = new Room("Invasion Point", "A breach in the outer defenses of Constructis. The surroundings show signs of battle, with damaged walls and debris.");
	Room* RoomTwo = new Room("Builderian Guard Barracks", "A fortified room where Builderian soldiers rest and prepare for battle.");
	Room* RoomThree = new Room("Training Grounds", "A large courtyard where Builderian soldiers practice combat and tactics.");
	Room* RoomFour = new Room("Technology Storage", "This secured room is filled with weapons and ammunition.");
	Room* RoomFive = new Room("Patrol Route", "A long hallway with multiple intersections, where guards regularly patrol.");
	Room* RoomSix = new Room("Security Room", "A high-tech room containing surveillance equipment that controls and monitors Contructis.");
	Room* RoomSeven = new Room("Bridge of Sacrifice", "A narrow bridge over a deep chasm, guarded by a powerful Builderian sentinel.");
	Room* RoomEight = new Room("Library of Schematics", "A vast repository of blueprints, schematics, and plans.");
	Room* RoomNine = new Room("Constructari Archives", "A secure valut containing sensitive information and relics.");
	Room* RoomTen = new Room("Hall of Innovation", "A museum-like space displaying groundbreaking inventions and architectural marvels.");
	Room* RoomEleven = new Room("Builder Living Quarters", "A residential area where inhabitants of Constructis reside.");
	Room* RoomTwelve = new Room("Labyrinth of Mechanics", "A complex maze of traps and hidden dangers.");
	Room* RoomThirteen = new Room("The Great Workshop", "A large, open space filled with workstations and tools for crafting and constructing.");
	Room* RoomFourteen = new Room("Materials Yard", "A bustiling area where raw materials are stored and processed.");
	Room* RoomFifteen = new Room("Builder's Sanctuary", "A serene garden with monuments dedicated to Bob, the Builder, and the Constructari Order.");
	Room* RoomSixteen = new Room("The Grand Architect's Chambers", "The private quarters of the Grand Architect and his elite Builderian Gaurd.");
	Room* RoomSeventeen = new Room("The Oracle's Sanctum", "The final room, home to the Great Oracle of Bob. There is a special android sentinel force proctecting its highness.");

	//connecting rooms
	roomConnect(RoomOne, RoomTwo, 's', false); // RoomTwo south of RoomOne, not locked
	roomConnect(RoomOne, RoomSix, 'e', true);
	roomConnect(RoomTwo, RoomThree, 'e', false);
	roomConnect(RoomThree, RoomFour, 'e', false);
	roomConnect(RoomThree, RoomSix, 'n', true);
	roomConnect(RoomFour, RoomFive, 'n', false);
	roomConnect(RoomFive, RoomSix, 'w', false);
	roomConnect(RoomFive, RoomEleven, 'e', true);
	roomConnect(RoomSix, RoomSeven, 'n', false);
	roomConnect(RoomSeven, RoomEight, 'n', false);
	roomConnect(RoomEight, RoomNine, 'w', false);
	roomConnect(RoomEight, RoomTen, 'n', false);
	roomConnect(RoomEleven, RoomTwelve, 'n', false);
	roomConnect(RoomEleven, RoomSeventeen, 'e', true);
	roomConnect(RoomTwelve, RoomThirteen, 'n', false);
	roomConnect(RoomThirteen, RoomFourteen, 'e', false);
	roomConnect(RoomThirteen, RoomFifteen, 'n', false);
	roomConnect(RoomFifteen, RoomSixteen, 'n', false);

	//placing objects in rooms
	
	addObjToRoom(RoomOne, InteractableNoun("key", "key somewhere"));
	addObjToRoom(RoomTwo, InteractableNoun("blah", "vlah someplace"));
	addObjToRoom(RoomThree, InteractableNoun("tree", "tree some pear"));


	//initialize position on map
	Room* currentRoom = RoomOne;
	

	//game loop
	char input;
	while (true) {
		//set room to occupied
		currentRoom->occupied = true;

		//output current room name, description if not visited, else output name
		if (currentRoom->visited != true) {
			cout << endl << currentRoom->name << ": " << endl << currentRoom->description << endl << endl;
			
			//set visited false
			currentRoom->visited = true;
		} else {
			cout << endl << currentRoom->name << endl << endl;
		}

		
		//
		
		//available rooms
		displayRoomInfo(currentRoom);


		//directional input exit codes, game exit codes, look code
		cout << "Enter direction (n, s, e, w) to go towards," << endl;
		cout << "or (l) to look around," << endl;
	        cout << "or type (x) to quit: ";
		cin >> input;

		// clear rest of the input buffer, this cin.ignore works best
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//tolower so uppercase input  will work as well
		input = tolower(input);
		
		//game exit
		if (input == 'x') {
			break;
		}
		
		//look around
		if (input == 'l') {
			cout << endl << currentRoom->description << endl;
			//output objs desc in room, if any
			for (int i = 0; i < currentRoom->numObjs; i++) {
			cout << currentRoom->objs[i].description << endl << endl;
			}
			continue;
		}



		//direction logic+input validation with available rooms
		Room* nextRoom = nullptr;
	
		if (input == 'n' && currentRoom->north && currentRoom->northLocked != true) {
			nextRoom = currentRoom->north;
		} else if (input == 's' && currentRoom->south && currentRoom->southLocked !=true) {
			nextRoom = currentRoom->south;
		} else if (input == 'e' && currentRoom->east && currentRoom->eastLocked != true) {
			nextRoom = currentRoom->east;
		} else if (input == 'w' && currentRoom->west && currentRoom->westLocked != true) {
			nextRoom = currentRoom->west;
		} else if (input == 'n' && currentRoom->north && currentRoom->northLocked != false) {
			cout << "\nThis room is locked..." << endl;
			continue;
		} else if (input == 's' && currentRoom->south && currentRoom->southLocked !=false) {
			cout << "\nThis room is locked..." << endl;
			continue;
		} else if (input == 'e' && currentRoom->east && currentRoom->eastLocked != false) {
			cout << "\nThis room is locked..." << endl;
			continue;
		} else if (input == 'w' && currentRoom->west && currentRoom->westLocked != false) {
			cout << "\nThis room is locked..." << endl;
		} else {
			cout << "\nThere is nothing that way..." << endl;
			continue;
		}
		
		//set current room to unoccopied, then go to next room
		currentRoom->occupied = false;
		currentRoom = nextRoom;
	
	}
	
	//the below will prob change if adding player struct with inventory for interactable items
	//free up the allocated memory for objs[] and rooms
	delete[] RoomOne->objs;
	delete RoomOne;
	delete[] RoomTwo->objs;
	delete RoomTwo;
	delete[] RoomThree->objs;
	delete RoomThree;
	delete[] RoomFour->objs;
	delete RoomFour;
	delete[] RoomFive->objs;
	delete RoomFive;
	delete[] RoomSix->objs;
	delete RoomSix;
	delete[] RoomSeven->objs;
	delete RoomSeven;
	delete[] RoomEight->objs;
	delete RoomEight;
	delete[] RoomNine->objs;
	delete RoomNine;
	delete[] RoomTen->objs;
	delete RoomTen;
	delete[] RoomEleven->objs;
	delete RoomEleven;
	delete[] RoomTwelve->objs;
	delete RoomTwelve;
	delete[] RoomThirteen->objs;
	delete RoomThirteen;
	delete[] RoomFourteen->objs;
	delete RoomFourteen;
	delete[] RoomFifteen->objs;
	delete RoomFifteen;
	delete[] RoomSixteen->objs;
	delete RoomSixteen;
	delete[] RoomSeventeen->objs;
	delete RoomSeventeen;

	return 0;
}

void pause() {
	char c;
	cout << "Press any key to continue... ";
	cin >> c;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	cout << endl;
}

string getname() {
	string name;
	char c;
	//get name loop
	
	while(true) {
		
		cout << "Enter name: ";
		cin >> name;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//validate and check for empty input
		if (!name.empty()) {
			cout << name << "? Is this correct? (y/n) ";
			cin >> c;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			c = tolower(c);

			if (c == 'y') {
				cout << "OK";
				break;
			} else if (c == 'n') {
				continue;
			}else {
			
			}

		}
		cout << "Invalid input. Please try again." << endl;
	}


	return name;
}

void ProgramGreeting() {
	// system time
	time_t timenow = time(NULL);
	tm *ltm = localtime(&timenow);

	//date output
	cout << "Date: " << 1 + ltm->tm_mon << '/' << ltm->tm_mday << '/' << 1900 + ltm->tm_year << endl; 


}

void story(string name) {
	
	//input loop
	while(true) {
		cout << " " <<  name << ", would you like to hear the story? (y/n) " << endl;
		char choose;
		cin >> choose;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
		if (choose == 'y') {


			cout << "North of Wales, in the Hewitt Highlands of Snowdonia, there exists an independent city-state known as Constructis, home to the followers of the esteemed prophet, Bob, the Builder." << endl;
			pause();
			cout << "The Temple of Constructis, now in the year 1423 AC (Anno Constructoris), continues to thrive in its sacred city. It remains separate from the United Britannia Empire and is governed by the ecclesiastical authority of the Builderian Order, which owes its allegiance to the teachings of Bob, the Builder." << endl;
			pause();
			cout << "The once-noble order, rooted in faith, compassion, and technology, has become corrupted, using its knowledge to exploit the earth's natural resources and causing suffering to the people outside its borders." << endl;
			pause();
			cout << "As the United Britannia Empire and the rest of the world struggle to survive, a desperate plan is put into motion: you, " << name << ", are a special soldier trained from youth by the Shadow Masons, a group of ex-Builderian elders, to infiltrate and destroy the order to which they once swore allegiance." << endl;
			pause();
			cout << "They have mentored you in the secret teachings of the Constructari, and you alone have the knowledge to end their destructive reign of terror. By wielding the technologies they have kept secret, you are the world's only hope." << endl;
			pause();
			break;
		} else if (choose == 'n') {
			cout << "..." << endl;
			pause();
			break;
		}
		cout << "Invalid..." << endl;
	}
	
}



void roomConnect(Room* a, Room* b, char direction, bool locked) {
	if (direction == 'n') {
		a->north = b;
		b->south = a;
		a->northLocked = locked;
		b->southLocked = locked;
	} else if (direction == 's') {
		a->south = b;
		b->north = a;
		a->southLocked = locked;
		b->northLocked = locked;
	} else if (direction == 'e') {
		a->east = b;
		b->west = a;
		a->eastLocked = locked;
		b->westLocked = locked;
	} else if (direction == 'w') {
		a->west = b;
		b->east = a;
		a->westLocked = locked;
		b->eastLocked = locked;
	}
}

void changeLockStatus(Room* room, char direction, bool locked) {
	if (direction == 'n') {
		room->northLocked = locked;
	} else if (direction == 's') {
		room->southLocked = locked;
	} else if (direction == 'e') {
		room->eastLocked = locked;
	} else if (direction == 'w') {
		room->westLocked = locked;
	}
}

void displayRoomInfo(Room* currentRoom) {
	cout << "Available rooms:" << endl;
	if (currentRoom->north != nullptr) {
		cout << "North: " << currentRoom->north->name;
		if (currentRoom->northLocked == true) {
			cout << " - LOCKED";
		}
		cout << endl;
	}
	if (currentRoom->south != nullptr) {
		cout << "South: " << currentRoom->south->name;
		if (currentRoom->southLocked == true) {
			cout << " - LOCKED";
		}
		cout << endl;
	}
	if (currentRoom->east != nullptr) {
		cout << "East: " << currentRoom->east->name;
		if (currentRoom->eastLocked == true) {
			cout << " - LOCKED";
		}
		cout << endl;
	}
	if (currentRoom->west != nullptr) {
		cout << "West: " << currentRoom->west->name;
		if (currentRoom->westLocked == true) {
			cout << " - LOCKED";
		}
		cout << endl;
	}
	cout << endl;
}


void addObjToRoom(Room* room, const InteractableNoun& obj) {
	
	//allocate new array of objs
	InteractableNoun* newObjs = new InteractableNoun[(room->numObjs) + (1)];
	
	//copy them to objs in room
	for (int i = 0; i < room->numObjs; i++)
		newObjs[i] = room->objs[i];

	//set new element to new obj
	newObjs[room->numObjs] = obj;
	
	//get rid of old array and copy over new
	delete[] room->objs;
	room->objs = newObjs;
	//set num of objs to new amount
	room->numObjs++;
}
