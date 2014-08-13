//Exercise 19

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"

// ============================================================================
// Set up Monster object
// ============================================================================

// Monster attack
int Monster_attack(void *self, int damage)
{
	// Point monster at self 
	// (self is a void pointer -- i.e. a pointer at any data type. In this 
	// program, self will point at a Monster.  But note that the type Monster is
	// which itself is an alias/typedef for struct Monster (see ex19.h))
	Monster *monster = self;

	printf("You attack %s!\n", monster->_(description));

	monster->hit_points -= damage;

	if (monster->hit_points > 0) {
		printf("It is still alive.\n");
		return 0;
	} else {
		printf("It is dead!\n");
		return 1;
	}
}

// Monster init
int Monster_init(void *self)
{
	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

// Instantiate an Object called MonsterProto, and define the init and attack
// function callbacks (that is, MonsterProto.init is a pointer that points to
// the function, int Monster_init(void *self)).  Similarly, MonsterProto.attack
// is a pointer that points to int Monster_attack(void *self, int damage)
Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};

// ============================================================================
// Set up Room object
// ============================================================================

void *Room_move(void *self, Direction direction)
{
	Room *room = self;
	Room *next = NULL;

	if(direction == NORTH && room->north) {
		printf("You go north, into:\n");
		next = room->north;
	} else if (direction == SOUTH && room->south) {
		printf("You got south, into:\n");
		next = room->south;
	} else if (direction == EAST && room->east) {
		printf("You go east, into:\n");
		next = room->east;
	} else if (direction == WEST && room->west) {
		printf("You go west, into:\n");
		next = room->west;
	} else {
		printf("You can't go that direction.");
		next = NULL;
	}
	
	if (next) {
		next->_(describe) (next);
	}

	return next;

}

int Room_attack(void *self, int damage)
{
	Room *room = self;
	Monster *monster = room->bad_guy;

	if (monster) {
		monster->_(attack) (monster, damage);
		return 1;
	} else {
		printf("You flail in the air at nothing. Idiot.\n");
		return 0;
	}
}

Object RoomProto = {
	.move = Room_move,
	.attack = Room_attack
};


// ============================================================================
// Set up Map object
// ============================================================================

void *Map_move(void *self, Direction direction)
{
	Map *map = self;
	Room *location = map->location;
	Room *next = NULL;

	next = location->_(move) (location, direction);

	if (next) {
		map->location = next;
	}

	return next;
}


int Map_attack(void *self, int damage)
{
	Map* map = self;
	Room* location = map->location;

	return location->_(attack) (location, damage);

}


int Map_init(void *self)
{
	Map *map = self;

	// Make some rooms for a small map
	// (Notice our use of the NEW macro)
	
	// For example the following macro call, 
	// Room *hall = NEW(Room, "The great Hall"), expands to:
	// Room *hall = Object_new(sizeof(Room), RoomProto, "The great Hall")
	// RoomProto has already been defined above (of type Object).  RoomProto 
	// has the move and attack functions defined. Therefore, Object_new returns 
	// a pointer to a block of memory, which is the size of RoomProto, and
	// contains pointers to the programmer-defined function callbacks (given in
	// the struct definition for RoomProto), and also pointers to the 'default' 
	// functions for the Object struct, which are declared in object.h and 
	// defined in object.c. This is a way of implementing generic default
	// functions for the Object type, but allowing the programmer to override
	// the defaults. This is a hand-made interface, and this is also an
	// implementation of what C++ defines as virtual functions (I think).
	
	Room *hall = NEW(Room, "The great Hall");
	Room *throne = NEW(Room, "The throne room");
	Room *arena = NEW(Room, "The arena, with the minotaur");
	Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

	// Put the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");

	// Set up the map rooms
	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;
	kitchen->west = throne;

	//start the map and the character off in the hall
	map->start = hall;
	map->location = hall;

	return 1;

}

Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};


// ============================================================================
// Set up other program stuff
// ============================================================================

int process_input(Map *game)
{
	printf("\n> ");

	char ch = getchar();
	getchar(); //eat the ENTER key

	int damage = rand() % 4;

	switch(ch) {
		case -1:
			printf("Giving up? You suck.\n");
			return 0;
			break;

		case 'n':
			game->_(move) (game, NORTH);
			break;

		case 's':
			game->_(move) (game, SOUTH);
			break;

		case 'e':
			game->_(move) (game, EAST);
			break;

		case 'w':
			game->_(move) (game, WEST);
			break;

		case 'a':
			game->_(attack) (game, damage);
			break;

		case 'l':
			printf("You can go:\n");
			if (game->location->north) printf("NORTH\n");
			if (game->location->south) printf("SOUTH\n");
			if (game->location->east) printf("EAST\n");
			if (game->location->west) printf("WEST\n");
			break;

		default:
			printf("What?: %d\n", ch);

	}

	return 1;
}


int main(int argc, char *argv[])
{
	// Simple way to set up the random number generation
	srand(time(NULL));
	
	// Make our map to work with
	// (Note: this uses the NEW macro)
	Map *game = NEW(Map, "The Hall of the Minotaur.");

	printf("You enter the ");
	// notice the use of the _(N) macro from header.h
	game->location->_(describe) (game->location);

	while (process_input(game)) {
		// endless loop
	}

	return 0;
}
