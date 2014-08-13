#ifndef _object_h
#define _object_h


// create a type, called Direction, which is actually an enum of directions
typedef enum {
	NORTH, SOUTH, EAST, WEST
} Direction;

typedef struct {
	// Description (string)
	char *description;
	
	//function ptr -- initiailize self 
	// *init is a function; so init is a pointer to a function
	//(self is a void pointer, which can point to any type of data)
	int (*init) (void *self);
	
	//function ptr -- describe self
	void (*describe) (void *self);
	
	//function ptr -- destroy
	void (*destroy) (void *self);
	
	//function ptr -- move object in a particular direction
	// *move is a function; move is the pointer to the function
	// *move returns a void pointer
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
// NEW wraps a function call to Object_new(sizeof(T), T##Proto, N);
// T##Proto concatenates the parameter, T, with "Proto" (that is what ## does)
// So, if T is "MyParam", then T##Proto is MyParamProto
// T is a data type or a struct

#define _(N) proto.N
// Replace _(N) with "proto.N", so that if N is "MyWhatever", then _(N) changes to proto.MyWhatever

#endif
