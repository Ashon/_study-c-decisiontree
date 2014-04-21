/**
 * Decision tree generator
 *
 * SplitTableCell.c
 *
 * @author juwon.lee
 * @date 2014-04-17
 *
 * mit licensed.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "ADT_DecisionTree.h"

/**
 * newSplitTableCell(SplitTableCell*, SplitTable*)
 *
 * @description
 *    ss
 *
 * @param
 *    s - SplitTableCell pointer.
 *    attributeColumn - attr List's head AttributeNode List.
 *    attributeRow - attr class's head AttributeNode List.
 *
 * @return
 *    SplitTableCell* - instance
 *
 */
SplitTableCell* newSplitTableCell(
        SplitTable* st,
        SplitTableCell* s,
        AttributeNode* attributeRow,
        AttributeNode* attributeColumn) {

    SplitTableCell* instance = (SplitTableCell*)malloc(sizeof(SplitTableCell));
    ObjectWrapper* instanceObjWrapper_cur;
    Object* foundObject;

    ObjectWrapper* colObjWrapper_cur; 
    ObjectWrapper* rowObjWrapper_cur;

    instance->splitTableCellLength = st->splitTableCellLength;
    *(instance->splitTableCellLength) = *(instance->splitTableCellLength) + 1;

    if(s) {
        instance->objectWrapperLength = (int*)malloc(sizeof(int));
        *(instance->objectWrapperLength) = 0;

        instance->objectWrapperList = newObjectWrapper(0, 0,
                instance->objectWrapperLength);
        instanceObjWrapper_cur = instance->objectWrapperList;

        rowObjWrapper_cur = attributeRow->objectWrapperList;
        while(rowObjWrapper_cur) {
            colObjWrapper_cur = attributeColumn->objectWrapperList;
            while(colObjWrapper_cur) {
                if(foundObject =
                    findObject(rowObjWrapper_cur, colObjWrapper_cur->object))
                    instanceObjWrapper_cur = 
                        newObjectWrapper(instanceObjWrapper_cur,
                                foundObject, instance->objectWrapperLength);

                colObjWrapper_cur = colObjWrapper_cur->link;
            }
            rowObjWrapper_cur = rowObjWrapper_cur->link;
        }

        s->link = instance;
    } else {
        instance->objectWrapperLength = 0;
        instance->objectWrapperList = 0;
    }

    instance->link = 0;

    return instance;
}

int getSplitTableCellLength(SplitTableCell* c) {
    return *(c->splitTableCellLength);
}

int getSplitTableCellSize(SplitTableCell* c) {
    return *(c->splitTableCellLength) - 1;
}

int delSplitTableCell(SplitTableCell* head) {
    SplitTableCell* p = head;
    SplitTableCell* q;
    do {
        q = p;
        p = p->link;
        if(q->objectWrapperList)
            delObjectWrapper(q->objectWrapperList);
        free(q->objectWrapperLength);
        free(q);
    } while(p);
    return 0;
}

void dbgSplitTableCell(SplitTableCell* c) {
    printf("     # SplitTableCell@%p", c);
    if(!c->link && !c->objectWrapperList)
        printf(" [BLANK]\n");
    else {
        if(c->link)
            printf(" -> %p", c->link);
        else
            printf(" [TAIL]");
        if(c->objectWrapperList)
            printf("\n       > value = %d\n", *(c->objectWrapperLength) - 1);
        else 
            printf(" [HEAD - size:%d]\n", getSplitTableCellSize(c));
    }
}

void dbgSplitTableCellList(SplitTableCell* head) {
    SplitTableCell* cur = head;
    for(; cur; cur = cur->link)
        dbgSplitTableCell(cur);
}
