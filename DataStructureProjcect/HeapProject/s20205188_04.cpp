#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;
ifstream inputfile; // ifstream: used to read from files
ofstream outputfile; // ofstream: used to create files and write on files

class GameEntry {				// a game score entry
public:
    GameEntry(const string& n="", int s=0, float k=0.0);	// constructor
    string getName() const;			// get player name
    int getStudentId() const;			// get player id
    float getScore() const;             // get player score
private:
    string name;				// student's name
    int studentId;			    // student's ID
    float score;               //student's score
};

GameEntry::GameEntry(const string& n, int s,float k)	// constructor
        : name(n), studentId(s),score(k) { }
string GameEntry::getName() const { return name; }
float GameEntry::getScore() const { return score; }
int GameEntry::getStudentId() const { return studentId; }


// This part is important in this code
class Comp{
public:
    bool operator()(const GameEntry& p, const GameEntry& q)
    {
        if (p.getScore()==q.getScore()){return p.getStudentId()<q.getStudentId();} //if gpa is same, then sorting by increasing order by student id
        return (p.getScore() > q.getScore()); // if gpa is not same, then sorting by decreasing order by GPA.
    }
};

// Vector based complete binary tree
template <typename E>
class VectorCompleteTree {
private:
    std::vector<E> V;		// Tree constents
public:
    typedef typename std::vector<E>::iterator Position; // Position in the tree
protected:
    Position pos(int i) {		// map index to a position
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
    Position root() { return pos(1); }				 // Get the root
    Position last() { return pos(size()); }			 // Get the last element
    void addLast(const E& e) { V.push_back(e); }			 // Add element to the end
    void removeLast() { V.pop_back(); }				 // Remove last element
    void swap(const Position& p, const Position& q) {		 // Swap two elementscV
        E e = *q;
        *q = *p;
        *p = e;
    }
};

template <typename E, typename C>
class HeapPriorityQueue {
public:
    HeapPriorityQueue() : T(VectorCompleteTree<E>()) {};	 // Default constructor
public:
    int size() const;		// number of elements
    bool empty() const;		// is it empty?
    void insert (const E& e);	// insert element
    const E& min();		// minimum element
    void removeEntry();		// remove minimum
private:
    VectorCompleteTree<E> T;	// priority queue constents
    C isLess;			// less than comparator

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
    T.addLast(e);			// Add e to heap
    Position v = T.last();	// e's position
    while (!T.isRoot(v)) {
        Position u = T.parent(v);
        if (!isLess(*v, *u)) break;	// if v in order, we're done
        T.swap(v, u);		// ... else swap with parent
        v = u;
    }
}

template <typename E, typename C> // remove Entry value (I changed the source code from "removeMin" to "removeEntry" because I changed heap sort order by GPA and StudentID
void HeapPriorityQueue<E,C>::removeEntry() {
    if (size() == 1)		// if only one element
        T.removeLast();		// get rid of it
    else {
        Position u = T.root();	// Root position
        T.swap(u, T.last());	// swap last with root
        T.removeLast();		// remove the last one
        while (T.hasLeft(u)) {	// down-heap bubbling
            Position v = T.left(u);
            if (T.hasRight(u) && isLess(*(T.right(u)), *v))
                v = T.right(u);		// v is u's smaller child
            if (isLess(*v, *u)) {	// is u out of order?
                T.swap(u, v);		// swap it
                u = v;
            }
            else break;
        }
    }
}

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


