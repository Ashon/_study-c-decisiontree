/**
 * Decision Tree Genarator v0.1
 *
 * clss.c
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
 * new_clss(clss*, char*, int*)
 *
 * @description
 *    makes a new clss instance link of *clss.
 *
 * @param
 *    c - clss pointer to attach a new clss
 *    str - name of new class instance
 *    len_clss - # of clss
 *
 * @return
 *    clss* - new clss instance's pointer
 */
clss* new_clss(clss* c, char* str, int* len_clss) {
    clss* ins;
    ins = (clss*)malloc(sizeof(clss));

    ins->len_clss = len_clss;
    *(ins->len_clss) = *(ins->len_clss) + 1;

    if(str) {
        ins->name = (char*)calloc(strlen(str) + 1, sizeof(char));
        strcpy(ins->name, str);
    } else
        ins->name = 0;

    ins->len_lobj = (int*)malloc(sizeof(int));
    *(ins->len_lobj) = 0;

    ins->node_lobj = new_lobj(0, 0, ins->len_lobj);

    if(c)
        c->link = ins;
    ins->link = 0;

    return ins;
}

/**
 * len_clss(clss*)
 * 
 * @description
 *    returns # of clss.
 *
 * @param
 *    c - clss
 *
 * @return
 *    int - # of clss
 */
int len_clss(clss* c) {
    return *(c->len_clss);
}

/**
 * n_clss(clss*)
 *
 * @description
 *    returns # of valid clss node.
 *
 * @param
 *    c - clss*
 *
 * @return
 *    int - # of valid clss node.
 */
int n_clss(clss * c) {
    return *(c->len_clss) - 1;
}

/**
 * del_clss(clss*)
 *
 * @description
 *    free memory all of clss
 *
 * @param
 *    head - head of clss.
 *
 * @return
 *    0 - returns 0 when 'free' finished.
 */
int del_clss(clss* head) {
    clss* p;
    clss* q;

    p = head;

    do {
        q = p;
        p = p->link;

        if(q->node_lobj)
            del_lobj(q->node_lobj);

        if(q->name)
            free(q->name);

        free(q->len_lobj);
        free(q);
    } while(p);

    return 0;
}

void dbg_clss(clss* head) {
    clss* cur = head;
    for(; cur; cur = cur->link) {
        printf("     ## clss@%p", cur);
        if(cur->link == 0 && cur->name == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->name && cur->node_lobj) {
                printf("\n        > name = %s\n", cur->name);
                printf("        > lobj = %p\n", cur->node_lobj);
                dbg_lobj(cur->node_lobj);
            } else
                printf(" [HEAD - size:%d]\n", n_clss(cur));
        }
    }
}
