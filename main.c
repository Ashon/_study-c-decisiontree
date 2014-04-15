/**
 * Decision Tree Genarator v0.1
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

// predefined macros.
#define MAX_BUF 255
#define ULL unsigned long long

// attr type constants.
#define AT_TYPE_TARGET 0
#define AT_TYPE_BINARY 1
#define AT_TYPE_CATEGORICAL 2
#define AT_TYPE_CONTINUOUS 3

/**
 * ADTs for decision tree generator.
 *
 * @dependency
 *  +-> d_tree : decision tree
 *    |
 *    +---> int* len_attr : length of attribute node (direct)
 *    +---> int* len_obj : length of object node (direct)
 *    |
 *    +---> attr* node_attr : [single list]
 *    |   |
 *    |   +---> int* len_attr : points to [d_tree->len_attr] (indirect)
 *    |   +---> char* name : attribute name
 *    |   +---> int* type : attribte type
 *    |   +---> int* len_clss : length of attribute's class.
 *    |   | 
 *    |   +---> clss* node_clss : [single list]
 *    |   |   |
 *    |   |   +---> int* len_clss : points to [attr->len_clss] (indirect)
 *    |   |   +---> char* name : class name
 *    |   |   |
 *    |   |   +---> clss* link : next clss node.
 *    |   |
 *    |   +-> *link : next attr node.
 *    |
 *    +---> obj* node_obj : [single list]
 *        |
 *        +---> int* len_obj : points to [d_tree->len_obj] (indirect)
 *        +---> int* len_prop : points to [d_tree->len_attr] (indirect)
 *        +---> int* prop_int : property array of obj.
 *        |
 *        +---> obj* link : next obj node.
 *
 * @constraint
 *    - # of obj's property equals to # of attr
 *    - all of [single list] has a head node is empty.
 *        [HEAD] -> [node] -> ... -> 0
 */

// ======== Define ADT ========

/*
 * ADT - clss
 */
typedef struct clss_ {
    int* len_clss; // indirect
    char* name;
    struct clss_* link;
} clss;

// function table of clss
clss* new_clss(clss*, char*, int*);
int len_clss(clss*);
int del_clss(clss*);
void dbg_clss(clss*);

/*
 * ADT - attr
 */
typedef struct attr_ {
    int* len_attr; // indirect
    char* name;
    int* type;
    int* len_clss; // direct
    clss* node_clss;
    struct attr_ * link;
} attr;

// function table of attr
attr* new_attr(attr*, char*, int*);
int len_attr(attr*);
int del_attr(attr*);
void dbg_attr(attr*);

/**
 * ADT - obj
 */
typedef struct obj_ {
    int* len_obj; // indirect
    int* len_prop; // indirect
    int* prop_int;
    // float* prop_float;
    struct obj_* link;
} obj;

// function table of obj
obj* new_obj(obj*, char*, int*, int*);
int len_obj(obj*);
int len_prop(obj*);
int del_obj(obj*);
void dbg_obj(obj*);

/**
 * ADT - d_tree
 */
typedef struct d_tree_ {
    int* len_attr;
    int* len_obj;
    attr* node_attr;
    obj* node_obj;
} d_tree;

// function table of d_tree
d_tree* new_dtree(d_tree*, char*);
int del_dtree(d_tree*);

// ======== Implementation of ADT ========

/*
 * new_clss(clss*, char*, int*)
 *
 * @description
 *    makes a new clss ins link of *clss.
 *
 * @param
 *    c - clss pointer to attach a new clss
 *    str - name of new class instance
 *    len_clss - # of clss
 *
 * @return
 *    clss* - new clss instance's pointer
 */
clss* new_clss(clss* c, char* str, int* len_clss) {
    clss* ins;
    ins = (clss*)malloc(sizeof(clss));

    ins->len_clss = len_clss;
    *(ins->len_clss) = *(ins->len_clss) + 1;

    if(str) {
        ins->name = (char*)calloc(strlen(str) + 1, sizeof(char));
        strcpy(ins->name, str);

    } else
        ins->name = 0;

    if(c)
        c->link = ins;
    ins->link = 0;

    return ins;
}

/*
 * len_clss(clss*)
 * 
 * @description
 *    returns # of clss.
 *
 * @param
 *    c - clss
 *
 * @return
 *    int - # of clss
 */
int len_clss(clss* c) {
    return *(c->len_clss);
}

/*
 * del_clss(clss*)
 *
 * @description
 *    free memory all of clss
 *
 * @param
 *    head - head of clss.
 *
 * @return
 *    0 - returns 0 when 'free' finished.
 */
int del_clss(clss* head) {
    clss* p;
    clss* q;

    p = head;

    do {
        q = p;
        p = p->link;
        if(q->name)
            free(q->name);

        free(q);
    } while(p);

    return 0;
}

void dbg_clss(clss* head) {
    clss* cur = head;
    for(; cur; cur = cur->link) {
        printf("     ## clss@%p", cur);
        if(cur->link == 0 && cur->name == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->name)
                printf("\n        > name = %s\n", cur->name);
            else
                printf(" [HEAD - len:%d]\n", len_clss(cur));
        }
    }
}

/*
 * new_attr(attr*, char*, int*)
 *
 * @description
 *    makes a new attr ins link of *a.
 * 
 * @param
 *    a - attr pointer to attach a new node.
 *
 *    str - string
 *       formed string such as "[ATTR_NAME]{[NODE_NAME],[NODE_NAME], .. }"
 *       [ATTR_NAME] - attribute's name
 *       [NODE_NAME] - node(class)'s name of attribute.
 *
 *    len_attr - # of attr (indirect)
 *
 * @return
 *    attr* - new attr instance's pointer.
 */
attr* new_attr(attr* a, char* str, int* len_attr) {
    attr* ins;
    clss* cur;

    char* buf;

    char* node;
    int name_length;

    ins = (attr*)malloc(sizeof(attr));
    ins->len_attr = len_attr;
    *(ins->len_attr) = *(ins->len_attr) + 1;

    if(a) {
        ins->type = (int*)malloc(sizeof(int));
        *(ins->type) = -1;

        buf = (char*)calloc(MAX_BUF, sizeof(char));
        strcpy(buf, strtok(str, "{"));
        ins->name = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(ins->name, buf);
        free(buf);

        node = strtok(strtok(0, "}"), ",");
        if(0 < strlen(node)) {
            ins->len_clss = (int*)malloc(sizeof(int));
            *(ins->len_clss) = 0;
            ins->node_clss = new_clss(0, 0, ins->len_clss);
            cur = ins->node_clss;
        }

        name_length = strlen(ins->name);
        if(!strcmp(&ins->name[name_length - 1], "@")){
            *(ins->type) = AT_TYPE_TARGET;
            ins->name[name_length - 1] = '\0';
        }

        if(!strcmp(node, "@")) {
            *(ins->type) = AT_TYPE_CONTINUOUS;
        } else do {
            cur = new_clss(cur, node, ins->len_clss);
        } while(node = strtok(0, ","));

        if(*(ins->type) == -1)
            if(2 < *(ins->len_clss))
                *(ins->type) = AT_TYPE_CATEGORICAL;
            else
                *(ins->type) = AT_TYPE_BINARY;

        a->link = ins;

    } else {
        ins->len_attr = len_attr;
        ins->name = 0;
        ins->type = 0;
        ins->len_clss = 0;
        ins->node_clss = 0;
    }

    ins->link = 0;

    return ins;
}

/*
 * len_attr(attr*)
 *
 * @description
 *    returns # of attr.
 *
 * @param
 *    a - attr
 *
 * @return
 *    int - # of attr nodes.
 */
int len_attr(attr* a) {
    return *(a->len_attr);
}

/*
 * del_attr(attr*)
 *
 * @description
 *    free all of attr node.
 *
 * @param
 *    head - head of attr node.
 *
 * @return
 *    0
 */
int del_attr(attr* head) {
    attr* p = head;
    attr* q;

    do {
        q = p;
        p = p->link;
        // todo for free
        if(q->name)
            free(q->name);
        if(q->type)
            free(q->type);
        if(q->len_clss)
            free(q->len_clss);
        if(q->node_clss)
            del_clss(q->node_clss);
        //
        free(q);
    } while(p);

    return 0;
}

void dbg_attr(attr* attr) {
    printf("## attr@%p", attr);

    if(!attr->link && !attr->name)
        printf(" [BLANK]\n");
    else {
        if(attr->link)
            printf(" -> %p", attr->link);
        else
            printf(" [TAIL]");

        if(attr->name)
            printf("\n   > name = %s\n", attr->name);
        else
            printf(" [HEAD - len:%d]\n", *(attr->len_attr));

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

        if(attr->node_clss) {
            printf("   > node_clss = %p\n", attr->node_clss);
            dbg_clss(attr->node_clss);
        }
    }
}

/*
 * new_obj
 *
 * @description
 *    makes a new obj ins link of o.
 *
 * @param
 *    o - target obj
 *    str - formed string such as "1,2,3,4"
 *    len_obj - # of object (indirect)
 *    len_prop - # of property (indirect)
 *               equals # of attribute.
 *
 * @return
 *    obj* - new obj instance's pointer.
 */
obj* new_obj(obj* o, char* str, int* len_obj, int* len_prop) {
    char* buf;
    obj* ins = (obj*)malloc(sizeof(obj));

    int* cur;
    // todo for new
    ins->len_obj = len_obj;
    *(ins->len_obj) = *(ins->len_obj) + 1;

    ins->len_prop = len_prop;

    if(*(len_prop)) {
        ins->prop_int = (int*)calloc(*(len_prop), sizeof(int));
        cur = ins->prop_int;

        buf = strtok(str, ",");
        do {
            *(cur++) = (int)atoi(buf);
        } while(buf = strtok(0, ","));
    } else {
        ins->prop_int = 0;
    }
    
    if(o)
        o->link = ins;
    ins->link = 0;

    return ins;
}

/*
 * len_o(obj*)
 *
 * @description
 *    returns # of obj
 *
 * @param
 *    o - obj
 *
 * @return
 *    int - # of obj node.
 */
int len_obj(obj* o) {
    return *(o->len_obj);
}

int len_prop(obj* o) {
    return *(o->len_prop);
}
/*
 * del_o
 * 
 * @description
 *    free memory all of obj's node.
 * 
 * @param
 *    o - head of obj node.
 *
 * @return
 *    0
 */
int del_obj(obj* head) {
    obj* p = head;
    obj* q;

    do {
        q = p;
        p = p->link;
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
void dbg_obj(obj* head) {
    obj* cur = head;
    int i;
    int length = len_prop(head);
    for(; cur; cur = cur->link) {
        printf("## obj@%p", cur);
        if(cur->link == 0 && cur->prop_int == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->prop_int){
                printf("\n   > values[len:%d] = [", length);
                for(i = 0;i < length; i++){
                    printf("%d", cur->prop_int[i]);
                    if(i < length - 1)
                        printf(", ");
                }
                printf("]\n");
            }
            else
                printf(" [HEAD - len:%d]\n", len_obj(cur));
        }
    }
}

d_tree* new_dtree(d_tree* t, char* filename) {
    d_tree* ins;

    FILE* fp;
    char *buf;
    int cond = -1;

    attr* cur_attr;
    obj* cur_obj;

    printf("file open");

    if((fp = fopen(filename, "r"))== 0){
        printf("file open error");
        return 0;
    } else {
        printf("*****");
        ins = (d_tree*)malloc(sizeof(d_tree));
        buf = (char*)calloc(MAX_BUF, sizeof(char));

        printf("alloc");
        ins->len_attr = (int*)malloc(sizeof(int));
        ins->len_obj = (int*)malloc(sizeof(int));

        *(ins->len_attr) = 0;
        *(ins->len_obj) = 0;

        ins->node_attr = new_attr(0, 0, ins->len_attr);
        ins->node_obj = new_obj(0, 0, ins->len_obj, ins->len_attr);

        cur_attr = ins->node_attr;
        cur_obj = ins->node_obj;

        cond++;

        while(fgets(buf, MAX_BUF, fp)) {
            if(0 < strlen(buf))
                buf[strlen(buf) - 1] = '\0';

            if(!strcmp(buf, "#")) {
                cond++;
                continue;
            }

            if(cond == 1) {
                cur_attr = new_attr(cur_attr, buf, ins->len_attr);
            }
            if(cond == 2) {
                cur_obj = new_obj(cur_obj, buf, ins->len_obj, ins->len_attr);
            }
        }
        t = ins;
        return t;
    }

    free(buf);
    fclose(fp);

    return 0;
}

int del_dtree(d_tree* t) {
    del_attr(t->node_attr);
    del_obj(t->node_obj);

    free(t->len_attr);
    free(t->len_obj);

    free(t);
    return 0;
}

// ======== main ========

int main() {
    char filename[] = "./train.dat";
    d_tree* dtr;
    
    printf("file name : %s\n", filename);

    dtr = new_dtree(dtr, filename);
    // object traversal

 //   del_dtree(tree);

    return 0;
}
