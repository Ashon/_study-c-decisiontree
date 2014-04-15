/**
 * Decision Tree Genarator v0.1
 *
 * dtree.h
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

#include "attr.h"
#include "obj.h"

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

