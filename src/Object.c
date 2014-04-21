/**
 * Decision Tree Genarator v0.1
 *
 * Object.c
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

#include "ADT_DecisionTree.h"

/**
 * newObject(Object*, char*, int*)
 *
 * @description
 *    makes a new Object instance link of o.
 *
 * @param
 *    o - target Object
 *    str - formed string such as "1,2,3,4"
 *    objectLength - # of Objectect (indirect)
 *
 * @return
 *    Object* - new Object instance's pointer.
 */
Object* newObject(DecisionTable* t, Object* o, char* str) {
    Object* ins = (Object*)malloc(sizeof(Object));
    Property* cur;
    char* buf;
    int val;
    // todo for new

    ins->objectLength = t->objectLength;
    *(ins->objectLength) = *(ins->objectLength) + 1;

    if(str) {
        ins->propertyLength = (int*)malloc(sizeof(int));
        *(ins->propertyLength) = 0;

        ins->propertyList = newProperty(ins, 0, 0);
        cur = ins->propertyList;

        buf = strtok(str, ",");
        do {
            val = atoi(buf);
            cur = newProperty(ins, cur, &val);
        } while(buf = strtok(0, ","));

    } else {
        ins->propertyList = 0;
    }
    
    if(o)
        o->link = ins;
    ins->link = 0;

    return ins;
}

Property* getObjectProperty(Object* o, int idx) {
    int i;
    Property* cur;

    if(-1 < idx && idx < *(o->propertyLength) - 1) {
        cur = o->propertyList;
        for(i = 0; i < idx; idx++)
            cur = cur->link;
        return cur;
    }

    return 0;
}

/**
 * len_o(Object*)
 *
 * @description
 *    returns # of Object. (include empty head List)
 *
 * @param
 *    o - Object
 *
 * @return
 *    int - # of Object List.
 */
int getObjectLength(Object* o) {
    return *(o->objectLength);
}

/**
 * n_Object(Object*)
 *
 * @description
 *    returns # of valid Object List.
 *
 * @param
 *    o - Object*
 *
 * @return
 *    int - # of valid Object List.
 */
int getObjectSize(Object* o) {
    return *(o->objectLength) - 1;
}

Object* compareObject(Object* oa, Object* ob) {
    if(oa == ob)
        return oa;
    return 0;
}

/**
 * del_o
 * 
 * @description
 *    free memory all of Object's List.
 * 
 * @param
 *    o - head of Object List.
 *
 * @return
 *    0
 */
int delObject(Object* head) {
    Object* p = head;
    Object* q;

    do {
        q = p;
        p = p->link;
        // todo for free q.
        if(q->propertyList){
            delProperty(q->propertyList);
            free(q->propertyLength);
        }
        
        free(q);
    } while(p);

    return 0;
}

/**
 * dbg_o
 * 
 * print log of Objectect List.
 */
void dbgObject(Object* o) {
    printf(" # Object@%p", o);
    if(!o->link && !o->propertyList)
        printf(" [BLANK]\n");
    else {
        if(o->link)
            printf(" -> %p", o->link);
        else
            printf(" [TAIL]");
        if(o->propertyList) {
            printf("\n   > PropertyList = %p\n", o->propertyList);
            dbgPropertyList(o->propertyList);
        } else
            printf(" [HEAD - size:%d]\n", getObjectSize(o)); 
    }
}

void dbgObjectList(Object* head) {
    Object* cur = head;
    for(; cur; cur = cur->link)
        dbgObject(cur);
}