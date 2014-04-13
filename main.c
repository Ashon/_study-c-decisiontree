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
    int* property_int;
    float* property_float;

    struct obj_* next;
} obj;

obj* new_o(obj*, char*);
int del_o(obj*);
void dbg_o(obj*);

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
 * free node
 * @param
 *    head - head of atNode.
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
    }while(p);

    return 0;
}

void dbg_an(atNode* an) {
    atNode* cur = an;
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
 * attribute function.
 */
attr* new_a(attr* a, char* str) {
    attr* instance;
    atNode* cur;

    char* name;
    char* nodes;
    char* node;
    int i, length;

    instance = (attr*)malloc(sizeof(attr));
    if(a) {
        instance->type = (int*)malloc(sizeof(int));
        *(instance->type) = -1;

        name = (char*)calloc(MAX_BUF, sizeof(char));
        strcpy(name, strtok(str,"{"));
        instance->name = (char*)calloc(strlen(name) + 1, sizeof(char));
        strcpy(instance->name, name);
        free(name);

        nodes = strtok(0, "}");
        node = strtok(nodes, ",");
        if(0 < strlen(node)) {
            instance->node_an = new_an(0, 0);
            cur = instance->node_an;
        }

        i = 0;
        length = strlen(instance->name);

        if(!strcmp(&instance->name[length - 1], "@")){
            *(instance->type) = AT_TYPE_CLASS;
            instance->name[length - 1] = '\0';
        }

        if(!strcmp(node, "@")) {
            *(instance->type) = AT_TYPE_CONTINUOUS;
        } else {
            do {
                cur = new_an(cur, node);
                i++;
            } while((node = strtok(0, ",")) != 0);
        }

        if(*(instance->type) == -1)
            if(2 < i)
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
    printf("\n## attr@%p", attr);
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
 * Object control function.
 */

obj* new_o(obj* o, char* str) {
    obj* instance = (obj*)malloc(sizeof(obj));
    // todo for new


    if(o)
        o->next = instance;
    instance->next = 0;

    return instance;
}

int del_o(obj* head) {
    obj* p = head;
    obj* q;
    do {
        q = p;
        p = p->next;
        // todo for free.


        free(q);
    } while(p);
    return 0;
}

// main
int main() {
    FILE* fp;
    char *str = (char*)calloc(MAX_BUF, sizeof(char));
    char filename[] = "./train.dat";

    printf("263: ## init node_attr .. ");
    attr* node_attr = new_a(0, 0);
    attr* cur_a = node_attr;
    printf("complete\n");

    printf("268: ## init node_obj .. ");
    obj* node_obj = new_o(0, 0);
    obj* cur_o = node_obj;
    printf("complete\n");

    int cond = 0;

    printf("275: ## open data file > %s .. ", filename);
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf(" !error\n");
        printf("279: ## file open error\n");
        return 1;
    } else {
        printf("complete\n");
        printf("283: ## read file\n");
        while(fgets(str, MAX_BUF, fp)) {
            if(0 < strlen(str))
                str[strlen(str) - 1] = '\0';
//            printf(" readline[cond = %d]> %s", cond, str);

            if(!strcmp(str, "#")) {
                printf("290: ## condtion : %d\n", ++cond);
                continue;
            }

            if(cond == 1) {
                printf("295:   > gen node_attr : %p <- \"%s\"", cur_a, str);
                cur_a = new_a(cur_a, str);
            }

            if(cond == 2) {
                printf("300:   > gen node_obj : %p <- \"%s\"", cur_o, str);
                cur_o = new_o(cur_o, str);
            }

            printf("\n");
        }
    }
    // attrnode traversal
    for(cur_a = node_attr; cur_a; cur_a = cur_a->next)
        dbg_a(cur_a);

    del_a(node_attr);
    del_o(node_obj);
    free(str);
    fclose(fp);
    return 0;
}

