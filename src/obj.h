/**
 * Decision Tree Genarator v0.1
 *
 * obj.h
 *
 * @author juwon.lee
 * @date 2014-04-11
 *
 * mit licensed.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prop.h"

// ======== Define ADT ========

/**
 * ADT - obj
 */
typedef struct obj_ {
    int* len_obj; // indirect
    int* len_prop; // direct
    prop* node_prop;
    // float* prop_float;
    struct obj_* link;
} obj;

// function table of obj
obj* new_obj(obj*, char*, int*);
int len_obj(obj*);
int del_obj(obj*);
void dbg_obj(obj*);

