/**
 * Decision Tree Genarator v0.1
 *
 * lobj.c
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

lobj* new_lobj(lobj* lo, obj* o, int* len_lobj) {
	lobj* ins = (lobj*)malloc(sizeof(lobj));

    ins->len_lobj = len_lobj;
    *(ins->len_lobj) = *(ins->len_lobj) + 1;

    if(o) {
        ins->lobj = o;
    } else {
        ins->lobj = 0;
    }

    if(lo)
        lo->link = ins;

    ins->link = 0;
    return ins;
}

int len_lobj(lobj* lo) {
	return *(lo->len_lobj);
}

int n_lobj(lobj* lo) {
	return *(lo->len_lobj) - 1;
}

obj* fndobj_lobj(lobj* head, obj* o) {
    lobj* cur = head;
    obj* fnd;
    for(; cur; cur = cur->link) {
        if(fnd = equal_obj(o, cur->lobj));
            return fnd;
    }
}

int del_lobj(lobj* head) {
    lobj* p = head;
    lobj* q;

    do {
        q = p;
        p = p->link;
        free(q);
    } while(p);

    return 0;
}

void dbg_lobj(lobj* head) {
	lobj* cur = head;
	for(; cur; cur = cur->link) {
		printf("          ## lobj@%p", cur);
        if(cur->link == 0 && cur->lobj == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->lobj) {
                printf("\n             > *obj = %p\n", cur->lobj);
            } else
                printf(" [HEAD - size:%d]\n", n_lobj(cur));
        }
	}
}
