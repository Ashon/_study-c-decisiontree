/**
 * Decision Tree Genarator v0.1
 *
 * ADT_DecisionTree.h
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

#define MAX_BUFFER_SIZE 255

#define ATTRIBUTE_TYPE_CLASS 0
#define ATTRIBUTE_TYPE_BINARY 1
#define ATTRIBUTE_TYPE_CATEGORICAL 2
#define ATTRIBUTE_TYPE_CONTINUOUS 3

/**
 * Abstract data types(ADTs) of decision tree generator.
 *
 * @description
 *    ADT dependency
 *    +-> DecisionTree : decision tree
 *      |
 *      +---> int* attributeLength : length of Attribute List (direct)
 *      +---> int* objectLength : length of Object List (direct)
 *      +---> Attribute* attributeList : [single list]
 *      |   +---> int* attributeLength : [DecisionTree->attributeLength]
 *      |   +---> char* attributeName : Attribute name
 *      |   +---> int* type : Attribute type
 *      |   +---> int* attributeNodeLength : length of Attribute's class.
 *      |   +---> AttributeNode* attributeNodeList : [single list]
 *      |   |   +---> int* attributeNodeLength : 
 *      |   |   |                         [Attribute->attributeNodeLength]
 *      |   |   +---> char* attributeNodeName : class name
 *      |   |   +---> int* objectWrapperLength : # of ObjectWrapper
 *      |   |   +---> ObjectWrapper* objectWrapperList :
 *      |   |   |   |                     [DecisionTree->ObjectList]
 *      |   |   |   +---> int* objectWrapperLength :
 *      |   |   |   |                     [Attribute->objectWrapperLength]
 *      |   |   |   +---> Object* object : [DecisionTree->Object_List]
 *      |   |   |   |                belonging to [Attribute->AttributeNode]
 *      |   |   |   +---> ObjectWrapper* link : next ObjectWrapper List.
 *      |   |   +---> AttributeNode* link : next AttributeNode List.
 *      |   +---> Attribute* link : next Attribute List.
 *      +---> Object* objectList : [single list]
 *      |   +---> int* objectLength : [DecisionTree->objectLength]
 *      |   +---> int* propertyLength : # of Property (direct)
 *      |   +---> Property* propertyList : [single list]
 *      |   |   +---> int* propertyLength : [Object->propertyLength]
 *      |   |   +---> int* value : Property value.
 *      |   |   +---> Property* link : next Property List.
 *      |   +---> Object* link : next Object List.
 *      +---> SplitTable* List_SplitTable : [single list]
 *          +---> int* splitTableLength : [DecisionTree->splitTableLength]
 *          +---> int* objectLength
 *          +---> Attribute* attributeColumn :
 *          |                     [DecisionTree->attributeList]
 *          +---> Attribute* attributeRow :
 *          |                     [DecisionTree->attributeList]
 *          +---> int* splitTableCellLength :
 *          +---> SplitTableCell* splitTableCellList : 
 *          |   +---> int* splitTableCellLength :
 *          |   |             [SplitTable->splitTableCellLength]
 *          |   +---> int* objectWrapperLength :
 *          |   +---> ObjectWrapper* objectWrapperList :
 *          |   +---> SplitTableCell* link : next SplitTableCell List.
 *          +---> SplitTable* link : next splitTable List
 *
 * @constraint
 *    - # of Object's Property equals to # of Attribute:
 *    - all of [single list]s have empty head List.
 *        [HEAD] -> [List] -> ... -> 0
 */

/*
 * ADT - Property
 */
typedef struct Property_ {
    int* propertyLength; // indirect
    int* value;

    struct Property_* link;
} Property;

/*
 * ADT - Object
 */
typedef struct Object_ {
    int* objectLength; // indirect
    int* propertyLength; // direct
    Property* propertyList;
    
    struct Object_* link;
} Object;

/*
 * ADT - ObjectWrapper
 */
typedef struct ObjectWrapper_ {
    int* objectWrapperLength;
    Object* object;

    struct ObjectWrapper_* link;
} ObjectWrapper;

/* 
 * ADT - AttributeNode
 */
typedef struct AttributeNode_ {
    int* attributeNodeLength; // indirect
    char* attributeNodeName;
    int* objectWrapperLength; // direct
    ObjectWrapper* objectWrapperList;

    struct Attribute_* parent;
    struct AttributeNode_* link;
} AttributeNode;

/*
 * ADT - Attribute
 */
typedef struct Attribute_ {
    int* attributeLength; // indirect
    char* attributeName;
    int* attributeType;
    int* attributeNodeLength; // direct

    AttributeNode* attributeNodeList;

    struct Attribute_* link;
} Attribute;

/*
 * ADT - SplitTableCell
 */
typedef struct SplitTableCell_ {
    int* splitTableCellLength;
    int* objectWrapperLength; // the value of split table cell.
    ObjectWrapper* objectWrapperList;

    struct SplitTableCell_* link;
} SplitTableCell;

/*
 * ADT - SplitTable
 */
typedef struct SplitTable_ {
    int* splitTableLength;
    int* objectLength;
    Attribute* attributeColumn; // column length = col->len_AttributeNode
    Attribute* attributeRow; // row length = row->len_AttributeNode
    int* splitTableCellLength;
    SplitTableCell* splitTableCellList;

    struct SplitTable_* link;
} SplitTable;

/*
 * ADT - AttributeNodeBranch
 */
typedef struct AttributeNodeBranch_ {
    AttributeNode attributeNode;
    struct DecisionBranch_* child;

    struct AttributeNodeBranch_* link;
} AttributeNodeBranch;

/*
 * ADT - DecisionTreeBranch
 */
typedef struct DecisionTreeBranch_ {
    Attribute* attribute;
    AttributeNodeBranch* attributeNodeBranchList;

    struct DecisionList_* link;
} DecisionBranch;

/*
 * ADT - DecisionTable
 */
typedef struct DecisionTable_ {
    int* attributeLength;
    int* objectLength;
    int* splitTableLength;
    Attribute* attributeList;
    Object* objectList;
    SplitTable* splitTableList;

} DecisionTable;

/*
 * function table of Property
 */
Property* newProperty(Object*, Property*, int*);
int delProperty(Property*);

int getPropertyLength(Property*);
int getProptertySize(Property*);
int getPropertyValue(Property*);

void dbgProperty(Property*);
void dbgPropertyList(Property*);

/*
 * function table of Object
 */
Object* newObject(DecisionTable*, Object*, char*);
int delObject(Object*);

Property* getObjectProperty(Object*, int);
int getObjectLength(Object*);
int getObjectSize(Object*);
Object* compareObject(Object*, Object*);

void dbgObject(Object*);
void dbgObjectList(Object*);

/*
 * function table of ObjectWrapper
 */
ObjectWrapper* newObjectWrapper(ObjectWrapper*, Object*, int*);
int delObjectWrapper(ObjectWrapper*);

int getObjectWrapperLength(ObjectWrapper*);
int getObjectWrapperSize(ObjectWrapper*);
Object* findObject(ObjectWrapper*, Object*);

void dbgObjectWrapper(ObjectWrapper*);
void dbgObjectWrapperList(ObjectWrapper*);

/*
 * function table of AttributeNode
 */
AttributeNode* newAttributeNode(Attribute*, AttributeNode*, char*);
int delAttributeNode(AttributeNode*);

int getAttributeNodeLength(AttributeNode*);
int getAttributeNodeSize(AttributeNode*);

void dbgAttributeNode(AttributeNode*);
void dbgAttributeNodeList(AttributeNode*);

/*
 * function table of Attribute
 */
Attribute* newAttribute(DecisionTable*, Attribute*, char*);
int delAttribute(Attribute*);

int getAttributeLength(Attribute*);
int getAttributeSize(Attribute*);

void dbgAttribute(Attribute*);
void dbgAttributeList(Attribute*);

/*
 * function table of SplitTableCell
 */
SplitTableCell* newSplitTableCell(SplitTable*, SplitTableCell*, AttributeNode*, AttributeNode*);
int delSplitTableCell(SplitTableCell*);

int getSplitTableCellLength(SplitTableCell*);
int getSplitTableCellSize(SplitTableCell*);

void dbgSplitTableCell(SplitTableCell*);
void dbgSplitTableCellList(SplitTableCell*);

/* 
 * function table of SplitTable
 */
SplitTable* newSplitTable(DecisionTable*, SplitTable*, Attribute*);
int delSplitTable(SplitTable*);

SplitTableCell* getSplitTableCell(SplitTable*, int, int);
int getSplitTableLength(SplitTable*);
int getSplitTableSize(SplitTable*);
int getSplitTableHeight(SplitTable*);
int getSplitTableWidth(SplitTable*);

float getGiniIndex(SplitTable*, int);
float getGiniSplit(SplitTable*);

void dbgSplitTable(SplitTable*);
void dbgSplitTableList(SplitTable*);

/*
 * function table of DecisionTable
 */
DecisionTable* newDecisionTable(DecisionTable*, FILE*);
int delDecisionTable(DecisionTable*);

Attribute* addAttribute(DecisionTable*, Attribute*, char*);
Attribute* getClassAttribute(DecisionTable*);
Object* addObject(DecisionTable*, Object*, char*);
SplitTable* generateSplitTable(DecisionTable*);
Attribute* splitAttributeNode(DecisionTable*, Attribute*);
void dbgDecisionTable(DecisionTable*);
