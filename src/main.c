/**
 * Decision Tree Genarator v0.1
 *
 * main.c
 *
 * @author juwon.lee
 * @date 2014-04-11
 *
 * mit licensed.
 *
 */

#include <stdio.h>

#include "adt_dtree.h"

int main() {

    char fname[] = "./dat/train.dat";

    dtree* t;
    attr* t_attr_clss;
    attr* t_attr_node;
    attr* cur_attr;
    stbl* st;
    stbl* cur_st;

    FILE* fp;
    
    fp = fopen(fname, "r");

    if(fp) {
        t = new_dtree(t, fp);
        // generate stbl;
       
        st = new_stbl(0, 0, 0);
        cur_st = st;

        // get class attribute
        t_attr_clss = get_clss(t);

     
        cur_attr = t->node_attr;
        for(; cur_attr; cur_attr = cur_attr->link) {
            if(cur_attr != t_attr_clss) {
                if(cur_attr->name)
                    cur_st = new_stbl(cur_st, t_attr_clss, cur_attr);
            }
        }

        dbg_dtree(t);
        dbg_stbl(st);
        del_stbl(st);
        del_dtree(t);
        fclose(fp);
    }

    return 0;
}
