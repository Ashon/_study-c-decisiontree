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

#include "ADT_DecisionTree.h"

int main(int argc, char *argv[]) {
    DecisionTable* t;
    FILE* fp;

    fp = fopen(argv[1], "r");
    if(fp) {
        t = newDecisionTable(t, fp);
        
        dbgDecisionTable(t);

        delDecisionTable(t);
        fclose(fp);
    }

    return 0;
}
