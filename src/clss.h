/**
 * Decision Tree Genarator v0.1
 *
 * clss.h
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

/*
 * ADT - clss
 */
typedef struct clss_ {
    int* len_clss; // indirect
    char* name;
    struct clss_* link;
} clss;

// function table of clss
clss* new_clss(clss*, char*, int*);
int len_clss(clss*);
int del_clss(clss*);
void dbg_clss(clss*);

