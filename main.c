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
int del_an(atNode*);
void dbg_an(atNode*);

/*
 * ADT - attr
 */
typedef struct attr_ {
    char* name;
    int* type;

    atNode* node_an;
    struct attr_ * next;
} attr;

attr* new_a(attr*, char*);
int del_a(attr*);
void dbg_a(attr*);

/**
 * ADT - Object
 */
typedef struct obj_ {
    int* prop_int;
    // float* prop_float;

    struct obj_* next;
} obj;

obj* new_o(obj*, char*, int);
int del_o(obj*);
void dbg_o(obj*, int);

/*
 * new_node
 *
 * @description
 *    makes a new atNode instance next of *an.
 *
 * @param
 *    an - atNode pointer to attach a new atNode
 *
 * @return
 *    atNode* - new atNode instance's pointer
 */
atNode* new_an(atNode* an, char* str) {
    atNode* instance;

    instance = (atNode*)malloc(sizeof(atNode));

    if(str) {
        instance->name = (char*)calloc(strlen(str) + 1, sizeof(char));
        strcpy(instance->name, str);
    } else
        instance->name = 0;

    if(an)
        an->next = instance;
    instance->next = 0;

    return instance;
}

/*
 * del_an
 *
 * @description
 *    free memory all of atNode
 *
 * @param
 *    head - head of atNode.
 *
 * @return
 *    0 - returns 0 when 'free' finished.
 */
int del_an(atNode* head) {
    atNode* p;
    atNode* q;

    p = head;

    do {
        q = p;
        p = p->next;
        if(q->name)
            free(q->name);
        free(q);
    } while(p);

    return 0;
}

void dbg_an(atNode* head) {
    atNode* cur = head;
    for(; cur; cur = cur->next) {
        printf("     ## atNode@%p", cur);
        if(cur->next == 0 && cur->name == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->next)
                printf(" -> %p", cur->next);
            else
                printf(" [TAIL]");
            if(cur->name)
                printf("\n        > name = %s\n", cur->name);
            else
                printf(" [HEAD]\n");
        }
    }
}

/*
 * new_a
 *
 * @description
 *    makes a new attr instance next of *a.
 * 
 * @param
 *    a - attr pointer to attach a new node.
 *
 *    str - string
 *       formatted string such as "[ATTR_NAME]{[NODE_NAME],[NODE_NAME], .. }"
 *       [ATTR_NAME] - attribute's name
 *       [NODE_NAME] - node(class)'s name of attribute.
 *
 * @return
 *    attr* - new attr instance's pointer.
 */
attr* new_a(attr* a, char* str) {
    attr* instance;
    atNode* cur;

    char* buf;

    char* nodes;
    char* node;
    int count_node;
    int name_length;

    instance = (attr*)malloc(sizeof(attr));
    if(a) {
        instance->type = (int*)malloc(sizeof(int));
        *(instance->type) = -1;

        buf = (char*)calloc(MAX_BUF, sizeof(char));
        strcpy(buf, strtok(str,"{"));
        instance->name = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(instance->name, buf);
        free(buf);

        nodes = strtok(0, "}");
        node = strtok(nodes, ",");
        if(0 < strlen(node)) {
            instance->node_an = new_an(0, 0);
            cur = instance->node_an;
        }

        name_length = strlen(instance->name);
        if(!strcmp(&instance->name[name_length - 1], "@")){
            *(instance->type) = AT_TYPE_CLASS;
            instance->name[name_length - 1] = '\0';
        }

        if(!strcmp(node, "@")) {
            *(instance->type) = AT_TYPE_CONTINUOUS;
        } else {
            count_node = 0;
            do {
                cur = new_an(cur, node);
                count_node++;
            } while(node = strtok(0, ","));
        }

        if(*(instance->type) == -1)
            if(2 < count_node)
                *(instance->type) = AT_TYPE_CATEGORICAL;
            else
                *(instance->type) = AT_TYPE_BINARY;

        a->next = instance;

    } else {
        instance->name = 0;
        instance->type = 0;
        instance->node_an = 0;
    }

    instance->next = 0;

    return instance;
}

int del_a(attr* head) {
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
        if(q->node_an)
            del_an(q->node_an);
        //
        free(q);
    } while(p);

    return 0;
}

void dbg_a(attr* attr) {
    printf("## attr@%p", attr);

    if(!attr->next && !attr->name)
        printf(" [BLANK]\n");
    else {
        if(attr->next)
            printf(" -> %p", attr->next);
        else
            printf(" [TAIL]");

        if(attr->name)
            printf("\n   > name = %s\n", attr->name);
        else
            printf(" [HEAD]\n");

        if(attr->type) {
            printf("   > type = %d",*(attr->type));
            switch(*(attr->type)) {
                case 0 :
                    printf(" [T_CLASS]\n");
                break;
                case 1 :
                    printf(" [T_BINARY]\n");
                break;
                case 2 :
                    printf(" [T_CATEGORICAL]\n");
                break;
                case 3 :
                    printf(" [T_CONTINUOUS]\n");
                break;
            }
        }

        if(attr->node_an) {
            printf("   > node_an = %p\n", attr->node_an);
            dbg_an(attr->node_an);
        }
    }
}

/*
 * new_o
 *
 * @description
 *    makes a new obj instance next of o.
 *
 * @param
 *    o - target obj
 *    str - formatted string likes.. "1,2,3,4"
 * 
 * @return
 *    obj* - new obj instance's pointer.
 */
obj* new_o(obj* o, char* str, int length) {
    char* buf;
    obj* instance = (obj*)malloc(sizeof(obj));

    int* cur;
    // todo for new
    if(length){
        instance->prop_int = (int*)calloc(length, sizeof(int));

        buf = strtok(str, ",");
        cur = instance->prop_int;

        do {
            *(cur++) = (int)atoi(buf);
        } while(buf = strtok(0, ","));

    } else
        instance->prop_int = 0;

    if(o)
        o->next = instance;
    instance->next = 0;

    return instance;
}

/*
 * del_o
 * 
 * @description
 *    free memory all of obj's node.
 * 
 * @param
 *    o - target obj node.
 */
int del_o(obj* head) {
    obj* p = head;
    obj* q;

    do {
        q = p;
        p = p->next;
        // todo for free q.
        free(q->prop_int);
        free(q);
    } while(p);

    return 0;
}

/*
 * dbg_o
 * 
 * print log of object node.
 */
void dbg_o(obj* head, int length) {
    obj* cur = head;
    int i;
    for(; cur; cur = cur->next) {
        printf("## objNode@%p", cur);
        if(cur->next == 0 && cur->prop_int == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->next)
                printf(" -> %p", cur->next);
            else
                printf(" [TAIL]");
            if(cur->prop_int){
                printf("\n   > values = [");
                for(i = 0;i < length; i++){
                    printf("%d", cur->prop_int[i]);
                    if(i < length - 1)
                        printf(", ");
                }
                printf("]\n");
            }
            else
                printf(" [HEAD]\n");
        }
    }
}

// main
int main() {
    FILE* fp;
    char *str = (char*)calloc(MAX_BUF, sizeof(char));
    char filename[] = "./train.dat";
    int cond = -1;
    // # of attribute
    int len_a = 0;
    attr* node_attr;
    attr* cur_a;
    obj* node_obj;
    obj* cur_o;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("file open error\n");
        return 1;

    } else {
        node_attr = new_a(0, 0);
        cur_a = node_attr;

        node_obj = new_o(0, 0, 0);
        cur_o = node_obj;

        cond++;

        while(fgets(str, MAX_BUF, fp)) {
            if(0 < strlen(str))
                str[strlen(str) - 1] = '\0';

            if(!strcmp(str, "#")) {
                cond++;
                continue;
            }

            if(cond == 1) {
                cur_a = new_a(cur_a, str);
                len_a++;
            }

            if(cond == 2) {
                cur_o = new_o(cur_o, str, len_a);
            }
        }
    }

    // attrnode traversal
    for(cur_a = node_attr; cur_a; cur_a = cur_a->next)
        dbg_a(cur_a);

    cur_o = node_obj;
    dbg_o(cur_o, len_a);

    del_a(node_attr);
    del_o(node_obj);

    free(str);
    fclose(fp);

    return 0;
}
