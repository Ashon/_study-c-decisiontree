/**
 * Decision tree generator
 *
 * stbl.c
 *
 * @author juwon.lee
 *
 * @date 2014-04-17
 *
 * mit licensed.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "adt_dtree.h"

stbl* new_stbl(stbl* st, attr* attr_clss, attr* attr_node, int* len) {
    stbl* ins = (stbl*)malloc(sizeof(stbl));
    scel* cur_scel;

    clss* cur_clss;
    clss* cur_node;

    ins->len_stbl = len;
    *(ins->len_stbl) = *(ins->len_stbl) + 1;

    if(st) {
        ins->attr_clss = attr_clss;
        ins->attr_node = attr_node;
    
        ins->len_scel = (int*)malloc(sizeof(int));
        *(ins->len_scel) = 0;
    
        ins->node_scel = new_scel(0, 0, 0, ins->len_scel);
        cur_scel = ins->node_scel;
    
        cur_clss = ins->attr_clss->node_clss->link;
        for(; cur_clss; cur_clss = cur_clss->link) {
            cur_node = ins->attr_node->node_clss->link;
            for(; cur_node; cur_node = cur_node->link)
                cur_scel = new_scel(cur_scel, cur_clss, cur_node, ins->len_scel);
        }

        st->link = ins;
    } else {
        ins->attr_clss = 0;
        ins->attr_node = 0;
        ins->node_scel = 0;
    }

    ins->link = 0;

    return ins;
}

int len_stbl(stbl* s) {
    return *(s->len_stbl);
}

int n_stbl(stbl* s) {
    return *(s->len_stbl) - 1;
}

int nrow_stbl(stbl* s) {
    return n_clss(s->attr_clss->node_clss);
}

int ncol_stbl(stbl* s) {
    return n_clss(s->attr_node->node_clss);
}

int del_stbl(stbl* head) {
    stbl* p = head;
    stbl* q;
    do {
        q = p;
        p = p->link;

        if(q->node_scel){
            del_scel(q->node_scel);
            free(q->len_scel);
        }
        
        free(q);
    } while(p);
}

scel* get_scel(stbl* s, int row, int col) {
    scel* cur;
    int i;
    int coord;
    int len_row = *(s->attr_clss->len_clss) - 1;
    int len_col = *(s->attr_node->len_clss) - 1;
//    printf("get_scel start : %d, %d\n",len_row, len_col);
    if((-1 < row && row < len_row) &&
            (-1 < col && col < len_col)) {
  //      printf("true\n");
        cur = s->node_scel->link;
    //    printf("set coord.. %d, %d -> ",row, col);
        coord = (*(s->attr_node->len_clss) - 1) * row + col;
     //   printf("coord :%d\t", coord);
        for(i = 0; i < coord; i++) {
            cur = cur->link;
        }
       // printf("%p :: val : %d\n", cur, *(cur->len_lobj) - 1);

        return cur;
    } else
//    printf("false\n");
    return 0;
}

float gini_idx(stbl* s, int col) {
    clss* cur;
    int i;
    int n_node_;
    int n_clss_;
    int* clss_;
    
    float gini_idx_ = 1;
    float sigma = 0;

    //printf("move cursor\n");
    cur = s->attr_node->node_clss->link;
    for(i = 0; i < col; i++)
        cur = cur->link;

  //  printf("n_node_\n");
    n_node_ = *(cur->len_lobj)-1;

    n_clss_ = n_clss(s->attr_clss->node_clss);
    clss_ = (int*)calloc(n_clss_, sizeof(int));

    i = 0;
    cur = s->attr_clss->node_clss;
    do { //; cur; cur = cur->link) {
        cur = cur->link; 
//        printf("get scel(%d, %d)\t", i, col);
        clss_[i] = *(get_scel(s, i, col)->len_lobj) - 1;
        i++;
    } while(i < n_clss_);

    for(i = 0; i < n_clss_; i++) {
  //      printf("%d^ / %d^ + ", clss_[i], n_node_);
        sigma += (float)(clss_[i] * clss_[i]) / (float)(n_node_ * n_node_);
    }
   // printf("sigma : %f\t", sigma);

    gini_idx_ -= sigma;

    free(clss_);

    return gini_idx_;
}

float gini_split(stbl* s) {
    return 0;
//    int len_obj_ = *(s->attr_node->node_lobj->link->lobj->len_obj) - 1;
}

void dbg_stbl(stbl* st) {
    stbl* cur = st;
    int i;
    for(; cur; cur = cur->link) {
        printf(" # stbl@%p", cur);
        if(!cur->link && !cur->node_scel)
            printf(" [BLANK]\n");
        else {
            if(cur->link)
                printf(" -> %p", cur->link);
            else
                printf(" [TAIL]");
            if(cur->attr_clss)
                printf("\n   > attr_clss = %p[ %s ]\n",
                        cur->attr_clss, cur->attr_clss->name);
            if(cur->attr_node)
                printf("   > attr_node = %p[ %s ]\n",
                        cur->attr_node, cur->attr_node->name);
            if(cur->node_scel) {
                printf("   > node_scel = %p\n", cur->node_scel);
                dbg_scel(cur->node_scel);
            } else
                printf(" [HEAD - size:%d]\n", n_stbl(cur));
        }
        if(cur->node_scel && cur->node_scel->link) {
        for(i = 0; i < n_clss(cur->attr_node->node_clss->link); i++) {
//         printf("");
    //    printf("cur : %p\n", cur);
      //  printf("cur->attr_node : %p\n", cur->attr_node);
        //printf("cur->atrr_node->node_clss : %p\n", cur->attr_node->node_clss);
           printf("gini idx(clss_length : %d) : %f\n", n_clss(cur->attr_node->node_clss->link), gini_idx(cur, i));
        }
        }
    }
}

