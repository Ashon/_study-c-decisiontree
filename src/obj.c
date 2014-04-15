/**
 * Decision Tree Genarator v0.1
 *
 * obj.c
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

#include "obj.h"

// ======== Implementation of ADT ========

/**
 * new_obj(obj*, char*, int*)
 *
 * @description
 *    makes a new obj ins link of o.
 *
 * @param
 *    o - target obj
 *    str - formed string such as "1,2,3,4"
 *    len_obj - # of object (indirect)
 *    len_prop - # of property (indirect)
 *               equals # of attribute.
 *
 * @return
 *    obj* - new obj instance's pointer.
 */
obj* new_obj(obj* o, char* str, int* len_obj) {
    obj* ins = (obj*)malloc(sizeof(obj));
    prop* cur;
    char* buf;
    int val;
    // todo for new

    ins->len_obj = len_obj;
    *(ins->len_obj) = *(ins->len_obj) + 1;

    if(str) {
        ins->len_prop = (int*)malloc(sizeof(int));
        *(ins->len_prop) = 0;

        ins->node_prop = new_prop(0, 0, ins->len_prop);
        cur = ins->node_prop;

        buf = strtok(str, ",");
        do {
            val = atoi(buf);
            cur = new_prop(cur, &val, ins->len_prop);
        } while(buf = strtok(0, ","));

    } else {
        ins->node_prop = 0;
    }
    
    if(o)
        o->link = ins;
    ins->link = 0;

    return ins;
}

/**
 * len_o(obj*)
 *
 * @description
 *    returns # of obj
 *
 * @param
 *    o - obj
 *
 * @return
 *    int - # of obj node.
 */
int len_obj(obj* o) {
    return *(o->len_obj);
}

/**
 * del_o
 * 
 * @description
 *    free memory all of obj's node.
 * 
 * @param
 *    o - head of obj node.
 *
 * @return
 *    0
 */
int del_obj(obj* head) {
    obj* p = head;
    obj* q;

    do {
        q = p;
        p = p->link;
        // todo for free q.
        if(q->node_prop)
            del_prop(q->node_prop);
        free(q);
    } while(p);

    return 0;
}

/**
 * dbg_o
 * 
 * print log of object node.
 */
void dbg_obj(obj* head) {
    obj* cur = head;
    int i;

    for(; cur; cur = cur->link) {
        printf("## obj@%p", cur);
        if(!cur->link && !cur->node_prop)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            printf("\n");
            if(cur->node_prop) {
                printf("   > node_prop = %p\n", cur->node_prop);
                dbg_prop(cur->node_prop);
            } else
                printf(" [HEAD - len:%d]\n", *(cur->len_obj)); 
        }
    }
}

