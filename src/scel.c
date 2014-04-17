/**
 * Decision tree generator
 *
 * scel.c
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

/**
 * new_scel(scel*, clss*, clss*)
 *
 * @description
 *    ss
 *
 * @param
 *    s - scel pointer.
 *    ncls - attr node's head clss node.
 *    ccls - attr class's head clss node.
 *
 * @return
 *    scel* -
 *
 */
scel* new_scel(scel* s, clss* ccls, clss* ncls) {
    scel* ins = (scel*)malloc(sizeof(scel));
    lobj* cur_ins;
    obj* obj_fnd;

    // cursor of attr_node->node_clss->node_lobj (col)
    lobj* cur_n_lobj; 

    // cursor of attr_class->node_clss->node_lobj (row)
    lobj* cur_c_lobj;

    if(s) {
        ins->len_lobj = (int*)malloc(sizeof(int));
        *(ins->len_lobj) = 0;

        ins->node_lobj = new_lobj(0, 0, ins->len_lobj);

        // initialize lobj cursor of ins->node_lobj ..
        cur_ins = ins->node_lobj;

        cur_c_lobj = ccls->node_lobj;
        for(; cur_c_lobj; cur_c_lobj = cur_c_lobj->link){
            cur_n_lobj = ncls->node_lobj;
            for(; cur_n_lobj; cur_n_lobj = cur_n_lobj->link) {
                obj_fnd = 0;
                obj_fnd = fndobj_lobj(cur_c_lobj, cur_n_lobj->lobj);    
                if(obj_fnd)
                    cur_ins = new_lobj(cur_ins, obj_fnd, ins->len_lobj);
            }
        }
    } else {
        ins->len_lobj = 0;
        ins->node_lobj = 0;
    }

    if(s)
        s->link = ins;
    ins->link = 0;

    return ins;
}

int len_scel(scel* c) {
    return 0;
}

int n_scel(scel* c) {
    return 1;
}

int del_scel(scel* head) {
    scel* p = head;
    scel* q;
    do {
        q = p;
        p = p->link;
        if(q->node_lobj)
            del_lobj(q->node_lobj);
        free(q->len_lobj);
        free(q);
    } while(p);
    return 0;
}

void dbg_scel(scel* head) {
    scel* cur = head;
    for(; cur; cur = cur->link) {
        printf("    ## scel@%p", cur);
        if(!cur->link && !cur->node_lobj)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->node_lobj)
                printf("\n        > value = %d\n", n_lobj(cur->node_lobj));
            else 
                printf(" [HEAD - size:%d]\n", n_scel(cur));
        }
    }
}
