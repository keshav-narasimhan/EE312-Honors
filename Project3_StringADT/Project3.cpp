// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Keshav Narasimhan
// ______
// Slip days used: 0
// Spring 2021
// Copy and paste this file at the top of all your submitted source code files.  Do not turn this in by itself.


#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    
    // allocate new UTString
    UTString *ut_string = (UTString*)malloc(sizeof(UTString));  

    // find length of string to be stored in UTString  
    int str_length = strlen(src); 

    // set UTString length to be length of src
    // set UTString initial capacity to length of src
    ut_string->length = str_length;    
    ut_string->capacity = str_length;
    
    // still have to initialize ut_string's actual string
    // allocate string on heap --> returns a pointer that pts to a char array that is length of src + null (1 byte) + check (4 bytes)
    ut_string->string = (char*)malloc(sizeof(char) * (str_length + 5));     

    // initialize UTString's string with src
    for (int a = 0; a < str_length; a++)
    {
        ut_string->string[a] = src[a];
    }

    // make sure to null terminate the UTString
    ut_string->string[str_length] = '\0';
    
    // before returning ut_string, make sure to use CHECK macro
    // this will add ~0xdeadbeef to end of string
    CHECK(ut_string) = SIGNATURE;

    return ut_string;

}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    
    // assert: aborts program is condition isn't true
    assert(isOurs(s));

    // return the length of UTString
    return s->length;

}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    
    assert(isOurs(s));

    // initialize new var (str_curr_length) that will be used as index for concatenation/holding new length of UTString
    // initialize new var (index) that will be the index for suffix
    int str_curr_length = s->length;
    int index = 0;

    while (s->capacity > str_curr_length && suffix[index] != '\0')
    {
        s->string[str_curr_length] = suffix[index];
        str_curr_length++;
        index++;
    }

    // update string length
    s->length = str_curr_length;

    // place null terminator at end of UTString
    s->string[str_curr_length] = '\0';

    // use CHECK macro to add the special signature
    CHECK(s) = SIGNATURE;

    return s;

}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    
    assert(isOurs(dst));

    int str_new_length = 0;
    for (int a = 0; a < dst->capacity; a++)
    {
        if (src[a] == '\0')
        {
            // exit loop if all have src has been copied
            break;
        }

        // copy src's chars into UTString's string
        dst->string[a] = src[a];

        // increment the new length of the UTString
        str_new_length++;
    }

    // update UTString length
    dst->length = str_new_length;

    // insert null temrinator
    dst->string[str_new_length] = '\0';

    // use CHECK macro for inserting signature
    CHECK(dst) = SIGNATURE;

    return dst;

}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {

    assert(isOurs(self));

    // free UTString's string first bc it was allocated last
    free(self->string);

    // free UTString itself
    free(self);

}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    
    assert(isOurs(s));

    // if current UTString has enough capacity, don't do anything
    if (s->capacity >= new_capacity)
    {
        return s;
    }

    // update UTString's capacity to new_capacity
    // reallocate string based on new capacity
    s->capacity = new_capacity;
    s->string = (char*)realloc(s->string, sizeof(char)*(new_capacity + 5));
    
    return s;

}
