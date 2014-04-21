/**
 * Decision Tree Genarator v0.1
 *
 * AttributeNode.c
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
 * newAttributeNode(Attribute*, AttributeNode*, char*)
 *
 * @description
 *    makes a new AttributeNode instance link of *AttributeNode.
 *
 * @param
 *    c - AttributeNode pointer to attach a new AttributeNode
 *    str - name of new class instance
 *    AttributeNodeLength - # of AttributeNode
 *
 * @return
 *    AttributeNode* - new AttributeNode instance's pointer
 */
AttributeNode* newAttributeNode(Attribute* a, AttributeNode* c, char* str) { 

    AttributeNode* instance;
    instance = (AttributeNode*)malloc(sizeof(AttributeNode));
    instance->parent = a;

    instance->attributeNodeLength = a->attributeNodeLength;
    *(instance->attributeNodeLength) = *(instance->attributeNodeLength) + 1;

    if(str) {
        instance->attributeNodeName = (char*)calloc(strlen(str) + 1, sizeof(char));
        strcpy(instance->attributeNodeName, str);
    } else
        instance->attributeNodeName = 0;

    instance->objectWrapperLength = (int*)malloc(sizeof(int));
    *(instance->objectWrapperLength) = 0;

    instance->objectWrapperList = newObjectWrapper(0, 0, 
                                    instance->objectWrapperLength);

    if(c)
        c->link = instance;
    instance->link = 0;

    return instance;
}

/**
 * getAttributeNodeLength(AttributeNode*)
 * 
 * @description
 *    returns # of AttributeNode.
 *
 * @param
 *    c - AttributeNode
 *
 * @return
 *    int - # of AttributeNode
 */
int getAttributeNodeLength(AttributeNode* c) {
    return *(c->attributeNodeLength);
}

/**
 * getAttributeNodeSize(AttributeNode*)
 *
 * @description
 *    returns # of valid AttributeNode List.
 *
 * @param
 *    c - AttributeNode*
 *
 * @return
 *    int - # of valid AttributeNode List.
 */
int getAttributeNodeSize(AttributeNode* c) {
    return *(c->attributeNodeLength) - 1;
}

/**
 * delAttributeNode(AttributeNode*)
 *
 * @description
 *    free memory all of AttributeNode
 *
 * @param
 *    head - head of AttributeNode.
 *
 * @return
 *    0 - returns 0 when 'free' finished.
 */

int delAttributeNode(AttributeNode* head) {
    AttributeNode* p;
    AttributeNode* q;

    p = head;

    do {
        q = p;
        p = p->link;

        if(q->objectWrapperList)
            delObjectWrapper(q->objectWrapperList);

        if(q->attributeNodeName)
            free(q->attributeNodeName);
        
        free(q->objectWrapperLength);
        free(q);
    } while(p);

    return 0;
}

void dbgAttributeNode(AttributeNode* ac) {
    printf("      # AttributeNode@%p", ac);
    if(ac->link == 0 && ac->attributeNodeName == 0)
        printf(" [BLANK]\n");
    else {
        if(ac->link)
            printf(" -> %p", ac->link);
        else
            printf(" [TAIL]");
        if(ac->attributeNodeName && ac->objectWrapperList) {
            printf("\n        > attributeNodeName = %s\n", ac->attributeNodeName);
            printf("        > parent = %p\n", ac->parent);
            printf("        > objectWrapperList = %p\n", ac->objectWrapperList);
            dbgObjectWrapperList(ac->objectWrapperList);
        } else
            printf(" [HEAD - size:%d]\n", getAttributeNodeSize(ac));
    }
}

void dbgAttributeNodeList(AttributeNode* head) {
    AttributeNode* cur = head;
    for(; cur; cur = cur->link)
        dbgAttributeNode(cur);
}
