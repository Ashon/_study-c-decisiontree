/**
 * Decision Tree Genarator
 *
 * @author ashon
 * @date 2014-04-11
 *
 * mit licensed.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Max buffer size
 */
#define MAX_BUF 255

/**
 * Attribute Type Constant
 */
#define ATTR_TYPE_CLASS 0
#define ATTR_TYPE_BINARY 1
#define ATTR_TYPE_CATEGORICAL 2
#define ATTR_TYPE_CONTINUOUS 3

/**
 * ADT for decision tree generator.
 * 
 * @schemas..
 *    Attribute < name, type, @AttrNodeVector, *link >
 *    AttrNodeVector < length, @AttrNode ... >
 *    AttrNode < name, *link >
 */
typedef struct AttrNode_ {
    char name[MAX_BUF];
    struct AttrNode_* prev;
    struct AttrNode_* next;
} AttrNode;

typedef struct AttrNodeVector_ {
    int length;
    AttrNode* nodes;
} AttrNodeVector;

typedef struct Attribute_ {
    char name[MAX_BUF];
    int type;
    AttrNodeVector* nodeVector;

    struct Attribute_ * prev;
    struct Attribute_ * next;
} Attribute;

/**
 * ADT - SampleData
 */
typedef struct Sample_ {

} Sample;

/**
 * getAttribute from strings.
 * string form => "[attributename]{[node], [node], ... }\n"
 */

/*
Attribute* getAttribute(char* form){
    s = (Sample*)malloc(sizeof(Sample));
}
*/

Attribute* read_attr(char* str, Attribute* attr){
    char* name;
    char* nodes;
    char* node;
    char* type;
    int i, length;

    // mem alloc
    attr = (Attribute*)calloc(1, sizeof(Attribute));

    name = (char*)calloc(MAX_BUF, sizeof(char));
    strcpy(name, strtok(str, "{"));

    printf(" attr->name : %s\n", name);
    strcpy(attr->name, name);
    // printf("parse nodes\n");
    nodes = strtok(0, "}");
    i = 0;
    node = strtok(nodes, ",");
    // printf("loop start\n");
    if(strcmp(node, "@")){
        printf(" type : %d", ATTR_TYPE_CONTINUOUS);
    }else{
        do {
            printf(" node %d : %s\n", i++, node);
        } while((node = strtok(0, ",")) != 0);
    }
    // printf("loop end\n");
    return attr;
}

char* getAttributeName(Attribute* attr){
    return attr->name;
}

void dbg_attr(Attribute* attr){
    printf("Attribute @ %p\n", attr);
    printf("[name = %s]\n", getAttributeName(attr));
    printf("[type = %d]\n", attr->type);
    printf("[nodeVector = %p]\n", attr->nodeVector);
    printf("\n");
}

// main
int main() {
    FILE* fp;
    char str[MAX_BUF];

    char *name;
    char *node;

    Attribute* attrNode;
    int cond = 0;

    fp = fopen("./train.dat", "r");
    if(fp == NULL)
        return 1;
    else
        while(fgets(str, 255, fp)){
            if(0 < strlen(str))
                str[strlen(str) - 1] = '\0';

            printf(" read > %s\n", str);
            if(cond == 1){
                read_attr(str, attrNode);
                dbg_attr(attrNode);
                // printf("dbg end\n");
            }
            if(!strcmp(str, "#"))
                cond++;


        }
    return 0;
}













