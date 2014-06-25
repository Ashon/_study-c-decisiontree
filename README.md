#DecisionTree
Decisiontree in C
##Abstract data types(ADTs) of decision tree generator.
<pre><code>ADT dependency
    +-> DecisionTree : decision tree
      |
      +---> intattributeLength : length of Attribute List (direct)
      +---> intobjectLength : length of Object List (direct)
      +---> AttributeattributeList : [single list]
      |   +---> intattributeLength : [DecisionTree->attributeLength]
      |   +---> charattributeName : Attribute name
      |   +---> inttype : Attribute type
      |   +---> intattributeNodeLength : length of Attribute's class.
      |   +---> AttributeNodeattributeNodeList : [single list]
      |   |   +---> intattributeNodeLength : 
      |   |   |                         [Attribute->attributeNodeLength]
      |   |   +---> charattributeNodeName : class name
      |   |   +---> intobjectWrapperLength : # of ObjectWrapper
      |   |   +---> ObjectWrapperobjectWrapperList :
      |   |   |   |                     [DecisionTree->ObjectList]
      |   |   |   +---> intobjectWrapperLength :
      |   |   |   |                     [Attribute->objectWrapperLength]
      |   |   |   +---> Objectobject : [DecisionTree->Object_List]
      |   |   |   |                belonging to [Attribute->AttributeNode]
      |   |   |   +---> ObjectWrapperlink : next ObjectWrapper List.
      |   |   +---> AttributeNodelink : next AttributeNode List.
      |   +---> Attributelink : next Attribute List.
      +---> ObjectobjectList : [single list]
      |   +---> intobjectLength : [DecisionTree->objectLength]
      |   +---> intpropertyLength : # of Property (direct)
      |   +---> PropertypropertyList : [single list]
      |   |   +---> intpropertyLength : [Object->propertyLength]
      |   |   +---> intvalue : Property value.
      |   |   +---> Propertylink : next Property List.
      |   +---> Objectlink : next Object List.
      +---> SplitTableList_SplitTable : [single list]
          +---> intsplitTableLength : [DecisionTree->splitTableLength]
          +---> intobjectLength
          +---> AttributeattributeColumn :
          |                     [DecisionTree->attributeList]
          +---> AttributeattributeRow :
          |                     [DecisionTree->attributeList]
          +---> intsplitTableCellLength :
          +---> SplitTableCellsplitTableCellList : 
          |   +---> intsplitTableCellLength :
          |   |             [SplitTable->splitTableCellLength]
          |   +---> intobjectWrapperLength :
          |   +---> ObjectWrapperobjectWrapperList :
          |   +---> SplitTableCelllink : next SplitTableCell List.
          +---> SplitTablelink : next splitTable List
</pre></code>

##Input File Example
<pre><code>\#
Home_Owner{No,Yes}
Marital_Status{Single,Married,Divorced}
Annual_Income{@}
Defaulted_Borrower@{No,Yes}
\#
1,0,125,0
0,1,100,0
0,0,70,0
1,1,120,0
0,2,95,1
0,1,60,0
1,2,220,0
0,0,85,1
0,1,75,0
0,0,90,1
</pre></code>
