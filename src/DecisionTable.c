/**
 * Decision Tree Genarator v0.1
 *
 * DecisionTable.c
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

DecisionTable* newDecisionTable(DecisionTable* t, FILE* fp) {
    DecisionTable* instance = (DecisionTable*)malloc(sizeof(DecisionTable));

    char *buf = (char*)calloc(MAX_BUFFER_SIZE, sizeof(char));
    int cond = -1;

    Attribute* attribute_cur;
    Object* object_cur; 

    instance->attributeLength = (int*)malloc(sizeof(int));
    instance->objectLength = (int*)malloc(sizeof(int));
    instance->splitTableLength = (int*)malloc(sizeof(int));

    *(instance->attributeLength) = 0;
    *(instance->objectLength) = 0;
    *(instance->splitTableLength) = 0;

    instance->attributeList = newAttribute(instance, 0, 0);
    instance->objectList = newObject(instance, 0, 0);
    instance->splitTableList = newSplitTable(instance, 0, 0);

    attribute_cur = instance->attributeList;
    object_cur = instance->objectList;

    cond++;

    while(fgets(buf, MAX_BUFFER_SIZE, fp)) {
       if(0 < strlen(buf))
            buf[strlen(buf) - 1] = '\0';
        if(!strcmp(buf, "#")) {
            cond++;
            continue;
        }

        // generate Attribute
        if(cond == 1) {
            attribute_cur = newAttribute(instance, attribute_cur, buf);
        }

        // generate Objectect
        if(cond == 2) {
            object_cur = addObject(instance, object_cur, buf);
        }
    }

    /*
     * find continuous attribute.. and tuning..
     *
     * code here..
     * splitAttributeNodeList(Attribute*)
     *
     * @description
     *    split & tuning a's attributeNode List.
     */
    /*
    attribute_cur = instance->attributeList->link;
    while(attribute_cur) {
        splitAttributeNode(instance, attribute_cur);
        attribute_cur = attribute_cur->link;
    }
*/
    // generate Split Table
    generateSplitTable(instance);

    /*
     * generate decision tree
     *
     * code here..
     */

    free(buf);
    
    t = instance;
    return instance;
}

Attribute* addAttribute(DecisionTable* t, Attribute* attribute_cur, char* buf) {
    attribute_cur = newAttribute(t, attribute_cur, buf);

    return attribute_cur;
}

Attribute* getClassAttribute(DecisionTable* t) {
    Attribute* cur = t->attributeList->link;
    while(cur) {
        if(*(cur->attributeType) == ATTRIBUTE_TYPE_CLASS)
            return cur;
        cur = cur->link;
    }
    return 0;
}

Object* addObject(DecisionTable* t, Object* object_cur, char* buf) {
    // t's cursor
    Attribute* attribute_cur;
    AttributeNode* attributeNode_cur;
    ObjectWrapper* objectWrapper_cur;

    // object_cur's Property cursor
    Property* cur_Property;

    object_cur = newObject(t, object_cur, buf);
    cur_Property = object_cur->propertyList->link;
    int idx;
    int count = 0;
    
    // attribute loop
    attribute_cur = t->attributeList;
    while(attribute_cur) {
        // if attribute->classList != null
        if(attribute_cur->attributeNodeList) {

            attributeNode_cur = attribute_cur->attributeNodeList->link;
            // classList index
            idx = 0;
            // classList loop
            while(attributeNode_cur) {
                // move objectWrapper_cur to last
                objectWrapper_cur = attributeNode_cur->objectWrapperList;
                while(objectWrapper_cur->link)
                    objectWrapper_cur = objectWrapper_cur->link;

                // compare classindex == object idx'th property
                if(idx == *(cur_Property->value)) {
                    objectWrapper_cur = newObjectWrapper(objectWrapper_cur,
                        object_cur, attributeNode_cur->objectWrapperLength);
                    break;
                }
                // next index
                idx++;
                // next attribute_class
                attributeNode_cur = attributeNode_cur->link;
            }
            
            // object's next property
            cur_Property = cur_Property->link;
        }
        // next attribute
        attribute_cur = attribute_cur->link;
    }
    return object_cur;
}

SplitTable* generateSplitTable(DecisionTable* t) {
    SplitTable* splitTable_cur = t->splitTableList;
    Attribute* classAttribute = getClassAttribute(t);
    Attribute* attribute_cur = t->attributeList;
    while(attribute_cur) {
        if(attribute_cur != classAttribute) {
            if(attribute_cur->attributeName)
                splitTable_cur = newSplitTable(t, splitTable_cur,
                    attribute_cur);
        }
        attribute_cur = attribute_cur->link;
    }
    return t->splitTableList;
}

Attribute* splitAttributeNode(DecisionTable* t, Attribute* a) {
    int devideCount = 10;

    AttributeNode* attributeNode_cur;
    Object* object_cur;

    // if a.type is continuous then
    if(*(a->attributeType) == ATTRIBUTE_TYPE_CONTINUOUS) {
        // initialize attributeNode cursor
        attributeNode_cur = a->attributeNodeList;
        // loop : devide
        while((*(a->attributeNodeLength) - 1) < devideCount)
            attributeNode_cur = newAttributeNode(a,
                    attributeNode_cur, "asdfasdf");
    }

    return a;
}

int delDecisionTable(DecisionTable* t) {
    delAttribute(t->attributeList);
    delObject(t->objectList);
    delSplitTable(t->splitTableList);

    free(t->attributeLength);
    free(t->objectLength);
    free(t->splitTableLength);

    free(t);
    return 0;
}

void dbgDecisionTable(DecisionTable* t) {
    printf("## DecisionTable@%p\n", t);
    printf("> attributeList = %p\n", t->attributeList);
    dbgAttributeList(t->attributeList);
    printf("> objectList = %p\n", t->objectList);
    dbgObjectList(t->objectList);
    printf("> splitTableList = %p\n", t->splitTableList);
    dbgSplitTableList(t->splitTableList);
}
