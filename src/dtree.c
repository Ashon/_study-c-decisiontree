/**
 * Decision Tree Genarator v0.1
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

dtree* new_dtree(dtree* t, FILE* fp) {
    char *buf = (char*)calloc(MAX_BUF, sizeof(char));
    int cond = -1;

    attr* cur_attr;
    obj* cur_obj;
    stbl* cur_stbl;

    dtree* ins = (dtree*)malloc(sizeof(dtree));

    ins->len_attr = (int*)malloc(sizeof(int));
    ins->len_obj = (int*)malloc(sizeof(int));
    ins->len_stbl = (int*)malloc(sizeof(int));

    *(ins->len_attr) = 0;
    *(ins->len_obj) = 0;
    *(ins->len_stbl) = 0;

    ins->node_attr = new_attr(0, 0, ins->len_attr);
    ins->node_obj = new_obj(0, 0, ins->len_obj);
    ins->node_stbl = new_stbl(0, 0, 0, ins->len_stbl);

    cur_attr = ins->node_attr;
    cur_obj = ins->node_obj;
    cur_stbl = ins->node_stbl;

    cond++;

    while(fgets(buf, MAX_BUF, fp)) {
       if(0 < strlen(buf))
            buf[strlen(buf) - 1] = '\0';
        if(!strcmp(buf, "#")) {
            cond++;
            continue;
        }

        // generate attribute
        if(cond == 1) {
            cur_attr = add_attr(ins, cur_attr, buf);
        }

        // generate object
        if(cond == 2) {
            cur_obj = add_obj(ins, cur_obj, buf);
        }
    }
    
    cur_stbl = gen_stbl(ins);

    free(buf);
    
    t = ins;
    return ins;
    
}

attr* add_attr(dtree* t, attr* cur_attr, char* buf) {
    cur_attr = new_attr(cur_attr, buf, t->len_attr);

    return cur_attr;
}

attr* get_clss_attr(dtree* t) {
    attr* cur = t->node_attr->link;
    for(; cur; cur = cur->link)
        if(*(cur->type) == AT_TYPE_TARGET)
            return cur;
    return 0;
}

obj* add_obj(dtree* t, obj* cur_obj, char* buf) {
    // t's cursor
    attr* cur_attr;
    clss* cur_clss;
    lobj* cur_lobj;

    // cur_obj's prop cursor
    prop* cur_prop;

    cur_obj = new_obj(cur_obj, buf, t->len_obj);
    cur_prop = cur_obj->node_prop->link;
    int idx;
    int count = 0;

    cur_attr = t->node_attr;
    
    for(; cur_attr; cur_attr = cur_attr->link) {
        if(cur_attr->node_clss) {
            cur_clss = cur_attr->node_clss->link;
            idx = 0;
            for(; cur_clss; cur_clss = cur_clss->link) {
                cur_lobj = cur_clss->node_lobj;

                while(cur_lobj->link)
                    cur_lobj = cur_lobj->link;

                if(idx == *(cur_prop->val)) {
                    cur_lobj = new_lobj(cur_lobj, cur_obj, cur_clss->len_lobj);
                    break;
                }
                idx++;
            }
            cur_prop = cur_prop->link;
        }
    }
    return cur_obj;
}

stbl* gen_stbl(dtree* t) {
    stbl* cur_stbl = t->node_stbl;
    attr* attr_clss = get_clss_attr(t);
    attr* cur_attr = t->node_attr;

    for(; cur_attr; cur_attr = cur_attr->link) {
        if(cur_attr != attr_clss) {
            if(cur_attr->name)
                cur_stbl = new_stbl(cur_stbl, attr_clss, cur_attr, t->len_stbl);
        }
    }
    return t->node_stbl;
}

int del_dtree(dtree* t) {
    del_attr(t->node_attr);
    del_obj(t->node_obj);
    del_stbl(t->node_stbl);

    free(t->len_attr);
    free(t->len_obj);
    free(t->len_stbl);

    free(t);
    return 0;
}

void dbg_dtree(dtree* t) {
    printf("## dtree@%p\n", t);
    printf("# node_attr = %p\n", t->node_attr);
    dbg_attr(t->node_attr);
    printf("# node_obj = %p\n", t->node_obj);
    dbg_obj(t->node_obj);
    printf("# node_stbl = %p\n", t->node_stbl);
    dbg_stbl(t->node_stbl);
}
