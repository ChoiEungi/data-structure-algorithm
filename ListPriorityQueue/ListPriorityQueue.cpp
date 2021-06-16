
#include <iostream>
#include <list> // STL to use in Priority Queeue

using namespace std;

struct Point2d{ // element struct
    double X;
    double Y;
    Point2d(double a, double b) : X(a), Y(b) {}
    double getX() const {return X;} // const mean: can't change the variable in function except mutable
    double getY() const {return Y;}
};

class LeftRight{
public:
    // override operator to define priority. This is used to comparator
    bool operator ()(const Point2d& a, Point2d& b){
        if (a.getX()==b.getX()) {return a.getY()<b.getY();}
        return a.getX()<b.getX();
    }

};

// sorted Linked Priority Queue
template <typename E, typename C> // E is element type and C is comparator type
class ListPriorityQueue{
public:
    int size() const; // check size
    bool empty() const; // check empty
    void insert(const E& e); // insert e into queue while keeping it sorted
    const E& min() const; // return a min value not removing
    void removeMin(); // remove min value

private:
    list<E> L;
    C isLess; // comparator object which defines a total order relation.
};

template <typename E, typename C>
int ListPriorityQueue<E,C>::size() const {
    return L.size();
}

template <typename E, typename C>
bool ListPriorityQueue<E,C>::empty() const {
    return L.empty();
}

template <typename E, typename C>
void ListPriorityQueue<E,C>::insert(const E& e) {
    typename list<E>::iterator p; // it opertate like index.
    p = L.begin();
    while (p != L.end() && !isLess(e, *p)) // until search e.value>p.value and p or p is end. if p is end value then break.
        p++;
    L.insert(p, e);
}

template <typename E, typename C>
const E& ListPriorityQueue<E,C>::min() const {
    return L.front();
}

template <typename E, typename C>
void ListPriorityQueue<E,C>::removeMin() {
    L.pop_front();
}

int main(){
    ListPriorityQueue<Point2d, LeftRight> pq;
    pq.insert(Point2d(2.3,1.2));
    pq.insert(Point2d(2.3,1.3));
    pq.insert(Point2d(2.3,1.0));

    cout<<pq.min().getY();
}
