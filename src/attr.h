/**
 * Decision Tree Genarator v0.1
 *
 * attr.h
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

#include "clss.h"

// predefined macros.
#define MAX_BUF 255

// attr type constants.
#define AT_TYPE_TARGET 0
#define AT_TYPE_BINARY 1
#define AT_TYPE_CATEGORICAL 2
#define AT_TYPE_CONTINUOUS 3

// ======== Define ADT ========

/*
 * ADT - attr
 */
typedef struct attr_ {
    int* len_attr; // indirect
    char* name;
    int* type;
    int* len_clss; // direct
    clss* node_clss;
    struct attr_ * link;
} attr;

// function table of attr
attr* new_attr(attr*, char*, int*);
int len_attr(attr*);
int del_attr(attr*);
void dbg_attr(attr*);

