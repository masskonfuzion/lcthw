#ifndef _ex19_h
#define _ex19_h

#include "object.h"

// Create a Monster struct (called struct Monster)
struct Monster {
	// proto is the "Object" object. Each struct that will behave as an "Object"
	// needs to have an Object called "proto" (and it must be called "proto" so
	// that the macros defined in object.h to work.
	Object proto;
	
	int hit_points;
};

// create a type, called "Monster", which is an alias for "struct Monster"
typedef struct Monster Monster;

// These functions will "belong" to the Monster "object"
// That is, the Object struct has pointers to functions for init, attack, move,
// etc.  So, e.g., the Monster_attack function will be the callback for the 
// Object.attack pointer (i.e., the function that is called when you call attack
// on an instance of Object)
int Monster_attack(void *self, int damage);
int Monster_init(void *self);

struct Room {
	Object proto;

	Monster *bad_guy;

	//define rooms -- note that we have to use "struct Room" here, because we have not typedef'ed the struct yet
	struct Room *north;
	struct Room *south;
	struct Room *east;
	struct Room *west;
};

// define a type, Room, which is an alias for struct Room (this allows us to simply declare a Room r, instead of having to declare struct Room r
typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

struct Map {
	Object proto;
	Room *start;
	Room *location;
};


// As usual, alias "struct Map" as simply "Map"
typedef struct Map Map;

void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif
