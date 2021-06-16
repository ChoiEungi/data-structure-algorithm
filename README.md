# Data Structure (C++ / Java / Python )

------

## Contents





## ArrayList

>  A data structure consisting of a collection of elements (values or variables), each identified by at least one array index or key. 



### Main method

- space: O(n)
- at(i), set(i, o), size(), empty() :  O(1)
- insert : worst : O(n), 삽입될 때 size를 늘림, 

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

> A double linked list is a concrete data structure consisting of a sequence of nodes. Each node stores element and link to the next node and previous node.

**Main method** 

- addFront, addBack, add, removeFront, removeBack, remove() : O(1)
- front(), back(), empty() : O(1)
- `DNode* header` , `Dnode* trailer` : private pointer 

[Code(C++)](/DLinkedList/DLinkedList.cpp)



## Stack

> ADT stores arbitrary object. Insertions and deletions follow the last-in first-out(LIFO) scheme.

### Main method

- space() : O(n)
- size(), top(), empty(), push(), pop() : O(1)
- private variable: capacity, Element,  t (index of top of the stack)

[Code(C++)](/ArrayStack/ArrayStack.cpp)



## Queue

> ADT stores arbitrary object. Insertions and deletions follow the first-in first-out (FIFO) scheme.



## Tree





## Linked Priority Queue

> an abstract data type for storing a collection of prioritized elements that supports arbitrary element insertion but supports removal of elements in order of priority.

**Main method**

- size(), empty() : O(1)

  |       method       | unsorted list | sorted list |
  | :----------------: | :-----------: | :---------: |
  |      insert()      |     O(1)      |    O(n)     |
  | min(), removeMin() |     O(n)      |    O(1)     |

- unsorted list means no sorting in insertion to priority queue, sorted list means sorting in insertion.

[Code(C++)](/ListPriorityQueue/ListPriorityQueue.cpp)

## Heaps





## Hash Tables





## Searching Trees





## Sorting





