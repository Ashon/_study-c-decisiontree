/**
 * Decision Tree Genarator v0.1
 *
 * prop.c
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
 * new_prop(prop*, int*, int*)
 *
 * @description
 *    makes a new prop instance link of p.
 *
 * @param
 *    p - target prop
 *    val - integer value
 *    len_prop - # of property (indirect)
 *               equals # of attribute.
 *
 * @return
 *    prop* - new prop instance's pointer.
 */
prop* new_prop(prop* p, int* val, int* len_prop) {
    prop* ins = (prop*)malloc(sizeof(prop));
    ins->len_prop = len_prop;
    *(ins->len_prop) = *(ins->len_prop) + 1;

    if(val) {
        ins->tag = (int*)malloc(sizeof(int));
        *(ins->tag) = 0;

        ins->val = (int*)malloc(sizeof(int));
        *(ins->val) = *(val);
    } else {
        ins->val = 0;
        ins->tag = 0;
    }

    if(p)
        p->link = ins;

    ins->link = 0;
    return ins;
}

/**
 * len_prop(prop*)
 *
 * @descriptinon
 *    returns # of prop node. (include empty head node)
 *
 * @param
 *    p - prop
 *
 * @return
 *    int - # of prop node
 */
int len_prop(prop* p) {
    return *(p->len_prop);
}

/**
 * n_prop(prop*)
 *
 * @description
 *    returns # of valid prop node.
 *
 * @param
 *    p - prop*
 *
 * @return
 *    int - # of valid prop node.
 */
int n_prop(prop* p) {
    return *(p->len_prop) - 1;
}

int get_prop(prop* p) {
    return *(p->val);
}

int del_prop(prop* head) {
    prop* p = head;
    prop* q;
    do {
        q = p;
        p = p->link;

        if(q->val)
            free(q->val);

        if(q->tag)
            if(0 < *(q->tag))
                *(q->tag) = *(q->tag) - 1;
            else
                free(q->tag);

        free(q);
    } while(p);
    return 0;
}

void dbg_prop(prop* head) {
    prop* cur = head;

    for(; cur; cur = cur->link) {
        printf("     ## prop@%p", cur);
        if(cur->link == 0 && cur->val == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->val)
                printf("\n        > val = %d\n", *(cur->val));
            else
                printf(" [HEAD - size:%d]\n", n_prop(cur));
        }
    }
}
