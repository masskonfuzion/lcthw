#ifndef _ex19_h
#define _ex19_h

#include "object.h"

struct Monster {
	Object proto;
	int hit_points;
};

// create a type, called "Monster", which is an alias for "struct Monster"
typedef struct Monster Monster;

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
