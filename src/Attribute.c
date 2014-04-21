/**
 * Decision Tree Genarator v0.1
 *
 * Attribute.c
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
 * newAttribute(Attribute*, char*, int*)
 *
 * @description
 *    makes a new Attribute instance link of *a.
 * 
 * @param
 *    a - Attribute pointer to attach a new List.
 *
 *    str - string
 *       formed string such as "[Attribute]{[List],[List], .. }"
 *       [Attribute_NAME] - Attribute's name
 *       [List_NAME] - List(class)'s name of Attribute.
 *
 *    attributeLength - # of Attribute (indirect)
 *
 * @return
 *    Attribute* - new Attribute instance's pointer.
 */
Attribute* newAttribute(DecisionTable* t, Attribute* a, char* str) {
    Attribute* instance;
    AttributeNode* cur;

    char* buf;

    char* List;
    int name_length;

    instance = (Attribute*)malloc(sizeof(Attribute));
    instance->attributeLength = t->attributeLength;

    *(instance->attributeLength) = *(instance->attributeLength) + 1;

    if(a) {
        instance->attributeType = (int*)malloc(sizeof(int));
        *(instance->attributeType) = -1;

        buf = (char*)calloc(MAX_BUFFER_SIZE, sizeof(char));
        strcpy(buf, strtok(str, "{"));
        instance->attributeName = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(instance->attributeName, buf);
        free(buf);

        List = strtok(strtok(0, "}"), ",");
        if(0 < strlen(List)) {
            instance->attributeNodeLength = (int*)malloc(sizeof(int));
            *(instance->attributeNodeLength) = 0;
            instance->attributeNodeList = newAttributeNode(instance, 0, 0);
            cur = instance->attributeNodeList;
        }

        name_length = strlen(instance->attributeName);
        if(!strcmp(&instance->attributeName[name_length - 1], "@")){
            *(instance->attributeType) = ATTRIBUTE_TYPE_CLASS;
            instance->attributeName[name_length - 1] = '\0';
        }

        if(!strcmp(List, "@")) {
            *(instance->attributeType) = ATTRIBUTE_TYPE_CONTINUOUS;
        } else do {
            cur = newAttributeNode(instance, cur, List);
        } while(List = strtok(0, ","));

        if(*(instance->attributeType) == -1)
            if(2 == *(instance->attributeNodeLength) - 1)
                *(instance->attributeType) = ATTRIBUTE_TYPE_BINARY;
            else if(2 < *(instance->attributeNodeLength) - 1)
                *(instance->attributeType) = ATTRIBUTE_TYPE_CATEGORICAL;

        a->link = instance;
    } else {
        instance->attributeName = 0;
        instance->attributeType = 0;
        instance->attributeNodeLength = 0;
        instance->attributeNodeList = 0;
    }

    instance->link = 0;

    return instance;
}

/**
 * attributeLength(Attribute*)
 *
 * @description
 *    returns # of Attribute. (include head List)
 *
 * @param
 *    a - Attribute*
 *
 * @return
 *    int - # of Attribute Lists.
 */
int getattributeLength(Attribute* a) {
    return *(a->attributeLength);
}

/**
 * n_Attribute(Attribute*)
 *
 * @description
 *    returns # of valid Attribute.
 *
 * @param
 *    a - Attribute*
 *
 * @return
 *    int - # of valid Attribute List.
 */
int getAttributeSize(Attribute* a) {
    return *(a->attributeLength) - 1;
}

/**
 * del_Attribute(Attribute*)
 *
 * @description
 *    free all of Attribute List.
 *
 * @param
 *    head - head of Attribute List.
 *
 * @return
 *    0
 */
int delAttribute(Attribute* head) {
    Attribute* p = head;
    Attribute* q;

    do {
        q = p;
        p = p->link;
        if(q->attributeName)
            free(q->attributeName);
        if(q->attributeType)
            free(q->attributeType);
        if(q->attributeNodeLength)
            free(q->attributeNodeLength);
        if(q->attributeNodeList)
            delAttributeNode(q->attributeNodeList);
        free(q);
    } while(p);

    return 0;
}

void dbgAttribute(Attribute* a) {
    printf(" # Attribute@%p", a);
    if(!a->link && !a->attributeName)
        printf(" [BLANK]\n");
    else {
        if(a->link)
            printf(" -> %p", a->link);
        else
            printf(" [TAIL]");

        if(a->attributeName)
            printf("\n   > attributeName = %s\n", a->attributeName);
        else
            printf(" [HEAD - size:%d]\n", getAttributeSize(a));

        if(a->attributeType) {
            printf("   > type = %d",*(a->attributeType));
            switch(*(a->attributeType)) {
                case 0 :
                    printf(" : [ATTRIBUTE_TYPE_CLASS]\n");
                break;
                case 1 :
                    printf(" : [ATTRIBUTE_TYPE_BINARY]\n");
                break;
                case 2 :
                    printf(" : [ATTRIBUTE_TYPE_CATEGORICAL]\n");
                break;
                case 3 :
                    printf(" : [ATTRIBUTE_TYPE_CONTINUOUS]\n");
                break;
            }
        }
        if(a->attributeNodeList) {
            printf("   > attributeNodeList = %p\n", a->attributeNodeList);
            dbgAttributeNode(a->attributeNodeList);
        }
    }
}

void dbgAttributeList(Attribute* head) {
    Attribute* cur = head;
    for(; cur; cur = cur->link){
        printf(" # Attribute@%p", cur);
        if(!cur->link && !cur->attributeName)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
    
            if(cur->attributeName)
                printf("\n   > attributeName = %s\n", cur->attributeName);
            else
                printf(" [HEAD - size:%d]\n", getAttributeSize(cur));
    
            if(cur->attributeType) {
                printf("   > type = %d",*(cur->attributeType));
                switch(*(cur->attributeType)) {
                    case 0 :
                        printf(" : [ATTRIBUTE_TYPE_CLASS]\n");
                    break;
                    case 1 :
                        printf(" : [ATTRIBUTE_TYPE_BINARY]\n");
                    break;
                    case 2 :
                        printf(" : [ATTRIBUTE_TYPE_CATEGORICAL]\n");
                    break;
                    case 3 :
                        printf(" : [ATTRIBUTE_TYPE_CONTINUOUS]\n");
                    break;
                }
            }
    
            if(cur->attributeNodeList) {
                printf("   > attributeNodeList = %p\n", cur->attributeNodeList);
                dbgAttributeNodeList(cur->attributeNodeList);
            }
        }
    }
}
