/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new() {
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL) {
        allocation_failed();
    }
    v.data[0] = 0;
    return v;
}

/* Create a new vector with a size (length) of 1
   and set its single component to zero... the
   RIGHT WAY */
vector_t *vector_new() {
    /* Declare what this function will return */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    /* YOUR CODE HERE */
    retval = (vector_t *) malloc(sizeof(vector_t));

    /* Check our return value to make sure we got memory */
    /* YOUR CODE HERE */
    if (retval == NULL) {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
       /* YOUR CODE HERE */
    retval->size = 1;
    retval->data = (int *) malloc(sizeof(int) * retval->size);

    /* Check the data attribute of our vector to make sure we got memory */
    /* YOUR CODE HERE */
    if (retval->data == NULL) {
        free(retval);				//Why is this line necessary?
        allocation_failed();
    }

    /* Complete the initialization by setting the single component to zero */
    /* YOUR CODE HERE */
    retval->data[0] = 0;
    
    /* and return... */
    return retval;
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    /* YOUR CODE HERE */
    if (loc < v->size) {
        return v->data[loc];
    } else {
        return 0;
    }
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) {
    /* YOUR SOLUTION HERE */
    /* Free the memory of data */
    free(v->data);
    /* Free the memory of vector */
    free(v);
}

int get_size(vector_t *v) {
    return v->size;
}
/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */

    /* YOUR SOLUTION HERE */
    /* Check if you can put the value in the current *v */
    if (loc < (v->size)) {
        v->data[loc] = value;
        return;
    }

    /* Allocate a new memory */
    int *new = (int *) malloc(sizeof(int) * ((int) loc + 1));

    /* Check if memory is NULL */
    if (new == NULL) {
        allocation_failed();
    }

    /* Fill with zero */
    for (int i = 0; i < loc + 1; i++) {
        new[i] = 0;
    }

    /* Fill with the previous values */
    for (int i = 0; i < v->size; i++) {
        new[i] = v->data[i];
    }

    free(v->data); // free previous data integer array
    v->data = new; // assign v-> data with new
    v->data[loc] = value; // assign value at loc
    v->size = loc + 1; // update size
    return;

    
}