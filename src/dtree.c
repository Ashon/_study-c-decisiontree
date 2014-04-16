/**
 * Decision Tree Genarator v0.1
 *
 * 
 * dtree.c
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

#include "adt_dtree.h"

/**
 * ADTs for decision tree generator.
 *
 * @dependency
 *  +-> dtree : decision tree
 *    |
 *    +---> int* len_attr : length of attribute node (direct)
 *    +---> int* len_obj : length of object node (direct)
 *    |
 *    +---> attr* node_attr : [single list]
 *    |   |
 *    |   +---> int* len_attr : points to [dtree->len_attr] (indirect)
 *    |   +---> char* name : attribute name
 *    |   +---> int* type : attribte type
 *    |   +---> int* len_clss : length of attribute's class.
 *    |   | 
 *    |   +---> clss* node_clss : [single list]
 *    |   |   |
 *    |   |   +---> int* len_clss : points to [attr->len_clss] (indirect)
 *    |   |   +---> char* name : class name
 *    |   |   |
 *    |   |   +---> clss* link : next clss node.
 *    |   |
 *    |   +-> *link : next attr node.
 *    |
 *    +---> obj* node_obj : [single list]
 *        |
 *        +---> int* len_obj : points to [dtree->len_obj] (indirect)
 *        +---> int* len_prop : # of property (direct)
 *        |
 *        +---> prop* node_prop : [single list]
 *        |   |
 *        |   +---> int* len_prop : points to [obj->len_prop] (indirect)
 *        |   +---> int* val : property value.
 *        |   |
 *        |   +---> prop* link : next prop node.
 *        |
 *        +---> obj* link : next obj node.
 *
 * @constraint
 *    - # of obj's property equals to # of attr:
 *    - all of [single list]s have empty head node.
 *        [HEAD] -> [node] -> ... -> 0
 */

// ======== Implementation of ADT ========

dtree* new_dtree(dtree* t, FILE* fp) {
    char *buf = (char*)calloc(MAX_BUF, sizeof(char));
    int cond = -1;

    attr* cur_attr;
    obj* cur_obj;

    dtree* ins = (dtree*)malloc(sizeof(dtree));

    ins->len_attr = (int*)malloc(sizeof(int));
    ins->len_obj = (int*)malloc(sizeof(int));

    *(ins->len_attr) = 0;
    *(ins->len_obj) = 0;

    ins->node_attr = new_attr(0, 0, ins->len_attr);
    ins->node_obj = new_obj(0, 0, ins->len_obj);

    cur_attr = ins->node_attr;
    cur_obj = ins->node_obj;

    cond++;

    while(fgets(buf, MAX_BUF, fp)) {
       if(0 < strlen(buf))
            buf[strlen(buf) - 1] = '\0';
        if(!strcmp(buf, "#")) {
            cond++;
            continue;
        }

        if(cond == 1) {
            cur_attr = new_attr(cur_attr, buf, ins->len_attr);
        }

        if(cond == 2) {
            cur_obj = new_obj(cur_obj, buf, ins->len_obj);
        }
    }
    free(buf);
    
    t = ins;
    return ins;
    
}

int del_dtree(dtree* t) {
    del_attr(t->node_attr);
    del_obj(t->node_obj);

    free(t->len_attr);
    free(t->len_obj);

    free(t);
    return 0;
}

void dbg_dtree(dtree* t) {
    printf("## dtree@%p\n", t);
    printf("   > node_attr = %p\n", t->node_attr);
    dbg_attr(t->node_attr);
    printf("   > node_obj = %p\n", t->node_obj);
    dbg_obj(t->node_obj);
}

