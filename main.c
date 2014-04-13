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
 *    attr_v < length, @attr ... >
 *    attr < name, type, @attrNode_v, *prev, *next >
 *    attrNode_v < length, @attrNode ... >
 *    attrNode < name, *prev, *next >
 */

/*
 * ADT - atNode
 */
typedef struct atNode_ {
    char* name;

    struct atNode_* prev;
    struct atNode_* next;
} atNode;

atNode* new_an(atNode*, char*);
int destroy_an(atNode*);
atNode* link_an(atNode*, atNode*);
atNode* next_an(atNode*);
atNode* prev_an(atNode*);
ULL size_an(atNode*);

/*
 * ADT - attr
 */
typedef struct attr_ {
    char* name;
    int* type;

    atNode* node;

    struct attr_ * prev;
    struct attr_ * next;
} attr;

attr* new_A(attr*, char*);
int destroy_A(attr*);
attr* link_A(attr*, attr*);
void dbg_A(attr*);
ULL size_A(attr*);

typedef struct attr_v_ {
    int* length;
    attr* head;
} attr_v;

/**
 * ADT - Object
 */
typedef struct Object_ {
    int* property_int;
    float* property_float;
} Object;

/*
 * attr Node Control Functions..
 */
atNode* new_an(atNode* an, char* str) {
    atNode* target = (atNode*)malloc(sizeof(atNode));
    target->name = (char*)calloc(strlen(str) + 1, sizeof(char));
    target->next = 0;
    strcpy(target->name, str);

    return link_an(an, target);
}

int destroy_an(atNode* an) {
    printf("   ## destroy an @ %p\n", an);
    printf("    > free an->name : %s\n", an->name);
    free(an->name);
    printf("    > free an : %p\n", an);
    free(an);
    printf("   ## destroy an complete.\n");
    return 0;
}
atNode* link_an(atNode* prev, atNode* next) {
    prev->next = next;
    next->prev = prev;

    return next;
}

atNode* next_an(atNode* an) {
    return an->next;
}

atNode* prev_an(atNode* an) {
    return an->prev;
}

void dbg_an(atNode* an) {
    printf("atNode@%p", an);
    printf("[name=%s,", an->name);
    printf("prev=%p,", an->prev);
    printf("next=%p]", an->next);
}

ULL size_an(atNode* an) {
    ULL size = 0;
    if(an->name)
        size += strlen(an->name);
    size += sizeof(an->next);
    size += sizeof(an->prev);

    return size;
}

/*
 * attr Control Functions..
 */
attr* new_A(attr* a, char* str) {
    attr* target;
    char* name;
    char* nodes;
    char* node;
    int i, length;

    target = (attr*)malloc(sizeof(attr));
    target->type = (int*)malloc(sizeof(int));
    target->next = 0;

    name = (char*)calloc(MAX_BUF, sizeof(char));
    strcpy(name, strtok(str,"{"));
    target->name = (char*)calloc(strlen(name) + 1, sizeof(char));
    strcpy(target->name, name);
    nodes = strtok(0, "}");
    free(name);
    node = strtok(nodes, ",");
    // initialize node_v
    if(0 < strlen(node))
    {
        target->anv = new_anv(target->anv);
    }

    i = 0;
    if(!strcmp(node, "@")) {
        *(target->type) = AT_TYPE_CONTINUOUS;
        /*
         * continuous type
         */
    } else {
        do {
            new_an_to_anv(target->anv, node);
            i++;
        } while((node = strtok(0, ",")) != 0);
        if(2 < i) {
            *(target->type) = AT_TYPE_CATEGORICAL;
        } else {
           *(target->type) = AT_TYPE_BINARY;
        }
    }
    return link_A(a, target);
}

int destroy_A(attr* a) {
    printf("## destroy attr @ %p (size = %d)\n", a, (int)size_A(a));
    printf(" > free a->name : %s\n", a->name);
    free(a->name);
    printf(" > free a->anv : %p\n", a->anv);
    destroy_anv(a->anv);
    printf(" > free a->type : %p\n", a->type);
    free(a->type);
    printf(" > free a : %p\n", a);
    free(a);
    printf("## destroy attr complete.\n");
    return 0;
}

attr* link_A(attr* prev, attr* next) {
    prev->next = next;
    next->prev = prev;

    return next;
}

char* name_A(attr* attr) {
    return attr->name;
}

attr* prev_A(attr* a) {
    return a->prev;
}

attr* next_A(attr* a) {
    return a->next;
}

int type_A(attr* a) {
    return *(a->type);
}

void dbg_A(attr* attr) {
    printf("attr@%p", attr);
    printf("[name=%s,", name_A(attr));
    printf("type=%d,", type_A(attr));
    dbg_anv(attr->anv);
//    printf("node_v=%s", dbg_an(attr->anv));
    printf("prev=%p,", prev_A(attr));
    printf("next=%p]\n", next_A(attr));
}

ULL size_A(attr* a) {
    ULL size = 0;
    if(a->name)
        size += strlen(a->name);
    size += sizeof(a->type);
    if(a->anv != 0);
        size += size_anv(a->anv);
    return size;
}
// main
int main() {
    FILE* fp;
    char *str = (char*)calloc(MAX_BUF, sizeof(char));

    attr* head = (attr*)malloc(sizeof(attr));
    head->name = 0;
    head->type = 0;
    head->anv = 0;
    head->prev = 0;
    head->next = 0;

    attr* attrNode = head;

    attr* cur;

    int cond = 0;

    printf("head -> %p\n", head);

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
                printf("condition : %d\n", cond);
            }
            if(cond == 1) {
                cond++;
                continue;
            }
            if(cond == 2) {
                printf("gen attr\n");
                attrNode = new_A(attrNode, str);
                dbg_A(attrNode);
            }
        }
        
    // attrnode traversal
    
    for(attrNode = next_A(head);
            attrNode != 0;
            attrNode = next_A(attrNode))
        dbg_A(attrNode);

    printf("\n# destroy node\n");
    
    for(attrNode = next_A(head);
            next_A(attrNode) != 0;
            attrNode = next_A(attrNode)) {
        cur = prev_A(attrNode);
        destroy_A(cur);
    }
    destroy_A(attrNode);
    printf("\n# destroy complete\n");
    free(str);

    fclose(fp);
    return 0;
}

