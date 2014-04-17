/**
 * Decision Tree Genarator v0.1
 *
 * 
 * adt_dtree.h
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

// attr type constants.
#define AT_TYPE_TARGET 0
#define AT_TYPE_BINARY 1
#define AT_TYPE_MULTIPLE 2
#define AT_TYPE_CONTINUOUS 3

/**
 * Abstract data types of decision tree generator.
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
 *    |   |   +---> int* len_lobj : # of node_lobj
 *    |   |   +---> lobj* node_lobj : link node of [dtree->node_obj]
 *    |   |   |   |
 *    |   |   |   +---> int* len_lobj : points to [attr->len_lobj]
 *    |   |   |   +---> obj* lobj : points to a [dtree->obj_node]
 *    |   |   |   |                belonging to [attr->clss]
 *    |   |   |   |
 *    |   |   |   +---> lobj* link : next lobj node.
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
 *
 * @constraint
 *    - # of obj's property equals to # of attr:
 *    - all of [single list]s have empty head node.
 *        [HEAD] -> [node] -> ... -> 0
 */


// ADT - prop
typedef struct prop_ {
    int* len_prop; // indirect
    int* tag;
    int* val;
    struct prop_* link;
} prop;

// function table of prop
prop* new_prop(prop*, int*, int*);
int len_prop(prop*);
int n_prop(prop*);
int get_prop(prop*);
int del_prop(prop*);
void dbg_prop(prop*);

// ADT - obj
typedef struct obj_ {
    int* len_obj; // indirect
    int* len_prop; // direct

    prop* node_prop;
    
    struct obj_* link;
} obj;

// function table of obj
obj* new_obj(obj*, char*, int*);
prop* obj_prop(obj*, int);
int len_obj(obj*);
int n_obj(obj*);
obj* equal_obj(obj*, obj*);
int del_obj(obj*);
void dbg_obj(obj*);

// ADT - lobj
typedef struct lobj_ {
	int* len_lobj;
	obj* lobj;

	struct lobj_* link;
} lobj;

// function table of lobj
lobj* new_lobj(lobj*, obj*, int*);
int del_lobj(lobj*);
void dbg_lobj(lobj*);
int len_lobj(lobj*);
int n_lobj(lobj*);
obj* fndobj_lobj(lobj*, obj*);

// ADT - clss
typedef struct clss_ {
    int* len_clss; // indirect
    char* name;

    int* len_lobj; // direct
    lobj* node_lobj;

    struct clss_* link;
} clss;

// function table of clss
clss* new_clss(clss*, char*, int*);
int len_clss(clss*);
int n_clss(clss*);
int del_clss(clss*);
void dbg_clss(clss*);

// ADT - attr
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
int n_attr(attr*);
int del_attr(attr*);
void dbg_attr(attr*);

// ADT - dtree
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
attr* add_attr(dtree*, attr*, char*);
attr* get_clss(dtree*);
obj* add_obj(dtree*, obj*, char*);

// ADT - scel - split cell
typedef struct scel_ {
	int* len_lobj; // the value of split table cell.

	lobj* node_lobj;

	struct scel_* link;
} scel;

//function table of scel
scel* new_scel(scel*, clss*, clss*);
int len_scel(scel*);
int n_scel(scel*);
int del_scel(scel*);
void dbg_scel(scel*);

// ADT - stbl - split table
typedef struct stbl_ {
	attr* attr_node; // column length = col->len_clss
	attr* attr_clss; // row length = row->len_clss

	scel* node_scel;

	struct stbl_* link;
} stbl;

//function table of stbl
stbl* new_stbl(stbl*, attr*, attr*);
int len_stbl(stbl*);
int n_stbl(stbl*);
int nrow_stbl(stbl*);
int ncol_stbl(stbl*);
int del_stbl(stbl*);
void dbg_stbl(stbl*);





