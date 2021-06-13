# Data Structure (C++ / Java / Python )

------

## Contents





## ArrayList

>  A data structure consisting of a collection of elements (values or variables), each identified by at least one array index or key. 



### Main method

- space: O(n)
- at(i) : A[i] , return index without removing, O(1)
- set(i, o) : A[i] = o , O(1)
- insert : worst : O(n), 삽입될 때 size를 늘림
- erase  : worst O(n)
- size : O(1)
- empty O(1)

[Code(C++)](/ArrayList/ArrayList.cpp)

## Linked List 

### Single Linked List 

> A singly linked list is a concrete data structure consisting of a sequence of nodes. Each node stores element and link to the next node 

- sequential access is slow because elements not in continuous memory locations.
- When you have to perform more search operation than that of insert or delete operation than it’s best to go ahead with an array list but in reverse case it’s always better to go ahead with linked list.

**Main method**

- search : O(n)
- insert, delete :O(1)

**Usage**

1. The time-sharing problem used by the scheduler during the scheduling of the processes in the Operating system.
2. *Image viewer* – Previous and next images are linked, hence can be accessed by the next and previous button.



### Double Linked List

**Main method** 

- addFront, addBack, add, removeFront, removeBack, remove() : O(1)
- front(), back(), empty() : O(1)
- `DNode* header` , `Dnode* trailer` : private pointer 

[Code(C++)](/DLinkedList/DLinkedList.cpp)