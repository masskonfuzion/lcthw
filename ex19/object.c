#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

// =============================================================================
// Set up functions to manage the Object struct
// =============================================================================

// Destroy the object
// Remember that the function takes a void pointer, which points to the
// actual memory to be manipulated.
void Object_destroy(void *self)
{
	// remember Object is a struct that is defined in object.h
	// assign obj to the self pointer (self is the actual object in memory)
	Object *obj = self;
	
	// if obj exists, then free its memory
	if(obj) {
		// if description exists, delete it
		if (obj->description) free(obj->description);
		// delete obj
		free(obj);
	}
}


void Object_describe(void *self)
{
	Object *obj = self;
	printf("%s.\n", obj->description);
}

int Object_init(void *self)
{
	//do nothing really -- this is for the object-orientedness of it all
	return 1;
}

void *Object_move(void *self, Direction direction)
{
	printf("You can't go that direction.\n");
	return NULL; // (in C++, the return would be nullptr)
}

int Object_attack(void *self, int damage)
{
	printf("You can't attack that.\n");
	return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
	//set up the default functions, in case they aren't set
	//(i.e., we're setting the function pointers, so the object's 'member' functions
	//will exist and be defined
	
	//if proto has an init function defined (init is a pointer, so it could 
	//point to NULL, but it could also point to a legit function.  The same
	//goes for all of the other functions pointers in this function
	if (!proto.init) proto.init = Object_init;
	if (!proto.describe) proto.describe = Object_describe;
	if (!proto.destroy) proto.destroy = Object_destroy;
	if (!proto.attack) proto.attack = Object_attack;
	if (!proto.move) proto.move = Object_move;
	
	//this may seem weird, but we can make a struct of one size, then point a different
	//pointer at it, to "cast" it
	Object *el = calloc(1, size); // create an empty array with 1 element, size bytes
	*el = proto; // Set the value of el to proto (or, point el at proto)
	// or more accurately, the previous line says "assign the proto struct to whatever el points at" (??)
	
	
	// copy the description over
	el->description = strdup(description);
	
	// initialize it with whatever we were given
	if (!el->init(el)) {
		//If el->init did not return a valid pointer, then we failed..
		el->destroy(el);
		return NULL;
	} else {
		// all done, we made object of any type
		return el;
	}
}
