#ifndef _object_h
#define _object_h


// create a type, called Direction, which is actually an enum of directions
typedef enum {
	NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
	// Description (string)
	char *description;
	
	//function ptr -- initiailize self (self is a void pointer)
	int (*init) (void *self);
	
	//function ptr -- describe self
	void (*describe) (void *self);
	
	//function ptr -- destroy
	void (*destroy) (void *self);
	
	//function ptr -- move object in a particular direction
	void *(*move) (void *self, Direction direction);
	
	//function ptr -- attack (inflict damage on the enemy)
	int (*attack) (void *self, int damage);
} Object;


int Object_init(void *self);

void Object_destroy(void *self);

void Object_describe(void *self);

void *Object_move(void *self, Direction direction);

int Object_attack(void *self, int damage);

void *Object_new(size_t size, Object proto, char *description);

// The next 2 lines are macros
#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif
