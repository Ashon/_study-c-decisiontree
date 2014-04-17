/**
 * Decision tree generator
 *
 * stbl.c
 *
 * @author juwon.lee
 *
 * @date 2014-04-17
 *
 * mit licensed.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "adt_dtree.h"

stbl* new_stbl(stbl* st, attr* attr_clss, attr* attr_node) {
    stbl* ins = (stbl*)malloc(sizeof(stbl));
    scel* cur_scel;

    clss* cur_clss;
    clss* cur_node;

    // printf("new_stbl : check condition :: st && attr_clss && attr_node.. ");
    if(st && attr_clss->name && attr_node->name) {
        // printf("true.\n");
        // printf("new_stbl : ins->attr_clss = attr_clss ..");
        ins->attr_clss = attr_clss;
        // printf("complete.\n");
        // printf("new_stbl : ins->attr_node = attr_node ..");
        ins->attr_node = attr_node;
        // printf("complete.\n");
        
        // printf("new_stbl : make head node :: ..");
        ins->node_scel = new_scel(0, 0, 0);

        cur_scel = ins->node_scel;
        // printf("complete.\n");

        cur_clss = ins->attr_clss->node_clss;
        for(; cur_clss; cur_clss = cur_clss->link) {
            if(cur_clss->name) {
                // printf("new_stbl : loop 1 ::\n");
                // printf("new_stbl : cur_node = ins->attr_node->node_clss->link.. ");
                cur_node = ins->attr_node->node_clss;
                // printf("complete.\n");
                for(; cur_node; cur_node = cur_node->link)
                    if(cur_node->name) {
                        printf("%s -- %s : \n", cur_clss->name, cur_node->name);
                        cur_scel = new_scel(cur_scel, cur_clss, cur_node);
                        dbg_lobj(cur_scel->node_lobj);
                    }
            }
        }
    } else {
        // printf("false.\n");
        ins->attr_clss = 0;
        ins->attr_node = 0;
        ins->node_scel = 0;
    }
    // printf("generated %p\n", ins);
    if(st)
        st->link = ins;
    ins->link = 0;

    return ins;
}

int len_stbl(stbl* s) {
    return 0;
}

int n_stbl(stbl* s) {
    return 1;
}

int nrow_stbl(stbl* s) {
    return n_clss(s->attr_clss->node_clss);
}

int ncol_stbl(stbl* s) {
    return n_clss(s->attr_node->node_clss);
}

int del_stbl(stbl* head) {
    stbl* p = head;
    stbl* q;
    do {
        q = p;
        p = p->link;
        if(q->node_scel)
            del_scel(q->node_scel);
        free(q);
    } while(p);
}

void dbg_stbl(stbl* st) {
    stbl* cur = st;
    for(; cur; cur = cur->link) {
        printf("## stbl@%p", cur);
        if(!cur->link && !cur->node_scel)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->attr_clss && cur->attr_clss->name)
                printf("\n   > attr_clss = %p[ %s ]\n",
                        cur->attr_clss, cur->attr_clss->name);
            if(cur->attr_node && cur->attr_node->name)
                printf("   > attr_node = %p[ %s ]\n",
                        cur->attr_node, cur->attr_node->name);
            if(cur->node_scel) {
                printf("   > node_scel = %p\n", cur->node_scel);
                dbg_scel(cur->node_scel);
            } else
                printf(" [HEAD - size:%d]\n", n_stbl(cur));
        }
    }
}











