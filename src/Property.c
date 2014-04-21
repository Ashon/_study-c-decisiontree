/**
 * Decision Tree Genarator v0.1
 *
 * Property.c
 *
 * @author juwon.lee
 * @date 2014-04-11
 *
 * mit licensed.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "ADT_DecisionTree.h"

/**
 * newProperty(Property*, int*, int*)
 *
 * @description
 *    makes a new Property instance link of p.
 *
 * @param
 *    p - target Property
 *    value - integer value
 *    PropertyLength - # of Propertyerty (indirect)
 *               equals # of attribute.
 *
 * @return
 *    Property* - new Property instance's pointer.
 */
Property* newProperty(Object* o, Property* p, int* value) {
    Property* instance = (Property*)malloc(sizeof(Property));
    instance->propertyLength = o->propertyLength;
    *(instance->propertyLength) = *(instance->propertyLength) + 1;

    if(value) {
        instance->value = (int*)malloc(sizeof(int));
        *(instance->value) = *(value);
    } else {
        instance->value = 0;
    }

    if(p)
        p->link = instance;

    instance->link = 0;
    return instance;
}

/**
 * getPropertyLength(Property*)
 *
 * @descriptinon
 *    returns # of Property List. (include empty head List)
 *
 * @param
 *    p - Property
 *
 * @return
 *    int - # of Property List
 */
int getPropertyLength(Property* p) {
    return *(p->propertyLength);
}

/**
 * getPropertySize(Property*)
 *
 * @description
 *    returns # of valid Property List.
 *
 * @param
 *    p - Property*
 *
 * @return
 *    int - # of valid Property List.
 */
int getPropertySize(Property* p) {
    return *(p->propertyLength) - 1;
}

int getPropertyValue(Property* p) {
    return *(p->value);
}

int delProperty(Property* head) {
    Property* p = head;
    Property* q;
    do {
        q = p;
        p = p->link;

        if(q->value)
            free(q->value);

        free(q);
    } while(p);
    return 0;
}

void dbgProperty(Property* p) {
    printf("      # Property@%p", p);
    if(p->link == 0 && p->value == 0)
        printf(" [BLANK]\n");
    else {
        if(p->link)
            printf(" -> %p", p->link);
        else
            printf(" [TAIL]");
        if(p->value)
            printf("\n        > value = %d\n", *(p->value));
        else
            printf(" [HEAD - size:%d]\n", getPropertySize(p));
    }
}

void dbgPropertyList(Property* head) {
    Property* cur = head;
    for(; cur; cur = cur->link)
        dbgProperty(cur);
}
