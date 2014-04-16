/**
 * Decision Tree Genarator v0.1
 *
 * attr.c
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

#include "adt_dtree.h"

/**
 * new_attr(attr*, char*, int*)
 *
 * @description
 *    makes a new attr instance link of *a.
 * 
 * @param
 *    a - attr pointer to attach a new node.
 *
 *    str - string
 *       formed string such as "[attr]{[node],[node], .. }"
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
                *(ins->type) = AT_TYPE_MULTIPLE;
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
 *    returns # of attr. (include head node)
 *
 * @param
 *    a - attr*
 *
 * @return
 *    int - # of attr nodes.
 */
int len_attr(attr* a) {
    return *(a->len_attr);
}

/**
 * n_attr(attr*)
 *
 * @description
 *    returns # of valid attr.
 *
 * @param
 *    a - attr*
 *
 * @return
 *    int - # of valid attr node.
 */
int n_attr(attr* a) {
    return *(a->len_attr) - 1;
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
                printf(" [HEAD - size:%d]\n", n_attr(cur));
    
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
                        printf(" [T_MULTIPLE]\n");
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

