/**
 * Decision Tree Genarator v0.1
 *
 * prop.h
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

// ======== Define ADT ========

/**
 * ADT - prop
 */
typedef struct prop_ {
    int* len_prop; // indirect
    int* val;
    struct prop_* link;
} prop;

// function table of prop
prop* new_prop(prop*, int*, int*);
int len_prop(prop*);
int get(prop*);
int del_prop(prop*);
void dbg_prop(prop*);

