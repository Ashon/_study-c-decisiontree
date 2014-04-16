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
    FILE* fp;
    
    fp = fopen(fname, "r");

    if(fp) {
        t = new_dtree(t, fp);
        
        dbg_attr(t->node_attr);
        //dbg_obj(t->node_obj);
        
        del_dtree(t);
        fclose(fp);
    }

    return 0;
}
