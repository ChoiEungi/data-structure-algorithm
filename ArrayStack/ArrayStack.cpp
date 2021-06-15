#include <iostream>
#include <stdexcept> // for std::out_of_range


using namespace std;

template<typename E>
class ArrayStack{
    enum { DEF_CAPACITY = 100 }; //default stack capacity,
public:
    ArrayStack(int cap = DEF_CAPACITY); // constructor
    int size() const;   //check num of elements in stack
    bool empty() const; //check empty
    const E& top() throw(std::out_of_range); // get top element not return
    void push(const E& e) throw(std::out_of_range); // push the element
    void pop() throw(std::out_of_range); // pop the element
private:
    E* S; // need to know the granmmer.
    int capacity;
    int t;

};

template<typename E>
ArrayStack<E>::ArrayStack(int cap)
:S(new E[cap]), capacity(cap), t(-1) {}  //constructor

template <typename E> int ArrayStack<E>::size() const { return t+1 ;}

template <typename E> bool ArrayStack<E>::empty() const { return t<0;}

template <typename E> const E& ArrayStack<E>::top() {
    try {
        if(empty()){
            throw std::out_of_range("Top of empty Stack");
        }
    }catch (std::out_of_range &e){
        cout << e.what() << endl; // show error
    }
    return S[t];

}

template <typename E> void ArrayStack<E>::push(const E &e) {
    if (size()==capacity) throw std::out_of_range("Push to full stack");
    S[++t] = e;
}

template <typename E> void ArrayStack<E>::pop() {
    if(empty()) throw std::out_of_range("Empty Stack");
    --t;
}

int main(){
    ArrayStack<double> doubleStack;
    ArrayStack<string> stringStack;
    stringStack.push("hello");
    cout<<stringStack.top()<<endl;
    stringStack.pop();
    stringStack.top();



}
