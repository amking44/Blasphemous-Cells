//DungeonOfTheSwamp.cpp
//Alex King, CISP 360
//12/19/2019
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

void bootMessage(int);
int endMessage(int, struct entity*);
int inputValidation2(int);
int inputValidation3(int);
int startCombat(struct entity*, struct entity);
int bladeTrap(struct entity*);
int room1(struct entity);
int room2(struct entity*); 
int room3(struct entity*);
int room4(struct entity*);
int room5(struct entity*, int);
int room6(struct entity*);

// Specification A1 - Put your monsters in a Monster() class. - This struct is used for all entities in the game, and there are a total of 3 monsters in the game which are created within their respective room.
struct entity
{
	string name;
	string className;
	int health, attackPower;
	int monstersSlain;
	int potions;
};

//+++++++++++++++++++++++++++++++VV+MAIN+VV+++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++FUNCTION++++++++++++++++++++++++++++++++++++++++++

int main() 
{
	int programIterations = 1;
	do
	{
		entity player;
		string name;
		bootMessage(programIterations);
		cout << "Please enter the name you wish to go by: ";
		// Specification C2 - Player Name
		cin >> player.name;
		cout << "\nYou have chosen to go by " << player.name << ".\n\n";
		int currentClass = 0;
		cout << "Select between 3 classes: \n1.Warrior(Health: 50, Attack Power:20) \n2.Pirate(Health: 40, Attack Power:40) \n3.Rogue(Health: 30, Attack Power:60)\n";
		cin >> currentClass;
		cout << endl;
		// Specification C3 - Input Validation
		inputValidation3(currentClass);
		if (currentClass == 1)
		{
			cout << "You've decided to play as a Warrior.\n\n";
			player.className = "Warrior";
			player.health = 50;
			player.attackPower = 20;
			player.potions = 0;
		}
		else if (currentClass == 2)
		{
			cout << "You've decided to play as a Pirate.\n\n";
			player.className = "Pirate";
			player.health = 40;
			player.attackPower = 40;
			player.potions = 0;
		}
		else if (currentClass == 3)
		{
			cout << "You've decided to play as a Rogue.\n\n";
			player.className = "Rogue";
			player.health = 30;
			player.attackPower = 60;
			player.potions = 0;
		}
		int room1Decision = room1(player);
		switch (room1Decision)
		{
			case 1:
			{
				int room2Decision = room2(&player);
					if (player.health == -1)
						programIterations = endMessage(programIterations, &player);
					switch (room2Decision)
					{
						case 1:
						{	
							int secretShortcut = 1;
							room5(&player, secretShortcut);
							room6(&player);
						}
						case 2:
						{
							int secretShortcut = 0;
							int room3decision = room3(&player);
							if (player.health == -1)
								programIterations = endMessage(programIterations, &player);
							if (room3decision == 5)
							{
								bladeTrap(&player);
							}
							if (player.health == -1)
								programIterations = endMessage(programIterations, &player);
							int room5decision = 0;
							int room6decision = 0;
							room4(&player);
								if (player.health == -1)
									programIterations = endMessage(programIterations, &player);
							room5(&player, secretShortcut);
								if (player.health == -1)
									programIterations = endMessage(programIterations, &player);
							room6(&player);
								if (player.health == -1)
									programIterations = endMessage(programIterations, &player);
						}	
						case 3:
							programIterations = endMessage(programIterations, &player);

					}
			}
			case 2:
			{
				programIterations = endMessage(programIterations, &player);
			}

		}
		//programIterations = endMessage(programIterations, &player); - end message and loop break/continue
		if (player.health == -1)
			programIterations = endMessage(programIterations, &player);
	}
	while (programIterations != 0);

	return 0;
}
//++++++++++++++++++++++++++++++++^^MAIN^^++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++FUNCTION++++++++++++++++++++++++++++++++++++++++++


//change message later to explain more/give more detail
void bootMessage(int count)
{
	if (count == 1)
		cout << "Welcome to the dungeon of The Swamp\n\n";
	cout << "In this game you will be adventuring through a dungeon trying to survive. The only two ways the game will end is if you escape through the exit, or if your health reach zero.\n\n";
	cout << "Once you enter a new room, you will have a various selection of things to do. To select an action, press the number corresponding to the action you wish to perform.\n\n";
}

int endMessage(int timesRun, struct entity *player)
{
	int exitOrNaw = 0;
	if ((*player).health == 0)
	{
		cout << "Looks like the dungeon got the best of you. Maybe this was a learning experience and the next generations can learn from your bones deep within the dungeon of The Swamp...or maybe not.\n\n";
	}
	if ((*player).health > 0)
	{
		cout << "You have made it out of the dungeon alive and well. Now you can grow old and tell the next generations of the stories of your adventure into the dangerous dungeon of The Swamp. The world will forever remember the name " << (*player).name << ".\n\n";
	}
	cout << "You have reached the end of the game. Enter 0 to exit or 1 to play again.\n";
	cin >> exitOrNaw;
	cout << endl;
	if (exitOrNaw == 0)
	{
		timesRun = 0; 		
	}
	else if (exitOrNaw == 1)
	{
		timesRun++;
		cout << timesRun << endl;
	}
	return timesRun;
}

//Specification B1 - Add Combat - This is a function that does combat using a player entity(struct) and a monster entity(struct) as arguments modifying player health with pointers.
int startCombat(struct entity *player, struct entity monster)
{
	while ((*player).health > 0 && monster.health > 0)
	{
		int combatChoice;
		cout << "Battle Start!!\n\n";
		cout << "Your Health:" << (*player).health << setw(28) << "Your Attack:" << (*player).attackPower << endl << monster.name << " Health:" << monster.health << setw(20) << monster.name << " Attack:" << monster.attackPower << endl << endl;
		cout << "1. Attack (Deal " << (*player).attackPower << " health of damage) \n2. Defend (Chance to reduce dmg by 1)";
		if ((*player).potions == 1)
		{
			cout << "\n.3 Use potion.";
		}
		cout << "\n\n";
		cin >> combatChoice;
		cout << endl;
		inputValidation2(combatChoice);
		if (combatChoice == 1)
		{
			monster.health = monster.health - (*player).attackPower;
			if (monster.health > 0)
				(*player).health = (*player).health - monster.attackPower;
		}
		else if (combatChoice == 2)
		{
			srand(time(NULL));
			int chance = rand()%3;
			if (chance == 1 || chance == 0)
			{
				cout << "Block successful!\n";
				(*player).health = (*player).health - (monster.attackPower - 10);
			}
			else if  (chance == 2)
			{
				cout << "Block failed!\n";
				(*player).health = (*player).health - monster.attackPower;
			}
		}	
		else if (combatChoice == 3)
		{
			cout << "You used the potion! It seems to have a positve effect, for your feel your strength returning. (Health +50, Attack +30)\n";
			(*player).health = (*player).health + 50;
			(*player).attackPower = (*player).attackPower + 50;
			(*player).potions = 0;
		}
	}
	if ((*player).health < 0)
	{
		(*player).health = -1;
		cout << "You've fallen to a " << monster.name << ".\n";
		return (*player).health;
	}
	if (monster.health < 0)
	{
		cout << "You've beaten the " << monster.name << ".\n";
		(*player).monstersSlain++;
		return (*player).health;
	}
	return 0;
}

//Specification B2 - Add trap encounters - This is one trap encounter that the player can interact with and try to disable, but they can fail and die here.
int bladeTrap(struct entity *player)
{
	int trapChoice = 0;
	cout << "You notice a tripwire right next to the door, along with what seems like a huge guillotine above!!\n";
	cout << "1. Try to disable the tripwire (75% chance to succeed with no injury, 25% chance to fail) \n2. Try to avoid the wire (50% chance to pass unharmed, 50% chance to trip it.)\n";
	cin >> trapChoice;
	cout << endl;
	inputValidation2(trapChoice);
		switch (trapChoice)
		{
			case 1:
			{
				int disableTrapChance = 0;
				srand(time(NULL));
				disableTrapChance = rand()%4;
				if (disableTrapChance == 0 || disableTrapChance == 1 || disableTrapChance == 2)
				{
					cout << "You've successfully disabled the trap and enter the next room.\n\n";
					return 1;
				}
				if (disableTrapChance == 3)
				{
					cout << "You try and disable it and fail to do so. You Managed to get past the trap but you lost two fingers in the process. (Health -5, Attack - 10)\n\n";
					(*player).health = (*player).health - 5;
					(*player).attackPower = (*player).attackPower - 10;
					return 1;
				}
			}
			
			case 2:
			{
				int trapAvoidChance = 0;
				srand(time(NULL));
				trapAvoidChance = rand()%2;
				if (trapAvoidChance == 0)
				{
					cout << "With great care, you pass over the tripwire, leaving the trap for some other sorry sap.\n\n";
				}
				if (trapAvoidChance == 1)
				{
					cout << "You are clumsy, slip and trigger the trap. The guillotine comes down on your spine and splits you in twain, swiftly ending your adventure. Maybe next time be a little more careful?\n\n";
					(*player).health = 0;
				}
			}
		}
	return 1;
}

int room1(struct entity player)
{
	int id = 1;
	int choice = 0;
	int choice2 = 0;
	int choice3 = 0;
	// Specification C4 – Abbreviated Room Description
	cout << "You enter the first room. Luckily, nobody seems to be present at the time. There seems to be a door to the next room to the South.\n";
	cout << "1. Examine the room closer. \n2. Exit the dungeon and live to explore another day. \n3. Move on to the next room to the South.\n";
	cin >> choice;
	cout << endl;
	inputValidation3(choice);
	switch(choice)
	{
		case 1:
			// Specification C5 - Detailed Look
			cout << "This is the first room you entered into when beginning the dungeon. The room is on the verge of falling apart. Nature has ravaged this area and reclaimed it as its' own. There seems to be remains of a door to the East and West,but fallen debris seems to have blocked these exits. The Southern door has quite unsettling sounds behind it. After a closer examination you notice writing on the wall next to the Southern exit.\n";
			cout << "1. Read the writing on the wall. \n2. Exit the dungeon and live to explore another day (exit through the Northern door). \n3. Move on to the next room to the South.\n";
			cin >> choice2;
			cout << endl;
			inputValidation3(choice2);
				switch(choice2)
				{
					case 1:
						cout << "The writing is in blood and is very hard to read. All you can make out is 'monsters', 'death', and..." << player.name << "!?!\n";
						cout << "1. Continue into the next room \n2. Play it safe and leave the dungeon.\n";
						cin >> choice3;
						cout << endl;
						inputValidation2(choice3);
						if (choice3 == 1)
						{
							cout << "Despite the extremely omnious warning, you forge ahead.\n\n"; 
							return 1;
						}
						else if (choice3 == 2)
							return 2;
					case 2:
						cout << "You've decided that this may not be your type of adventure.\n\n";
						return 2;
					case 3:
						cout << "You tell yourself that is all this room has to offer, and you move along to the next room.\n\n";
						return 1;
				}
		case 2:
			cout << "You have decided to explore another day.\n";
			return 2;
		case 3:
			cout << "You walk towards the door and hear things inside, giving you a bad feeling about what's ahead.\n\n";
			return 1;
	}
	return choice3;
}

int room2(struct entity *player)
{
	int choice, choice2, choice3, choice4 = 0;
	//Specifivation A3 - Randomly determine if the room is occupied. - Two functions are used from <cstdlib> to create a random number then take the modulus of that number to create random monster spawning.
	srand(time(NULL));
	int monsterSpawn = rand()%3;
	if (monsterSpawn == 1 || monsterSpawn == 2)
	{
		int combatChoice = 0;
		cout << "You knew these sounds weren't your imagination. As you walk in the room you see a small hellish monster. It notices you, so you ready yourself for a fight.\n\n";
		entity imp;
		imp.name = "Devilish Imp";
		imp.health = 15;
		imp.attackPower = 5;
		startCombat(player, imp);
		if ((*player).health == -1)
			return 3;
		cout << "With the imp gone, you can now clearly explore the rest of the horrifying room.\n\n";	
	}
	if (monsterSpawn == 0)
	{
		cout << "You enter the second room. Those ominous noises seem to have just been your imagination. "; 
	}
	cout << "You begin to look around and this room still feels like an evil presence is watching. What could possibly make you feel this way? Other than that there is an exit to the West to the next room.\n";
	cout << "1. Examine the room closer. \n2. Move onto the next room to the West.\n";
	cin >> choice;
	cout << endl;
	if (choice == 1)
	{
		cout << "As you take a step back, you see an open box in the center of the room. This makes you understand 	why an imp from hell would be here, for there is a pentagram drawn on the floor with the box in the 	middle. There also seems to be something on the Southern wall, but from this distance you can't quite make 	it out.\n\n";
		cout << "1. Check out what is on the Southern wall. \n2. Examine the box. \n3. Leave through the Western exit.\n\n";
		cin >> choice2;
		cout << endl;
		inputValidation3(choice2);
		switch (choice2)
		{	
			case 1:
				
				cout << "You walk towards the wall cautiously. There seems to be some sort of switch on the wall, but you can't tell where it goes. With what you've previously observed, do you press it, or leave it and go through the West exit?\n\n";
				cout << "1. Press the switch. \n2. Play it safe and leave through the West exit.\n";
				cin >> choice3;
				cout << endl;
				inputValidation2(choice3);
				if (choice3 == 1)
				{
					cout << "The switch seems to have opened a shortcut to a different room.\n\n";
					return 1;
				}
				else if (choice3 == 2)
				{
					cout << "You don't take any more chances and choose to go through the Western exit.\n\n";
					return 2;
				}
			case 2:
				cout << "Throwing caution to the wind, you look inside the box.\n\n";
				cout << "A tiny creature jumps at you and cuts you! You have lost 10 health.\n";
				(*player).health = (*player).health - 10;
				cout << "Feeling flustered but focused, you decide wether to use the West exit or examine the Southern wall. \n\n";
				cout << "1. Check Southern wall. \n2. Exit through the Western exit.\n";
				cin >> choice3;
				cout << endl;
				inputValidation2(choice3);
				if (choice3 == 1)
				{
					cout << "You walk towards the wall cautiously. There seems to be some sort of switch on the wall, but you can't tell where it goes. With what you've previously observed, do you press it, or leave it and go through the West exit?\n\n";
					cout << "1. Press the switch. \n2. Play it safe and leave through the West exit.\n";
					cin >> choice4;
					cout << endl;
					inputValidation2(choice4);
				}
				if (choice4 == 1)
				{
					cout << "The switch seems to have opened a shortcut to a different room.\n\n";
					return 1;
				}
				else if (choice4 == 2)
				{
					cout << "You don't take any more chances and choose to go through the Western exit.\n\n";
					return 2;
				}
		}
	}
	return 2;
}

int room3(struct entity *player)
{
	int choice1, choice2, choice3 = 0;	
	cout << "After seeing what the second room held, you take your time when entering this third room. This room is oddly plain compared to the previous. A door seems to lead further into the dungeon on the Southern wall.\n\n";
	cout << "1. Look around. \n2. Rest. (Health +15, Attack -5) \n3. Exit and move on to the next room. \n";
	cin >> choice1;
	cout << endl;
	inputValidation3(choice1);
	switch (choice1)
	{
		case 1:
			cout << "With the last room having a evil feeling to it, this room is seems so out of place. It isn't worn down very much and it seems as if not a single soul has been here. The only thing you see is the door to the next room.\n\n";
			cout << "1. Continue looking. \n2. Rest. (Health +15, Attack -5) \n3. Proceed through the door and continue your journey.\n";
			cin >> choice2;
			cout << endl;
			inputValidation3(choice2);
			switch (choice2)
			{
				case 1:
					cout << "Nothing else seems to be here.....\n\n";
					cout << "......\n\n";
					return 5;
				case 2:
					cout << "With having to deal with the disaster of the last room, you decide to take a short rest to regain some strength for the coming hardships.\n";
					cout << "After resting you decide wether to stay and look around more, or to keep going.\n";
					cout << "1. Continue looking. \n2. Keep going.\n";
					cin >> choice3;
					cout << endl;
					inputValidation2(choice3);
					switch (choice3)
					{
						case 1:
							cout << "Nothing else seems to be here.....\n\n";
							cout << "......\n\n";
							return 5;
						case 2:
							cout << "As you walk through the door, you hear a click and feel your foot trigger a tripwire. Before you can even fully look up, the guillotine above you splits you in twain. A better adventurer would have paid attention.\n\n";
							(*player).health = 0;
					}
			case 3:
				cout << "As you walk through the door, you hear a click and feel your foot trigger a tripwire. Before you can even fully look up, the guillotine above you splits you in twain. A better adventurer would have paid attention.\n\n";
				(*player).health = 0;
			}				
	}
	return 1;
}

int room4(struct entity *player)
{
	int choice1, choice2, choice3 = 0;
	cout << "The adventure begins to wear on you as you enter the fourth room. The room has an exit to the next room to the East, a well with water, and what seems to be a statue on the Western wall facing the well.\n";
	cout << "1. Examine golem. \n2. Examine well. \n3. Examine room.";
	cin >> choice1;
	cout << endl;
	inputValidation3(choice1);
	switch (choice1)
	{	
		case 1:
		{
			cout << "You take a few steps closer to examine the golem. Before you can examine it closely, you step on a pressure plate that made the golem come to life. He doesn't seem happy with you. You think to yourself, 'A good adventurer would have seen that coming...'\n\n";
			entity golem;
			golem.name = "Holy Stone Golem";
			golem.health = 70;
			golem.attackPower = 15;
			startCombat(player, golem);
			if ((*player).health == -1)
				return 3;
			cout << "With the golem gone the room is definitely safe.\n";
			cout << "1. Examine well. \n2. Go through the Eastern exit.\n";
			cin >> choice2;
			cout << endl;
			inputValidation2(choice2);
			switch (choice2)
				case 1:
					cout << "You take a closer look at the well. The water is still and seems to be holy. Drinking this might be of some benefit. Hopefully.\n";
					cout << "1. Drink the water. \n2. Don't drink the water.\n";
					cin >> choice3;
					switch (choice3)
						case 1:
							//Specification B2 - Add trap encounters - Second trap, if you have slain more than 2 monsters, you'll die.
							if ((*player).monstersSlain > 1)
							{
								cout << "You drink the water, but you immediately feel an intense burning inside you. The pain is too unbearable and right before you draw your last breath, you hear a holy voice tell you, 'You have far too much blood on your hands to live...\n\n";
								(*player).health = 0;
							}
		}
		case 2:
		{
			cout << "You take a closer look at the well. The water is still and seems to be holy. Drinking this might be of some benefit. Hopefully.\n";
			cout << "1. Drink the water. \n2. Don't drink the water.\n";
			cin >> choice2;
			switch (choice2)
				case 1:
					if ((*player).monstersSlain == 1)
					{	
						cout << "The water is very refreshing and tastes like the nectar of the gods. You feel much stronger than before. (Health +100, Attack +20)\n";
						(*player).health = (*player).health + 100;
						(*player).attackPower = (*player).attackPower + 20;
						cout << "The statue still stands tall and the exit is to the East.\n";
						cout << "1. Look at the golem. \n2. Proceed into the next room to the East.\n";
						cin >> choice3;
						cout << endl;
						inputValidation2(choice3);
						switch (choice3)
							case 1:
							{
								cout << "You take a few steps closer to examine the golem. Before you can examine it closely, you step on a pressure plate that made the golem come to life. He doesn't seem happy with you. You think to yourself, 'A good adventurer would have seen that coming...\n\n'";
								entity golem;
								golem.name = "Holy Stone Golem";
								golem.health = 70;
								golem.attackPower = 20;
								startCombat(player, golem);
								cout << "With the golem gone the room is definitely safe.\n";
								cout << "All that is left is to proceed through the Eastern exit.\n\n";
								cout << "1. Go to the next room.\n";
								cin.ignore();
								return 1;
							}
					}
		}
	}
	return 1;
}

// Specification C1 - Five Rooms
int room5(struct entity *player, int shortcutEntrance)
{
	if (shortcutEntrance == 0)
	{
		int choice1, choice2, choice3 = 0;
		cout << "The further and further in you go, the more you doubt you'll ever make it out alive. This fifth room is another untouched room, with but a single chest in the corner. And of course there is an exit, which is on the Eastern wall.\n";
		cout << "1. Carefully inspect the room. \n2. Open the chest. \n3. Go to the next room.\n";
		cin >> choice1;
		cout << endl;
		inputValidation3(choice1);
		switch (choice1)
		{
			case 1:
				cout << "Using knowledge from previous rooms, you stay alert as you do not know what to expect. No footprints....no tripwires....no hidden monsters.....just an evil gloomy chest.\n\n";
				cout << "1. Open the chest. \n2. Proveed to the next room.\n";
				cin >> choice2;
				cout << endl;
				inputValidation2(choice2);
				switch (choice2)
				{
					//Specification B3 - Add treasure - Room with just a treasure chest, but players can only open it if they've slain more than 2 monsters.
					case 1:
						if ((*player).monstersSlain < 2)
							cout << "You try and open the chest but it won't budge. You look for a lock to try and pick, but it has no lock, or even a latch for that matter. This strange chest gives you the same feeling as you felt in the second room. Like you're being watched.\n\n";
						if ((*player).monstersSlain == 2)
						{
							cout << "You go up to the chest and you place your hand on it, but it seems to open itself. As if it knew to open it for you. Inside the chest is a potion. This could come in handy later, so you decide to keep it.\n";
							(*player).potions = 1;
						}
						cout << "Knowing there isn't anything left but the chest, you decide to move on to the next room.\n\n";
						return 1;
					case 2:
						cout << "You know from your previous experiences in this dungeon that the chest is obviously a trap, therefore you decide to pass up the opportunity for treasure and move to the next room.\n\n";
						return 1;
				}
		}
	}
	else if (shortcutEntrance == 1)
	{
		int choice1 = 0;
		cout << "This shortcut seems like it helped, but you can't be sure. The room you are in now is empty aside from a single ominous looking chest. It seems like it would fit in the last room.\n\n";
		cout << "1. Inspect the room. \n2. Open the chest. \n3. Go to the next room.\n";
		cin >> choice1;
		cout << endl;
		inputValidation3(choice1);
		switch (choice1)
		{
			case 1:
			{
				if ((*player).monstersSlain < 2)
					cout << "You try and open the chest but it won't budge. You look for a lock to try and pick, but it has no lock, or even a latch for that matter. This strange chest gives you the same feeling as you felt in the second room. Like you're being watched.\n\n";
				if ((*player).monstersSlain == 2)
				{
					cout << "You go up to the chest and you place your hand on it, but it seems to open itself. As if it knew to open it for you. Inside the chest is a potion. This could come in handy later, so you decide to keep it.\n";
					(*player).potions = 1;
				}
				cout << "Knowing there isn't anything left but the chest, you decide to move on to the next room to the East.\n\n";
				return 1;
			}
			case 2:
			{
				cout << "You know from your previous experiences in this dungeon that the chest is obviously a trap, therefore you decide to pass up the opportunity for treasure and move to the next room towars the East.\n\n";
				return 1;
			}	
		}
	}
	return 1;
}

//Specification A2 - Add more rooms - This is the sixth and final room in the game.
int room6(struct entity *player)
{
	int donkeyPin = 0;
	cout << "As soon as you enter the sixth room, you see a door that leads outside. With all the bad things you've seen, you don't hesitate to sprint out the door. But just like the dungeon itself, it's not that easy. Before you even take 3 steps a giant green monster drops from above. You knew you were being watched the whole time. As the green giant lands, he lets out a deep roar and yells 'WHAT ARE YOU DOIN' IN MY SWAMP?!?!' This felt like a nightmare, for the one and only Shrek stood before you.\n\n";
	entity shrek;
	shrek.name = "Shrek";
	shrek.health = 150;
	shrek.attackPower = 25;
	startCombat(player, shrek);
	cout << "The mad ogre put up quite a fight but in the end he could not 'Do the roar.' or win. You came out victorious and you have never been happier to see the light of day. Looking around you see the exit and Shrek lying there cold and dead. You notice a 'Donkey pin' on his vest. Do you take it or leave it?\n\n";
	cout << "1. Take the pin as a trophy. \n2. Leave it so the rest of his kind know not to mess with " << (*player).name << " ever again.\n";
	cin >> donkeyPin;
	cout << endl;
	inputValidation2(donkeyPin);
	if (donkeyPin == 1)
	{
		cout << "You can now return to Lord Farquaad with proof you've emerged victorious and live a life of wealth and fame now.\n\n";
	}
	if (donkeyPin == 2)
	{
		cout << "You never were one to take a trophy and brag about it. You leave it so every evil being who sees it will know to not mess with the bloodthirtsy murderer " << (*player).name << ". The kill was more than enough in itself, and Lord Farquaad will just have to believe that you accomplished your task.\n\n";
	}
	return 1;
}

// Specification C3 - Input Validation
int inputValidation3(int input)
{
	while(input != 1 && input != 2 && input != 3)
	{
		cout << "Invalid entry. Try again.\n";
		cin.clear();
  	cin.ignore(10000,'\n');
		cin >> input;
	}
	return input;
}

int inputValidation2(int input)
{
	while(input != 1 && input != 2)
	{
		cout << "Invalid entry. Try again.\n";
		cin.clear();
  	cin.ignore(10000,'\n');
		cin >> input;
	}
	return input;
}