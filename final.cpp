// final.cpp
// Austin Horn, CISP 360
// 5/??/23

#include <iostream>
#include <string>
#include <limits> // for numeric_limits in the cin.ingore parameters

using namespace std;

void pause();
string getname();
void story(string);
void ProgramGreeting();

struct InteractableNoun {
	string name; 
	string description;
	bool flag;
	//default constructor
	InteractableNoun() {
		name = "";
		description = "";
		flag = false;
	}

	//parameterized constructor
	InteractableNoun(const string& objName, const string& desc, bool flag) {
		name = objName;
		description = desc;
		flag = flag;
	}
};

struct KeyItem {
	string name; 
	string description;
	
	KeyItem() {
		name = "";
		description = "";
	}
	KeyItem(const string& objName, const string& desc) {
		name = objName;
		description = desc;
	}
};

struct Armor {
	string name;
	int defense;
	string description;
	Armor(){
		name = "";
		defense = 0;
		description = "";
	}
	Armor(const string& name, const int df, const string& desc){
		name = name;
		defense = df;
		description = desc;
	}

}

struct Weapon {
	string name;
	int damage;
	string description;
	Weapon(){
		name = "";
		damage = 0;
		description = "";
	}
	Weapon(const string& name, const int dmg, const string& desc){
		name = name;
		damage = dmg;
		description = desc;
	}
}

struct Inventory {
	Weapon* weapon;
	Armor* armor;
	KeyItem* keys;
	int numKeys;
	Inventory() {
		weapon = nullptr;
		armor = nullptr;
		keys = nullptr;
		numKeys = 0;
	} 
}

struct Player {
	int health;
	Inventory* inv;
}

struct Enemy {
	string name; 
	int health;
	string description;
	Inventory* inv;
	Enemy() {
		name = "";
		description = "";
		health = 0;
		inv = nullptr;
	}
	Enemy(const string& objName, const string& desc, int hp) {
		name = objName;
		description = desc;
		health = hp;
		inv = nullptr;
	}
};

struct Room {
	//using the name as the id, reduces code
	string name;
	string description;
	InteractableNoun* objs;
	KeyItem* keys;
	Enemy* enemies;
	Weapon* weapons;
	Armor* armors;
	int numObjs;
	int numKeys;
	int numEnemies;
	int numWeapons;
	int numArmors;
	//using pointers to connected rooms
	Room* north;
	Room* south;
	Room* east;
	Room* west;
	//spawn a monster if room is dark, occupied, and not visited
	bool visited;
	bool occupied;
	bool dark;
	bool northLocked;
	bool southLocked;
	bool eastLocked;
	bool westLocked;
	//constructor
	Room(const string& roomName, const string& desc, bool darkQ) {
		name = roomName;
		description = desc;
		dark = darkQ;
		north = nullptr;
		south = nullptr;
		east = nullptr;
		west = nullptr;
		objs =  nullptr;
		keys = nullptr;
		enemies = nullptr;
		numObjs = 0;
		numKeys = 0;
		numEnemies = 0;
		numWeapons = 0;
		numArmors = 0;
		visited = false;
		occupied = false;
		northLocked = false;
		southLocked = false;
		eastLocked = false;
		westLocked = false;
	}

};

void roomConnect(Room* , Room*, char, bool);
void setLockStatus(Room*, char, bool);
void displayRoomInfo(Room*);

void addObjToRoom(Room*, const InteractableNoun&);
void addEnemiesToRoom(Room*, const Enemy&);

//add to room
void addKey(Room*, const KeyItem&);
void addWeapon(Room*, const Weapon&);
void addArmor(Room*, const Armor&);

//add to inv
void addKey(Inv*, const KeyItem&);
void addWeapon(Inv*, const Weapon&);
void addArmor(Inv*, const Armor&);

//take from room
void TakeKey(Inv*, Room*, const KeyItem&);
//take from inv
void TakeKey(Inv*, Inv*, const KeyItem&);

// inv-room swap
void SwapWeapon(Inv*, Room*, const Weapon&);
void SwapArmor(Inv*, Room*, const Armor&);
// inv-inv swap
void SwapWeapon(Inv*, Inv*, const Weapon&);
void SwapArmor(Inv*, Inv*, const Armor&);

int main() {
	
	//greeting and getting users name
	ProgramGreeting();
	string name = getname();
	
	//story
	story(name);


	//making rooms
	Room* RoomOne = new Room("Invasion Point", "A breach in the outer defenses of Constructis. The surroundings show signs of battle, with damaged walls and debris.", false);
	Room* RoomTwo = new Room("Builderian Guard Barracks", "A fortified room where Builderian soldiers rest and prepare for battle.", true);
	Room* RoomThree = new Room("Training Grounds", "A large courtyard where Builderian soldiers practice combat and tactics.", true);
	Room* RoomFour = new Room("Technology Storage", "This secured room is filled with weapons and ammunition.", true);
	Room* RoomFive = new Room("Patrol Route", "A long hallway with multiple intersections, where guards regularly patrol.", true);
	Room* RoomSix = new Room("Security Room", "A high-tech room containing surveillance equipment that controls and monitors Contructis.", true);
	Room* RoomSeven = new Room("Bridge of Sacrifice", "A narrow bridge over a deep chasm, guarded by a powerful Builderian sentinel.", true);
	Room* RoomEight = new Room("Library of Schematics", "A vast repository of blueprints, schematics, and plans.", false);
	Room* RoomNine = new Room("Constructari Archives", "A secure valut containing sensitive information and relics.", true);
	Room* RoomTen = new Room("Hall of Innovation", "A museum-like space displaying groundbreaking inventions and architectural marvels.", true);
	Room* RoomEleven = new Room("Builder Living Quarters", "A residential area where inhabitants of Constructis reside.", true);
	Room* RoomTwelve = new Room("Labyrinth of Mechanics", "A complex maze of traps and hidden dangers.", false);
	Room* RoomThirteen = new Room("The Great Workshop", "A large, open space filled with workstations and tools for crafting and constructing.", true);
	Room* RoomFourteen = new Room("Materials Yard", "A bustiling area where raw materials are stored and processed.", true);
	Room* RoomFifteen = new Room("Builder's Sanctuary", "A serene garden with monuments dedicated to Bob, the Builder, and the Constructari Order.", true); 
	Room* RoomSixteen = new Room("The Grand Architect's Chambers", "The private quarters of the Grand Architect and his elite Builderian Gaurd.", true);
	Room* RoomSeventeen = new Room("The Oracle's Sanctum", "The final room, home to the Great Oracle of Bob. There is a special android sentinel force proctecting its highness.", true);
	
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

	//add interactable objects to rooms

	//add key items to rooms

	//make weapons
	
	//make armors
		
	//add weapons to rooms
	
	//add armors to rooms
	
	//add key items to inventories
		
	//add weapons to inventories
	
	//add armors to inventories
	
	//make enemies
	
	//assign inventories to enemies
	
	//add enemies to rooms

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
			//output objs desc in room, if any
			for (int i = 0; i < currentRoom->numObjs; i++) {
			cout << currentRoom->objs[i].description << endl << endl;
			}
			//set visited false
			currentRoom->visited = true;
		} else {
			cout << endl << currentRoom->name << endl << endl;
		}

		//available rooms
		displayRoomInfo(currentRoom); 
		

		//add interaction with objs after navigation works
		
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
			for (int i = 0; i < currentRoom->numObjs; i++) {
			cout << currentRoom->objs[i].description << endl;
			}
			continue;
		}

		//direction logic+input validation with available/unlocked rooms
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
	//game loop end
	
	//deallocate memory
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
	cout << "Enter any character to continue... ";
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
				cout << "OK " << name << ", " << endl;
				break;
			} else if (c == 'n') {
				continue;
			}

		}
		cout << "Invalid input. Please try again." << endl;
	}


	return name;
}

void story(string name) {
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
}

void ProgramGreeting() {
	// system time
	time_t timenow = time(NULL);
	tm *ltm = localtime(&timenow);

	//date output
	cout << "Date: " << 1 + ltm->tm_mon << '/' << ltm->tm_mday << '/' << 1900 + ltm->tm_year << endl; 


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

//add to room functions
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

void addEnemiesToRoom(Room* room, const Enemy& enemy) {
	Enemy* newEnemies = new Enemy[(room->numEnemies) + 1];

	for (int i = 0; i < room->numEnemies; i++)
		newEnemies[i] = room->enemies[i];

	newEnemies[room->numEnemies] = enemy;

	delete[] room->enemies;
	room->enemies = newEnemies;
	room->numEnemies++;
}

void addKey(Room* room, const KeyItem& key) {
	KeyItem* newKeys = new KeyItem[(room->numKeys) + 1];

	for (int i = 0; i < room->numKeys; i++)
		newKeys[i] = room->keys[i];

	newKeys[room->numKeys] = key;

	delete[] room->keys;
	room->keys = newKeys;
	room->numKeys++;
}

void addWeapon(Room* room, const Weapon& weapon) {
	Weapon* newWeapons = new Weapon[(room->numWeapons) + 1];

	for (int i = 0; i < room->numWeapons; i++)
		newWeapons[i] = room->weapons[i];

	newWeapons[room->numWeapons] = weapon;

	delete[] room->weapons;
	room->weapons = newWeapons;
	room->numWeapons++;
}

void addArmor(Room* room, const Armor& armor) {
	Armor* newArmors = new Armor[(room->numArmors) + 1];

	for (int i = 0; i < room->numArmors; i++) 
		newArmors[i] = room->armors[i];

	newArmors[room->numArmors] = armor;

	delete[] room->armors;
	room->armors = newArmors;
	room->numArmors++;
}

//add to inventory functions
void addKey(Inv* inv, const KeyItem& key) {
	KeyItem* newKeys = new KeyItem[(inv->numKeys) + 1];

	for (int i = 0; i < inv->numKeys; i++)
		newKeys[i] = inv->keys[i];

	newKeys[inv->numKeys] = key;

	delete[] inv->keys;
	inv->keys = newKeys;
	inv->numKeys++;
}

void addWeapon(Inv* inv, const Weapon& weapon) {
	//get rid of previous, or it performs no operation if nullptr
	delete inv->weapon;
	//allocate new to inv
	inv->weapon = new Weapon(weapon);
}

void addArmor(Inv* inv, const Armor& armor) {
	delete inv->armor;
	inv->armor = new Armor(armor);
}

//take from room
void TakeKey(Inv* invAdd, Room* roomRemove, const KeyItem& key) {
	//find key in room
	int keyIndex = -1;
	for(int i = 0; i < roomRemove->numKeys; i++) {
		if (roomRemove->keys[i].name == key.name) {
			keyIndex = i; 
			break; 
		}
	}
	
	if(keyIndex != -1) {
		//add key to inv
		addKey(invAdd, roomRemove->keys[keyIndex]);

		//remove key from room
		KeyItem* newKeys = new KeyItem[(roomRemove->numKeys) - 1];
		for (int i = 0; j = 0; i < roomRemove->numKeys; i++) {
			if (i != keyIndex) {
				newKeys[j++] = roomRemove->keys[i];
			}
		}
		delete[] roomRemove->keys;
		roomRemove->keys = newKeys;
		roomRemove->numKeys--;
	}	
}

//take from inv
void TakeKey(Inv* invAdd, Inv* invRemove, const KeyItem& key) {
	//find key in inv
	int keyIndex = -1;
	for(int i = 0; i < invRemove->numKeys; i++) {
		if (invRemove->keys[i].name == key.name) {
			keyIndex = i; 
			break; 
		}
	}
	
	if(keyIndex != -1) {
		//add key to inv
		addKey(invAdd, invRemove->keys[keyIndex]);

		//remove key from room
		KeyItem* newKeys = new KeyItem[(invRemove->numKeys) - 1];
		for (int i = 0; j = 0; i < invRemove->numKeys; i++) {
			if (i != keyIndex) {
				newKeys[j++] = invRemove->keys[i];
			}
		}
		delete[] invRemove->keys;
		invRemove->keys = newKeys;
		invRemove->numKeys--;
	}
}

// inv-room swap functions
void SwapWeapon(Inv* inv, Room* room, const Weapon& weapon){ 
	//find weapon in room
	int weaponIndex = -1;
	for (int i = 0; i <room->numWeapons; i++) {
		if (room->weapons[i].name == weapon.name) {
			weaponIndex = i;
			break;
		}
	}
	//swap
	if (weaponIndex != -1) {
		Weapon temp = *inv->weapon;
		*inv->weapon = room->weapons[weaponIndex];
		room->weapons[weaponIndex] = temp;
	}
}

void SwapArmor(Inv* inv, Room* room, const Armor& armor) {
	//find armor in room
	int armorIndex = -1;
	for (int i = 0; i <room->numArmors; i++) {
		if (room->armors[i].name == armor.name) {
			armorIndex = i;
			break;
		}
	}
	//swap
	if (weaponIndex != -1) {
		Armor temp = *inv->armor;
		*inv->armor = room->armors[armorIndex];
		room->armors[armorIndex] = temp;
	}
}

// inv-inv swap functions
void SwapWeapon(Inv* inv1, Inv* inv2, const Weapon& weapon) {
	//find weapon in inv1
	//only one weapon per inv, much simpler check
	if (inv1->weapon != nullptr && inv1->weapon->name == weapon.name) {
		//swap
		Weapon* temp = inv1->weapon;
		inv1->weapon = inv2->weapon;
		inv2->weapon = temp;
	}
}

void SwapArmor(Inv* inv1, Inv* inv2, const Armor& armor) {
	//find armor in inv1, only one armor per inv
	if (inv1->armor != nullptr && inv1->armor->name == armor.name) {
		//swap
		Armor* temp = inv1->armor;
		inv1->armor = inv2->armor;
		inv2->armor = temp;
	}
}

void roomInteractionMenu(Room* currentRoom, Player* player) {
	//interaction menu loop
	while(true) {
		cout << "Room Interaction Menu:" << endl;
		cout << "1. Loot enemies" << endl;
		cout << "2. Loot room" << endl;
		cout << "3. Interact with room" << endl;
		cout << "4. Exit menu" << endl;
		cout << "Choose an option (1-4): ";
		int choice;
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//Loot enemies sub-menu
		if (choice == 1) {
			if(currentRoom->numEnemies > 0) {
			cout << "Choose an enemy to interact with (1-" << currentRoom->numEnemies << "): ";
			int enemyIndex;
			cin >> enemyIndex;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			if (enemyIndex >= 1 && enemyIndex <= currentRoom->numEnemies) {
				int codeIndex = enemyIndex - 1;
				cout << "1. Swap weapon with enemy" << endl;
				cout << "2. Swap armor with enemy" << endl;
				
			}
	

		}
}

