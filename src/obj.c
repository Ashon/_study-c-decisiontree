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

#include "adt_dtree.h"

/**
 * new_obj(obj*, char*, int*)
 *
 * @description
 *    makes a new obj instance link of o.
 *
 * @param
 *    o - target obj
 *    str - formed string such as "1,2,3,4"
 *    len_obj - # of object (indirect)
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

prop* obj_prop(obj* o, int idx) {
    int i;
    prop* cur;

    if(-1 < idx && idx < len_prop(o->node_prop)) {
        cur = o->node_prop;
        for(i = 0; i < idx; idx++)
            cur = cur->link;
        return cur;
    }

    return 0;
}
/**
 * len_o(obj*)
 *
 * @description
 *    returns # of obj. (include empty head node)
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
 * n_obj(obj*)
 *
 * @description
 *    returns # of valid obj node.
 *
 * @param
 *    o - obj*
 *
 * @return
 *    int - # of valid obj node.
 */
int n_obj(obj* o) {
    return *(o->len_obj) - 1;
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
        if(q->node_prop){
            del_prop(q->node_prop);
            free(q->len_prop);
        }
        
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
                printf(" [HEAD - size:%d]\n", n_obj(cur)); 
        }
    }
}

