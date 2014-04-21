/**
 * Decision Tree Genarator v0.1
 *
 * ObjectWrapper.c
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

ObjectWrapper* newObjectWrapper(
        ObjectWrapper* lo,
        Object* o,
        int* ObjectWrapperLength) {

	ObjectWrapper* instance = (ObjectWrapper*)malloc(sizeof(ObjectWrapper));

    instance->objectWrapperLength = ObjectWrapperLength;
    *(instance->objectWrapperLength) = *(instance->objectWrapperLength) + 1;

    if(o) {
        instance->object = o;
    } else {
        instance->object = 0;
    }

    if(lo)
        lo->link = instance;

    instance->link = 0;
    return instance;
}

int getObjectWrapperLength(ObjectWrapper* lo) {
	return *(lo->objectWrapperLength);
}

int getObjectWrapperSize(ObjectWrapper* lo) {
	return *(lo->objectWrapperLength) - 1;
}

Object* findObject(ObjectWrapper* head, Object* o) {
    ObjectWrapper* cur = head;
    Object* fnd;
    for(; cur; cur = cur->link) {
        if(fnd = compareObject(o, cur->object));
            return fnd;
    }
    return 0;
}

int delObjectWrapper(ObjectWrapper* head) {
    ObjectWrapper* p = head;
    ObjectWrapper* q;

    do {
        q = p;
        p = p->link;
        free(q);
    } while(p);

    return 0;
}

void dbgObjectWrapper(ObjectWrapper* ow) {
	printf("           # ObjectWrapper@%p", ow);
    if(ow->link == 0 && ow->object == 0)
        printf(" [BLANK]\n");
    else {
        if(ow->link)
            printf(" -> %p", ow->link);
        else
            printf(" [TAIL]");
        if(ow->object) {
            printf("\n             > object = %p\n", ow->object);
        } else
            printf(" [HEAD - size:%d]\n", getObjectWrapperSize(ow));
    }
}

void dbgObjectWrapperList(ObjectWrapper* head) {
    ObjectWrapper* cur = head;
    for(; cur; cur = cur->link)
        dbgObjectWrapper(cur);
}
