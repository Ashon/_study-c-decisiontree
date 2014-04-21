/**
 * Decision tree generator
 *
 * SplitTable.c
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

SplitTable* newSplitTable(DecisionTable* t, SplitTable* st,
    Attribute* attributeColumn) 
{
    SplitTable* instance = (SplitTable*)malloc(sizeof(SplitTable));
    SplitTableCell* cur_SplitTableCell;

    AttributeNode* cur_AttributeNode;
    AttributeNode* cur_list;

    instance->splitTableLength = t->splitTableLength;
    *(instance->splitTableLength) = *(instance->splitTableLength) + 1;

    instance->objectLength = t->objectLength;

    if(st) {
        instance->attributeRow = getClassAttribute(t);
        instance->attributeColumn = attributeColumn;
    
        instance->splitTableCellLength = (int*)malloc(sizeof(int));
        *(instance->splitTableCellLength) = 0;
    
        instance->splitTableCellList = newSplitTableCell(instance, 0, 0, 0);
        cur_SplitTableCell = instance->splitTableCellList;
    
        cur_AttributeNode = instance->attributeRow->attributeNodeList->link;
        while(cur_AttributeNode) {
            cur_list = instance->attributeColumn->attributeNodeList->link;
            while(cur_list) {
                cur_SplitTableCell = newSplitTableCell(instance, cur_SplitTableCell,
                    cur_AttributeNode, cur_list);

                cur_list = cur_list->link;
            }
            cur_AttributeNode = cur_AttributeNode->link;
        }

        st->link = instance;
    } else {
        instance->attributeRow = 0;
        instance->attributeColumn = 0;
        instance->splitTableCellList = 0;
    }

    instance->link = 0;

    return instance;
}

int getSplitTableLength(SplitTable* s) {
    return *(s->splitTableLength);
}

int getSplitTableSize(SplitTable* s) {
    return *(s->splitTableLength) - 1;
}

int getSplitTableHeight(SplitTable* s) {
    return getAttributeNodeSize(s->attributeRow->attributeNodeList);
}

int getSplitTableWidth(SplitTable* s) {
    return getAttributeNodeSize(s->attributeColumn->attributeNodeList);
}

int delSplitTable(SplitTable* head) {
    SplitTable* p = head;
    SplitTable* q;
    do {
        q = p;
        p = p->link;

        if(q->splitTableCellList){
            delSplitTableCell(q->splitTableCellList);
            free(q->splitTableCellLength);
        }
        
        free(q);
    } while(p);
}

SplitTableCell* getSplitTableCell(SplitTable* s, int row, int col) {
    SplitTableCell* cur;
    int i;
    int coord;
    int len_row = *(s->attributeRow->attributeNodeLength) - 1;
    int len_col = *(s->attributeColumn->attributeNodeLength) - 1;

    if((-1 < row && row < len_row) &&
        (-1 < col && col < len_col)) {
        cur = s->splitTableCellList->link;
        coord = (*(s->attributeColumn->attributeNodeLength) - 1) * row + col;
        for(i = 0; i < coord; i++)
            cur = cur->link;
        return cur;
    }
    return 0;
}

float getGiniIndex(SplitTable* s, int col) {
    AttributeNode* cur = s->attributeColumn->attributeNodeList->link;
    int i;
    int ListSize;
    int attributeNodeLength;
    int* attributeNode;
    float giniIdx;
    float sigma = 0;

    for(i = 0; i < col; i++)
        cur = cur->link;

    ListSize = *(cur->objectWrapperLength) - 1;
    attributeNodeLength = *(s->attributeRow->attributeNodeLength) - 1;
    attributeNode = (int*)calloc(attributeNodeLength, sizeof(int));

    for(i = 0; i < attributeNodeLength; i++) {
        attributeNode[i] = *(getSplitTableCell(s, i, col)->objectWrapperLength) - 1;
    }

    for(i = 0; i < attributeNodeLength; i++)
        sigma += (float)(attributeNode[i] * attributeNode[i]) / (ListSize * ListSize);
    giniIdx = 1 - sigma;

    free(attributeNode);

    return giniIdx;
}

float getGiniSplit(SplitTable* s) {
    int i;
    float giniIdx;
    float giniSplit = 0;
    int objectSize = *(s->objectLength) - 1;

    Attribute* column = s->attributeColumn;
    AttributeNode* cur = column->attributeNodeList->link;

    if(s->splitTableCellList) {
        for(i = 0; i < *(column->attributeNodeLength) - 1; i++) {
           giniIdx = getGiniIndex(s, i);
           giniSplit += ((float)(*(cur->objectWrapperLength) - 1) / objectSize) * giniIdx;
           cur = cur->link;
        }
    }

    return giniSplit;
}

void dbgSplitTable(SplitTable* st) {
    int i;
    AttributeNode* cur;
    printf(" # SplitTable@%p", st);
    if(!st->link && !st->splitTableCellList)
        printf(" [BLANK]\n");
    else {
        if(st->link)
            printf(" -> %p", st->link);
        else
            printf(" [TAIL]");
        if(st->attributeRow)
            printf("\n   > attributeRow = %p[ %s ]\n",
                    st->attributeRow, st->attributeRow->attributeName);
        if(st->attributeColumn)
            printf("   > attributeColumn = %p[ %s ]\n",
                    st->attributeColumn, st->attributeColumn->attributeName);
        if(st->splitTableCellList) {
            cur = st->attributeColumn->attributeNodeList->link;
            for(i = 0; i < *(st->attributeColumn->attributeNodeLength) - 1; i++) {
                printf("   > GINI index [ %s : %s ] = %f\n",
                    cur->parent->attributeName, cur->attributeNodeName,
                    getGiniIndex(st, i));
                cur = cur->link;
            }
            printf("   > GINI Split = %f\n", getGiniSplit(st));
            printf("   > splitTableCellList = %p\n", st->splitTableCellList);
            dbgSplitTableCellList(st->splitTableCellList);
        } else
            printf(" [HEAD - size:%d]\n", getSplitTableSize(st));
    }
}

void dbgSplitTableList(SplitTable* head) {
    SplitTable* cur = head;
    for(; cur; cur = cur->link)
        dbgSplitTable(cur);
}

