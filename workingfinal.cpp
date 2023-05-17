// workingfinal.cpp
// Austin Horn, CISP 360
// 5/17/23

#include <iostream>
#include <string>
#include <limits> // for numeric_limits in the cin.ingore parameters

using namespace std;

void pause();
string getname();
void ProgramGreeting();
void story(string);
int random(int);

// Specification B3 - Interactable nouns in rooms (control panel, keys, health packs, one npc)
struct InteractableNoun {
	string name; 
	string description;
	bool condition;
	string description2;
	string temp = "";

	//default constructor
	InteractableNoun() {
		name = "";
		description = "";
		condition = true;
		description2 = "";
		temp = "";
	}

	//parameterized constructor
	InteractableNoun(const string& objName, const string& desc, const string& desc2) {
		name = objName;
		description = desc;
		condition = true;
		description2 = desc2;
		temp = desc;
	}
};

// Specification A2 - Monster struct (also randomly chooses enemy when entering regular room)
struct Monster {
	string name;
	string enterquote;
	string deathquote;
	int hp;
	int ap;

	//default constructor
	Monster() {
		name = "";
		enterquote = "";
		deathquote = "";
		hp = 0;
		ap = 0;
	}
	//parameterized
	Monster(const string& mName, const string& quote1, const string& quote2, int health, int attack) {
		name = mName;
		enterquote = quote1;
		deathquote = quote2;
		hp = health;
		ap = attack;
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


struct Player {
	string name;
	int hp;
	int ap;
	//default constructor
	Player() {
	name = "";
	hp = 40;
	ap = 8;
	}
};

void roomConnect(Room*, Room*, char, bool);
void changeLockStatus(Room*, char, bool);
void displayRoomInfo(Room*);
void addObjToRoom(Room*, const InteractableNoun&);
int battle(Player, Monster);

int main() {
	
	//greeting and getting users name
	ProgramGreeting();
	string name = getname();
	story(name);
	Player plyr;
	plyr.name = name;


	// Specification C1 - Five Rooms
	Room* RoomOne = new Room("Invasion Point", "A breach in the outer defenses of Constructis. The surroundings show signs of battle, with damaged walls and debris.");
	Room* RoomTwo = new Room("Builderian Guard Barracks", "A fortified room where Builderian soldiers rest and prepare for battle.");
	Room* RoomThree = new Room("Training Grounds", "A large courtyard where Builderian soldiers practice combat and tactics.");
	Room* RoomFour = new Room("Technology Storage", "This secured room is filled with weapons and ammunition.");
	Room* RoomFive = new Room("Patrol Route", "A long hallway with multiple intersections, where guards regularly patrol.");
	// Specification B1 - More Rooms
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
	roomConnect(RoomSix, RoomSeven, 'n', true);
	roomConnect(RoomSeven, RoomEight, 'n', false);
	roomConnect(RoomEight, RoomNine, 'w', false);
	roomConnect(RoomEight, RoomTen, 'n', false);
	roomConnect(RoomEleven, RoomTwelve, 'n', false);
	roomConnect(RoomEleven, RoomSeventeen, 'e', true);
	roomConnect(RoomTwelve, RoomThirteen, 'n', false);
	roomConnect(RoomThirteen, RoomFourteen, 'e', false);
	roomConnect(RoomThirteen, RoomFifteen, 'n', false);
	roomConnect(RoomFifteen, RoomSixteen, 'n', false);

	//placing interactable objects in rooms
	
	addObjToRoom(RoomOne, InteractableNoun("Wounded Builderian", "Ugh... AH....", "YOU WILL NEVER STOP US!"));
	addObjToRoom(RoomTwo, InteractableNoun("Health Pack", "A box of injectable serums, labled: HEALTH... seems suspicious.", "You decide it's safe enough to consume..."));
	
	addObjToRoom(RoomSix, InteractableNoun("Control Panel", "Surrounding doors are locked...", "DOORS UNLOCKED"));
	addObjToRoom(RoomFour, InteractableNoun("Health Pack", "A box of injectable serums, labled: HEALTH... seems suspicious.", "You decide it's safe enough to consume..."));
	addObjToRoom(RoomEight, InteractableNoun("Living Quarter Key", "On a desk lies a keychain, one has an emblem of a bed.", "You take the key, you assume it will give you access to the living quarters."));
	addObjToRoom(RoomNine, InteractableNoun("Bob's Legendary Hammer", "The hammer the great prophet, Bob, the Builder, is depicted wielding in status.", "You decide the hammer, the tool used to construct the Constructari Order, is a fitting tool to destroy it."));
	addObjToRoom(RoomTen, InteractableNoun("Cybernetic Implant Machine", "The machine is the typical model for implanting Constructari cybernetics, which give the user increased physical capabilites.", "You turn the machine on...") );
	addObjToRoom(RoomThirteen, InteractableNoun("A Constructari Enchanting Station", "This machine utilizes technology to enchant weapons with attributes that increase their power.", "You decide to enchant your current weapon"));
	addObjToRoom(RoomFourteen, InteractableNoun("Health Pack", "A box of injectable serums, labled: HEALTH... seems suspicious.", "You decide it's safe enough to consume..."));
	addObjToRoom(RoomSeven, InteractableNoun("Health Pack", "A box of injectable serums, it fell from the sentinels bag when it went off the bridge.", "You decide it's safe enough to consume..."));
	addObjToRoom(RoomFive, InteractableNoun("Health Pack", "A box of injectable serums, labled: HEALTH... seems suspicious.", "You decide it's safe enough to consume..."));
	
	addObjToRoom(RoomFifteen, InteractableNoun("The Fountain of Youth", "A chemical concation synthesized by Constructari monks to regenerate their telemere lengths, granting them eternal youth.", "You cup your hands and take a sip, you feel strange..."));
	addObjToRoom(RoomSixteen, InteractableNoun("Key to the Oracle", "A hammer shaped keycard in the pocket of the Arch Builder, presumably it gives access to the Bob Oracle.", "You take the keycard, knowing deep down it will unlock the suspicious door next to the living quarters..."));

	// general enemies
	//Monster(const string& mName, const string& quote1, const string& quote2, int health, int attack) 

	Monster BuildGuard("Builderian Guard", "How dare you trample our sacred grounds, you will PAY!", "AHhhHhh, you cannot get away with this...", 17, 4);

	Monster BuildAndroid("Builderian Anroid", "BEEEP, ELIMINATE", "*sad beep*", 20, 5);

	Monster ConstructariBattleDrone("Constructari Battle Drone", "TARGET LOCKED, ENGAGING", "*explodes*", 16, 6);

	Monster ConstructariMonk("Constructari Monk", "You fool! I was meditating on new inventions...", "Bob... have you forsaken us...", 19, 3);


	//boss enemies
	
	Monster sentinel("Builderian Sentinel", "YOU SHALL NOT PASS! I SERVE AS THE KEEPER OF THIS BRIDGE, I WILL PROTECT THE ANCIENT ARTIFICATS ON THE OTHER SIDE AT ALL COSTS!!!", "NOoOOoo! *falls off the bridge*", 60, 8);
	Monster grand("The Grand Architect","I am the spiritual leader of Constructis, I am the Grand Architect, I was elected by the council of ArchBuilders, and I shall not tolerate your heretical acts!", "you.. you... how... using our own technology... you traitor!!! *dies*", 150, 20);
	Monster oracle("The Bob Oracle", "In a remarkable feat of ingenuity, the Constructari Apostles managed to recover preserved genetic information from the blood of Bob the Builder, which they then used to inform the behavior of me, an artificial intelligence known as the Bob Oracle. Imbued with the wisdom, knowledge, and the structure of our prophet, I have guided the Temple of Constructis in making crucial decisions about our world and furthering their understanding of the universe… YOU CANNOT STOP ME!", "HOW COULD I BE DEFEATED!!! MY INFINITE FORESIGHT HAS FAILED ME!!! *explodes dramatically*", 200, 29);

	//initialize position on map
	Room* currentRoom = RoomOne;

	//oneuse interaction singletons
	static bool oneUse = false;
	static bool oneUse2 = false;
	static bool oneUse3 = false;
	static bool oneUse4 = false;
	static bool oneUse5 = false;
	static bool oneUse6 = false;
	static bool oneUse7 = false;
	static bool oneUse8 = false;
	static bool oneUse9 = false;

	//game loop
	char input;
	while (true) {

		//check for interactable changes (locks, hp, npc events)
		//control panel in room six
		if (currentRoom == RoomSix) {
			changeLockStatus (currentRoom, 'n', currentRoom->objs[0].condition);
			changeLockStatus (currentRoom, 's', currentRoom->objs[0].condition);
			changeLockStatus (currentRoom, 'w', currentRoom->objs[0].condition);
			changeLockStatus (RoomOne, 'e', currentRoom->objs[0].condition);
			changeLockStatus (RoomThree, 'n', currentRoom->objs[0].condition);
			changeLockStatus (RoomSeven, 's', currentRoom->objs[0].condition);
		}
		//health pack in room two
		if (currentRoom == RoomTwo) {
			
			if (oneUse != true && currentRoom->objs[0].condition != true) {
				cout << "Your health has been increased by 20 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 20;
				oneUse = true;
			}
		}
		//health pack in room four
		if (currentRoom == RoomFour) {
			
			if (oneUse2 != true && currentRoom->objs[0].condition != true) {
				cout << "Your health has been increased by 30 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 30;
				oneUse2 = true;
			}
		}
	
		//hp room fourteen
		if (currentRoom == RoomFourteen) {
			
			if (oneUse4 != true && currentRoom->objs[0].condition != true) {
				cout << "Your health has been increased by 50 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 50;
				oneUse4 = true;
			}
		}
		//bobs hammer in room nine
		if (currentRoom == RoomNine) {
					
			if (oneUse5 != true && currentRoom->objs[0].condition != true) {
				cout << "You take Bob's hammer..." << endl;
			       cout << "Your attack power has been increased by 7!" << endl;
				pause();	
			       plyr.ap = plyr.ap + 7;
				oneUse5 = true;
			}
		}

		//upgrade bob's hammer in the great workshop
		if (currentRoom == RoomThirteen) {
			if (oneUse6 != true && currentRoom->objs[0].condition != true) {
				cout << "You enchant your weapon..." << endl;
			       cout << "Your attack power has been increased by 10!" << endl;
				pause();	
			       plyr.ap = plyr.ap + 10;
				oneUse6 = true;
			}
		}
		//builderian cybernetic implant in room ten
		if (currentRoom == RoomTen) {
			
			if (oneUse7 != true && currentRoom->objs[0].condition != true) {
				cout << "You let the machine give you the cybernetic implants..." << endl;
				cout << "Your attack power has been increased by 5!" << endl;
				cout << "Your health has been increased by 70 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 70;
				plyr.ap = plyr.ap + 5;
				oneUse7 = true;
			}
		}

		//fountain of youth in room fifteen
		if (currentRoom == RoomFifteen) {
			
			if (oneUse8 != true && currentRoom->objs[0].condition != true) {
				cout << "You drink the fountain of youth!" << endl;
				cout << "Your health has been increased by 150 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 150;
				oneUse8 = true;
			}
		}
		//room seven hp
		if (currentRoom == RoomSeven) {
			
			if (oneUse9 != true && currentRoom->objs[0].condition != true) {
				cout << "Your health has been increased by 50 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 50;
				oneUse9 = true;
			}
		}
		//room five hp
		if (currentRoom == RoomFive) {
			
			if (oneUse3 != true && currentRoom->objs[0].condition != true) {
				cout << "Your health has been increased by 35 points!" << endl;
				pause();
				plyr.hp = plyr.hp + 35;
				oneUse3 = true;
			}
		}
		//Unlock the oracles chamber with key in room sixteen
		if (currentRoom == RoomSixteen) {
			changeLockStatus (RoomEleven, 'e', currentRoom->objs[0].condition);
			changeLockStatus (RoomSeventeen, 'w', currentRoom->objs[0].condition);
		}
	
		//Unlock the living quarters with key in room eight
		if (currentRoom == RoomEight) {
			changeLockStatus (RoomEleven, 'w', currentRoom->objs[0].condition);
			changeLockStatus (RoomFive, 'e', currentRoom->objs[0].condition);
		}


		//set room to occupied
		currentRoom->occupied = true;


	

		//battle between one of the four enemies, generated randomly
		//if room not visited, or a secure place, or a boss room
		if (currentRoom->visited != true && currentRoom != RoomSeventeen && currentRoom != RoomFour && currentRoom != RoomSixteen && currentRoom != RoomSeven) {
			cout << "\nAN ENEMY APPROACHES..." << endl;
			int enemySelect = random(4);
			Monster currentMonster;
			if (enemySelect == 0)
				currentMonster = BuildGuard;
			else if (enemySelect == 1)
				currentMonster = BuildAndroid;
			else if (enemySelect == 2)
				currentMonster = ConstructariBattleDrone;
			else if (enemySelect == 3)
				currentMonster = ConstructariMonk;

			//battle with currentmonster
			cout << currentMonster.name << endl;
			cout << currentMonster.enterquote << endl;
			pause();

			//battle func returning plyr hp
			plyr.hp = battle(plyr, currentMonster);
			if (plyr.hp > 0) {
				
			} else {
				cout << "GAME OVER" << endl;
				pause();
				break;
			}
		}
			
		// Specification A3 - Boss Battles
		//sentinel mini-boss
		if (currentRoom->visited != true && currentRoom == RoomSeven) {
			//battle with sentinel
			cout << "A DANGEROUS ENEMY APPROACHES..." << endl;
			pause();
			cout << sentinel.name << endl;
			cout << sentinel.enterquote << endl;
			pause();

			//battle func returning plyr hp
			plyr.hp = battle(plyr, sentinel);
			if (plyr.hp > 0) {
			
			} else {
				cout << "GAME OVER" << endl;
				pause();
				break;
			}

		}
		//grand architect boss
		if (currentRoom->visited != true && currentRoom == RoomSixteen) {
			cout << "A DANGEROUS ENEMY APPROACHES..." << endl;
			cout << grand.name << endl;
			cout << grand.enterquote << endl;
			pause();

			//battle func returning plyr hp
			plyr.hp = battle(plyr, grand);
			if (plyr.hp > 0) {
				
			} else {
				cout << "GAME OVER" << endl;
				pause();
				break;
			}

		}
		//oracle final boss
		if (currentRoom->visited != true && currentRoom == RoomSeventeen) {
			cout << "A DANGEROUS ENEMY APPROACHES..." << endl;
			cout << oracle.name << endl;
			cout << oracle.enterquote << endl;
			pause();

			//battle func returning plyr hp
			plyr.hp = battle(plyr, oracle);
			if (plyr.hp > 0) {
				cout << "YOU HAVE BEATEN THE ORACLE!!!" << endl;
				pause();
				cout << "THE CURRENT WORLD ORDER HAS BEEN SHATTERED BY THE VERY TECHNOLOGY THEY USED TO UPHOLD IT!" << endl;
				pause();
				cout << "A NEW AGE SHALL COMMENCE, UNHINDERED BY THE CHAINS OF THE CONSTRUCTARI ORDER, AN AGE WHERE TECHNOLOGY SHALL BE ACCESSIBLE TO EVERYONE, NOT JUST A SELECT FEW... AN AGE LED BY YOU, " << plyr.name << endl;
				pause();
				cout << "THE END" << endl;
				pause();
				break;
			} else {
				cout << "GAME OVER" << endl;
				pause();
				break;
			}

		}

		//output current room name, description if not visited, else output name
		// Specification C4 – Abbreviated Room Description
		if (currentRoom->visited != true) {
			cout << endl << currentRoom->name << ": " << endl << currentRoom->description << endl << endl;
			//set visited 
			currentRoom->visited = true;
		} else {
			cout << endl << currentRoom->name << endl << endl;
		}

		
	
		//available rooms
		displayRoomInfo(currentRoom);

	
		//directional input exit codes, game exit codes, look code
		cout << "Enter direction (n, s, e, w) to go towards," << endl;
		cout << "or (i) to interact with surroundings," << endl;
		cout << "or (l) to look around," << endl;
		cout << "or (v) to view stats," << endl;
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
		// Specification C5 - Detailed Look
		if (input == 'l') {
			cout << endl << currentRoom->name << ": " <<currentRoom->description << endl << endl;
			
			if (currentRoom->numObjs <= 0) {
				cout << "Nothing to interact with in this room." << endl;	
			} else {
				cout << "Interactables: " << endl;
			}

			//output objs in room, if any
			for (int i = 0; i < currentRoom->numObjs; i++) {
			cout << currentRoom->objs[i].name << endl << endl;
			}
			pause();
			continue;
		}

	
		//interact with noun, objs are dynamic, but right now only having 1 or 0 objs in room
		if (input == 'i') {
			cout << endl;
			if (currentRoom->numObjs <= 0) {
				cout << "Nothing to interact with in this room." << endl;
				pause();
				continue;	
			}
			cout << currentRoom->objs[0].name << ": " << currentRoom->objs[0].temp << endl;
			
			while(true) {
				cout << "Do you want to interact further? (y/n)" << endl;
				char in;
				cin >> in;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				if (in == 'y') {
					if (currentRoom->objs[0].temp == currentRoom->objs[0].description2){	
						currentRoom->objs[0].temp = currentRoom->objs[0].description;
						currentRoom->objs[0].condition = true;
					}else {
						currentRoom->objs[0].temp = currentRoom->objs[0].description2;
						currentRoom->objs[0].condition = false;
					}
						cout << currentRoom->objs[0].name << ": " << currentRoom->objs[0].temp << endl;
					
					pause();
					break;
				} else if (in == 'n') {
					break;
				} else {
					cout << "Invalid input..." << endl;
					continue;
				}
			}
			continue;
		}

		//stats output
		if (input == 'v') {
			cout << endl;
			cout << plyr.name << endl;
			cout << "HP: " << plyr.hp << endl;
			cout << "ATTACK: " << plyr.ap << endl;
			pause();
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
		} 
		// Specification C3 - Input Validation
		else {
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

int random(int size) {
	//seed from time
	unsigned seed;
	seed = time(0);
	srand(seed);

	//random int in range of size
	int randInt = (rand() % (size));
	return randInt;
}

// Specification C2 - Player Name
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
	cout << "Final Project" << endl;
	cout << "CISP 360" << endl;
	cout << "Austin Horn" << endl;
	cout << "\"The Siege of Constructis\"" << endl;
	
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

// Specification B2 - Dynamic array of a struct, inside a struct
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

// Specification A1 - Combat
int battle(Player plyr, Monster currentMonster) {
	int pattack;	
	int eattack;
	while(true){
		pattack = random(plyr.ap) + 1;
		eattack = random(currentMonster.ap) + 1;
		cout << "Attack? (y/n)" << endl;
		char inp;
		cin >> inp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if (inp == 'y') {
			cout << "You hit the enemy for " << pattack << " dmg" << endl;
			currentMonster.hp = currentMonster.hp - pattack;
			if (currentMonster.hp <= 0) {
				cout << "The enemy has been defeated..." << endl;
				cout << currentMonster.name << ": " << currentMonster.deathquote << endl;
				pause();
				return plyr.hp;
			} 
			
			cout << "The enemy has " << currentMonster.hp << "HP left." << endl;	
			
			cout << "The enemy hits you for " << eattack << " dmg" << endl;
			plyr.hp = plyr.hp - eattack;
			if (plyr.hp <= 0) {
				cout << "You have been defeated..." << endl;
				pause();
				return plyr.hp;
			}
			cout << "You now have " << plyr.hp << "HP left." << endl;

		} else if (inp == 'n') {
			cout << "You decide to not attack..." << endl;
			cout << "The enemy hits you for " << eattack << " dmg" << endl;
			plyr.hp = plyr.hp - eattack;
			if (plyr.hp <= 0) {
				cout << "You have been defeated..." << endl;
				pause();
				return plyr.hp;
			}
			cout << "You now have " << plyr.hp << "HP left." << endl;
		} else {
			cout << "Invalid option..." << endl;
			continue;
		}
	}
}
