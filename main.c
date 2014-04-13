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

#define ULL unsigned long long
/**
 * attr Type Constant
 */
#define AT_TYPE_CLASS 0
#define AT_TYPE_BINARY 1
#define AT_TYPE_CATEGORICAL 2
#define AT_TYPE_CONTINUOUS 3

/**
 * ADT for decision tree generator.
 * 
 * @schemas..
 *    attr < name, type, @atNode_v, *next >
 *    atNode < name, *next >
 */

/*
 * ADT - atNode
 */
typedef struct atNode_ {
    char* name;

    struct atNode_* next;
} atNode;

atNode* new_an(atNode*, char*);
int destroy_an(atNode*);
void dbg_an(atNode*);

/*
 * ADT - attr
 */
typedef struct attr_ {
    char* name;
    int* type;

    atNode* node;
    struct attr_ * next;
} attr;

attr* new_a(attr*, char*);
int destroy_a(attr*);
void dbg_a(attr*);

/**
 * ADT - Object
 */
typedef struct obj_ {
    int* property_int;
    float* property_float;

    struct obj_* next;
} obj;

/*
 * new_node
 *
 * @param
 *    an - link point.
 *
 * @return
 *    atNode* - next nodes pointer.
 */
atNode* new_an(atNode* an, char* str) {
    atNode* target;

    target = (atNode*)malloc(sizeof(atNode));

    if(str) {
        target->name = (char*)calloc(strlen(str) + 1, sizeof(char));
        strcpy(target->name, str);
    } else
        target->name = 0;

    if(an)
        an->next = target;
    target->next = 0;

    return target;
}

/*
 * free node
 * @param
 *    head - head of atNode.
 * @return
 *    0 - returns 0 when 'free' finished.
 */
int destroy_an(atNode* head) {
    atNode* p;
    atNode* q;

    p = head;

    do {
        q = p;
        p = p->next;
        if(q->name)
            free(q->name);
        free(q);
    }while(p);

    return 0;
}

void dbg_an(atNode* an) {
    atNode* cur = an;
    for(; cur; cur = cur->next) {
        printf("    ##atNode @ %p\n", cur);
        if(cur->name)
            printf("     > name = %s\n", cur->name);
        if(cur->next)
            printf("     > next = %p\n", cur->next); 
    }
}

/*
 * attribute function.
 */
attr* new_a(attr* a, char* str) {
    attr* target;
    atNode* cur;

    char* name;
    char* nodes;
    char* node;
    int i, length;

    target = (attr*)malloc(sizeof(attr));
    if(a) {
        target->type = (int*)malloc(sizeof(int));
        *(target->type) = -1;

        name = (char*)calloc(MAX_BUF, sizeof(char));
        strcpy(name, strtok(str,"{"));
        target->name = (char*)calloc(strlen(name) + 1, sizeof(char));
        strcpy(target->name, name);
        free(name);

        nodes = strtok(0, "}");
        node = strtok(nodes, ",");
        if(0 < strlen(node)) {
            target->node = new_an(0, 0);
            cur = target->node;
        }

        i = 0;
        if(!strcmp(node, "@")) {
            *(target->type) = AT_TYPE_CONTINUOUS;
        } else {
            do {
                cur = new_an(cur, node);
                i++;
            } while((node = strtok(0, ",")) != 0);
            if(2 < i) {
                *(target->type) = AT_TYPE_CATEGORICAL;
            } else {
                *(target->type) = AT_TYPE_BINARY;
            }
        }
        a->next = target;
    } else {
        target->name = 0;
        target->type = 0;
        target->node = 0;
    }

    target->next = 0;
    return target;
}

int destroy_a(attr* head) {
    attr* p = head;
    attr* q;
    do {
        q = p;
        p = p->next;
        // todo for free
        if(q->name)
            free(q->name);
        if(q->type)
            free(q->type);
        if(q->node)
            destroy_an(q->node);
        //
        free(q);
    } while(p);
    return 0;
}

void dbg_a(attr* attr) {
    printf("##attr @ %p\n", attr);
    if(attr->name)
        printf(" > name = %s\n", attr->name);
    if(attr->type)
        printf(" > type = %d\n", *(attr->type));
    if(attr->node)
        dbg_an(attr->node);
    if(attr->next)
        printf(" > next = %p\n", attr->next);
}

// main
int main() {
    FILE* fp;
    char *str = (char*)calloc(MAX_BUF, sizeof(char));

    attr* head = new_a(0, 0);
    attr* cur = head;

    int cond = 0;

    fp = fopen("./train.dat", "r");
    if(fp == NULL)
        return 1;
    else
        while(fgets(str, MAX_BUF, fp)) {
            if(0 < strlen(str))
                str[strlen(str) - 1] = '\0';
            printf(" > %s\n", str);
            if(!strcmp(str, "#")) {
                cond++;
            }
            if(cond == 1) {
                cond++;
                continue;
            }
            if(cond == 2) {
                cur = new_a(cur, str);
            }
        }

    // attrnode traversal
    /*
    for(cur = head; cur; cur = cur->next)
        dbg_a(cur);
    */
    destroy_a(head);
    free(str);
    fclose(fp);
    return 0;
}

