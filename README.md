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

> A tree is an abstract model of a hierarchical structure. A tree consists of nodes with a parent-child relation.

**Main method**

- p.left(), p.right(), p.parent() :Nested position class 
- size(), empty(), root() 
- positions() : return position of node
- addroot(), expandExternal() ,removeExternal()

[Code(C++)](/BinaryTree/BinaryTree.cpp)





## Linked Priority Queue

> an abstract data type for storing a collection of prioritized elements that supports arbitrary element insertion but supports removal of elements in order of priority.

**Main method**

- entry : (key, value) key indicates priority

- size(), empty() : O(1) 

  |       method       | unsorted list | sorted list |
  | :----------------: | :-----------: | :---------: |
  |      insert()      |     O(1)      |    O(n)     |
  | min(), removeMin() |     O(n)      |    O(1)     |

- unsorted list means no sorting in insertion to priority queue(use selection sort in removing), sorted list means sorting in insertion(insertion sort).

[Code(C++)](/ListPriorityQueue/ListPriorityQueue.cpp)



## Heaps

> Priority Queue that implemented by trees.

- Heap-Order: key(v) >= key(parent(v)) (v is node)
- Condition is complete binary tree. (max num of nodes 2^i in i level and must insert from left to right)

**Main method**

- entry : (key, value) key indicates priority
- space : O(n)
- insert(), removeMin(): O(log n)
- size(), empty(), min() : O(1) 



## Maps

> Explanation



**Main methods**

- key()
- value()
- setKey(k)
- setValue(v)
- find(k) : return iterator (entry를 access할 수 있는 인자), O(n)
- put(k, v) : O(n)
- erase() : O(n)
- begin() , end() : 
- size(), empty() :



## Searching Trees

> 



## Sorting

> 



