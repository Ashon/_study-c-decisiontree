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
 *  +-> dtree : decision tree
 *    |
 *    +---> int* len_attr : length of attribute node (direct)
 *    +---> int* len_obj : length of object node (direct)
 *    |
 *    +---> attr* node_attr : [single list]
 *    |   |
 *    |   +---> int* len_attr : points to [dtree->len_attr] (indirect)
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
 *        +---> int* len_obj : points to [dtree->len_obj] (indirect)
 *        +---> int* len_prop : # of property (direct)
 *        |
 *        +---> prop* node_prop : [single list]
 *        |   |
 *        |   +---> int* len_prop : points to [obj->len_prop] (indirect)
 *        |   +---> int* val : property value.
 *        |   |
 *        |   +---> prop* link : next prop node.
 *        |
 *        +---> obj* link : next obj node.
 *
 * @constraint
 *    - # of obj's property equals to # of attr:
 *    - all of [single list]s have empty head node.
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
 * ADT - prop
 */
typedef struct prop_ {
    int* len_prop; // indirect
    int* val;
    struct prop_* link;
} prop;

// function table of prop
prop* new_prop(prop*, int*, int*);
int len_prop(prop*);
int get(prop*);
int del_prop(prop*);
void dbg_prop(prop*);

/**
 * ADT - obj
 */
typedef struct obj_ {
    int* len_obj; // indirect
    int* len_prop; // direct
    prop* node_prop;
    // float* prop_float;
    struct obj_* link;
} obj;

// function table of obj
obj* new_obj(obj*, char*, int*);
int len_obj(obj*);
int del_obj(obj*);
void dbg_obj(obj*);

/**
 * ADT - dtree
 */
typedef struct dtree_ {
    int* len_attr;
    int* len_obj;
    attr* node_attr;
    obj* node_obj;
} dtree;

// function table of dtree
dtree* new_dtree(dtree*, FILE*);
int del_dtree(dtree*);
void dbg_dtree(dtree*);

// ======== Implementation of ADT ========

/**
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

/**
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

/**
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

/**
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
        ins->name = 0;
        ins->type = 0;
        ins->len_clss = 0;
        ins->node_clss = 0;
    }

    ins->link = 0;

    return ins;
}

/**
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

/**
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

void dbg_attr(attr* head) {
    attr* cur = head;
    for(; cur; cur = cur->link){
        printf("## attr@%p", cur);
        if(!cur->link && !cur->name)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
    
            if(cur->name)
                printf("\n   > name = %s\n", cur->name);
            else
                printf(" [HEAD - len:%d]\n", *(cur->len_attr));
    
            if(cur->type) {
                printf("   > type = %d",*(cur->type));
                switch(*(cur->type)) {
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
    
            if(cur->node_clss) {
                printf("   > node_clss = %p\n", cur->node_clss);
                dbg_clss(cur->node_clss);
            }
        }
    }
}
/**
 * new_prop
 */
prop* new_prop(prop* p, int* val, int* len_prop) {
    prop* ins = (prop*)malloc(sizeof(prop));
    ins->len_prop = len_prop;
    *(ins->len_prop) = *(ins->len_prop) + 1;

    if(val) {
        ins->val = (int*)malloc(sizeof(int));
        *(ins->val) = *(val);
    } else
        ins->val = 0;

    if(p)
        p->link = ins;

    ins->link = 0;
    return ins;
}

int len_prop(prop* p) {
    return *(p->len_prop);
}

int get_prop(prop* p) {
    return *(p->val);
}

int del_prop(prop* head) {
    prop* p = head;
    prop* q;
    do {
        q = p;
        p = p->link;
        if(q->val);
            free(q->val);
        free(q);
    } while(p);
    return 0;
}

void dbg_prop(prop* head) {
    prop* cur = head;

    for(; cur; cur = cur->link) {
        printf("     ## prop@%p", cur);
        if(cur->link == 0 && cur->val == 0)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->val)
                printf("\n        > val = %d\n", *(cur->val));
            else
                printf(" [HEAD - len:%d]\n", len_prop(cur));
        }
    }
}
/**
 * new_obj(obj*, char*, int*)
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
obj* new_obj(obj* o, char* str, int* len_obj) {
    obj* ins = (obj*)malloc(sizeof(obj));
    prop* cur;
    char* buf;
    int val;
    // todo for new

    ins->len_obj = len_obj;
    *(ins->len_obj) = *(ins->len_obj) + 1;

    if(str) {
        ins->len_prop = (int*)malloc(sizeof(int));
        *(ins->len_prop) = 0;

        ins->node_prop = new_prop(0, 0, ins->len_prop);
        cur = ins->node_prop;

        buf = strtok(str, ",");
        do {
            val = atoi(buf);
            cur = new_prop(cur, &val, ins->len_prop);
        } while(buf = strtok(0, ","));

    } else {
        ins->node_prop = 0;
    }
    
    if(o)
        o->link = ins;
    ins->link = 0;

    return ins;
}

/**
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

/**
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
        if(q->node_prop)
            del_prop(q->node_prop);
        free(q);
    } while(p);

    return 0;
}

/**
 * dbg_o
 * 
 * print log of object node.
 */
void dbg_obj(obj* head) {
    obj* cur = head;
    int i;

    for(; cur; cur = cur->link) {
        printf("## obj@%p", cur);
        if(!cur->link && !cur->node_prop)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            printf("\n");
            if(cur->node_prop) {
                printf("   > node_prop = %p\n", cur->node_prop);
                dbg_prop(cur->node_prop);
            } else
                printf(" [HEAD - len:%d]\n", *(cur->len_obj)); 
        }
    }
}

dtree* new_dtree(dtree* t, FILE* fp) {
    char *buf = (char*)calloc(MAX_BUF, sizeof(char));
    int cond = -1;

    attr* cur_attr;
    obj* cur_obj;

    dtree* ins = (dtree*)malloc(sizeof(dtree));

    ins->len_attr = (int*)malloc(sizeof(int));
    ins->len_obj = (int*)malloc(sizeof(int));

    *(ins->len_attr) = 0;
    *(ins->len_obj) = 0;

    ins->node_attr = new_attr(0, 0, ins->len_attr);
    ins->node_obj = new_obj(0, 0, ins->len_obj);

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
            cur_obj = new_obj(cur_obj, buf, ins->len_obj);
        }
    }
    free(buf);
    
    t = ins;
    return ins;
    
}

int del_dtree(dtree* t) {
    del_attr(t->node_attr);
    del_obj(t->node_obj);

    free(t->len_attr);
    free(t->len_obj);

    free(t);
    return 0;
}

void dbg_dtree(dtree* t) {
    printf("## dtree@%p\n", t);
    printf("   > node_attr = %p\n", t->node_attr);
    dbg_attr(t->node_attr);
    printf("   > node_obj = %p\n", t->node_obj);
    dbg_obj(t->node_obj);
}

