# ec2202_2021Spring_PA04

## File list
Example: readme.md s20205188_04.cpp s20205188_04.out , input1.txt, output1.txt

## Command Line Arguments
compile: `g++ -o s20205188_04.out s20205188_04.cpp`

Example: `./s20205188_04.out input1.txt output1.txt`

## Description of your code
### 문제 접근

1. 힙 자료 구조형에서 Comp Class에서 연산자를 재정의 할 때, 문제에서 제시한 조건을 정의해줘 힙에서 insert 시 정렬될 때 GPA는 내림차순으로, Student_id에 대해서는 오름차순으로 정의했다. 자세한 과정은 코드에서 설명한다. 또한 heap에서 remove할 때 정렬 또한 Comp에서 정의한 연산자의 영향으로 remove를 해도 정렬될 떄 GPA는 내림차순으로, Student_id에 대해서는 오름차순으로 정의했다. 그렇기에 source code의 `removeMin()` method를 정해진 기준에서 Entry값을 제거하게 되므로 `removeEntry()`로 method name을 변경했다.
2. File I/O를 통해 input을 받은 후 heap에 모두 insert한다. 이 때 1에서 언급한 방식으로 정렬되고, input이 끝나면 heap이 빌 때 까지 print/remove한다. remove 시 정렬도 1에서 언급한 방식으로 정렬된다.



## Code

### GameEntry Class

- 문제에서 사용할 객체이다. 객체의 프로퍼티는 string, int, float이다.

```c++
class GameEntry {            // a game score entry
public:
    GameEntry(const string& n="", int s=0, float k=0.0);   // constructor
    string getName() const;          // get player name
    int getStudentId() const;        // get player id
    float getScore() const;             // get player score
private:
    string name;            // student's name
    int studentId;           // student's ID
    float score;               //student's score
};
GameEntry::GameEntry(const string& n, int s,float k)	// constructor
        : name(n), studentId(s),score(k) { }
string GameEntry::getName() const { return name; }
float GameEntry::getScore() const { return score; }
int GameEntry::getStudentId() const { return studentId; }

```



### Comp Class(가장 중요)

정렬의 기준을 GPA는 내림차순으로, Student id는 오름차순으로 진행했다. 만약 GPA가 같으면 Student_id로 오름차순으로 진행하므로 if문을 걸어 return을 하고 if문에 걸리지 않으면 GPA로 오름차순을 진행한다

```c++
// This part is important in this code
class Comp{
public:
    bool operator()(const GameEntry& p, const GameEntry& q)
    {
        if (p.getScore()==q.getScore()){return p.getStudentId()<q.getStudentId();} //if gpa is same, then sorting by increasing order by student id
        return (p.getScore() > q.getScore()); // if gpa is not same, then sorting by decreasing order by GPA.
    }
};
```



### Vector based Heap

- 힙 자료구조
- remove할 때 min값이 아니기에 `removeMin()`을 `removeEntry()`로 변경했다.

```c++
// Vector based complete binary tree
template <typename E>
class VectorCompleteTree {
private:
    std::vector<E> V;     // Tree constents
public:
    typedef typename std::vector<E>::iterator Position; // Position in the tree
protected:
    Position pos(int i) {     // map index to a position
        return V.begin() + i;
    }
    int idx(const Position& p) const { // map a position to index
        return p - V.begin();
    }
public:
    VectorCompleteTree() : V(1) {} // constructor
    int size() const { return V.size() - 1; } // Size of the tree
    Position left (const Position& p) { return pos(2*idx(p)); } // left position
    Position right (const Position& p) { return pos(2*idx(p)) + 1; } // right position
    Position parent (const Position& p) { return pos(idx(p) >> 1); } // parent position
    bool hasLeft ( const Position& p) const { return 2*idx(p) <= size(); } // Is there left?
    bool hasRight ( const Position& p) const { return 2*idx(p) + 1 <= size(); } // Is there right?
    bool isRoot ( const Position& p) const { return idx(p) == 1; } // Is root?
    Position root() { return pos(1); }           // Get the root
    Position last() { return pos(size()); }           // Get the last element
    void addLast(const E& e) { V.push_back(e); }          // Add element to the end
    void removeLast() { V.pop_back(); }              // Remove last element
    void swap(const Position& p, const Position& q) {      // Swap two elementscV
        E e = *q;
        *q = *p;
        *p = e;
    }
};

template <typename E, typename C>
class HeapPriorityQueue {
public:
    HeapPriorityQueue() : T(VectorCompleteTree<E>()) {};    // Default constructor
public:
    int size() const;     // number of elements
    bool empty() const;       // is it empty?
    void insert (const E& e);  // insert element
    const E& min();       // minimum element
    void removeEntry();       // remove minimum
private:
    VectorCompleteTree<E> T;   // priority queue constents
    C isLess;        // less than comparator

    typedef typename VectorCompleteTree<E>::Position Position;
};

template <typename E, typename C> // Number of elements
int HeapPriorityQueue<E,C>::size() const {
    return T.size();
}

template <typename E, typename C> // is it empty?
bool HeapPriorityQueue<E,C>::empty() const {
    return size() == 0;
}

template <typename E, typename C>
const E& HeapPriorityQueue<E,C>::min() {
    return *(T.root());
}

template <typename E, typename C>
void HeapPriorityQueue<E,C>::insert(const E& e) {
    T.addLast(e);        // Add e to heap
    Position v = T.last(); // e's position
    while (!T.isRoot(v)) {
        Position u = T.parent(v);
        if (!isLess(*v, *u)) break;    // if v in order, we're done
        T.swap(v, u);     // ... else swap with parent
        v = u;
    }
}

template <typename E, typename C> // remove Entry value (I changed the source code from "removeMin" to "removeEntry" because I changed heap sort order by GPA and StudentID
void HeapPriorityQueue<E,C>::removeEntry() {
    if (size() == 1)      // if only one element
        T.removeLast();       // get rid of it
    else {
        Position u = T.root(); // Root position
        T.swap(u, T.last());   // swap last with root
        T.removeLast();       // remove the last one
        while (T.hasLeft(u)) { // down-heap bubbling
            Position v = T.left(u);
            if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                v = T.right(u);       // v is u's smaller child
            if (isLess(*v, *u)) {  // is u out of order?
                T.swap(u, v);     // swap it
                u = v;
            }
            else break;
        }
    }
}
```



### main

- input token에서 student_id, student_name, gpa를 받는다. 이 때 token은 string값이므로 istringstream을 이용해 int, float값으로 변경한다. 이후 GameEntry instance를 힙에 넣어준다.insertion이 끝나면 heap이 빌 때 까지 print/remove를 한다.

```c++
int main(int argc, char* argv[]){ // File I/O
    HeapPriorityQueue<GameEntry, Comp> hpq;
    float gpa;
    if (argc < 3) {
        cout << "Usage: " << argv[0] << "inputfile output_file" << endl;
    }

    inputfile.open(argv[1]);
    if (inputfile.fail())
        cout << "Cannot open inpufile" << endl;

    outputfile.open(argv[2]);
    if (outputfile.fail())
        cout << "Cannot open outputfile" << endl;

    if (inputfile.is_open()) {
        string line;
        while (getline(inputfile, line)) {
            string token;
            stringstream ss(line); // string tokenizer
            string student_name; // input student_name from token
            int student_id; // input student_id from token
            int i = 0; // check where tab is. i.e. set i=0 is student_id, i=1 is name, i=2 is gpa.
            while (getline(ss, token, '\t')) {
                if (i == 0) {
                    istringstream isid(token); //change string type to int type
                    isid >> student_id;
                } else if (i == 1) {
                    student_name = token;  //input student name
                } else if (i == 2) {
                    istringstream isgpa(token); // change string type to float type
                    isgpa >> gpa;
                }
                i++;
            }
            hpq.insert(GameEntry(student_name, student_id, gpa)); // insert GameEntry object into heap
        }
    }
    // take out all heap value until heap is empty.
    while (!hpq.empty()){
        outputfile<<hpq.min().getStudentId()<<"\t"<<hpq.min().getName()<<"\t"<<hpq.min().getScore()<<endl;
        hpq.removeEntry(); //remove heap value
    }
    outputfile.close();
    return 0;

}
```



### Exception, Limitation

만약 line이 format에 맞지 않으면 오류가 발생한다. 