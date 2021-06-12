#include <iostream>
#include <stdexcept> // for std::out_of_range
using namespace std;

template <typename E>
class ArrayList{
public:
    ArrayList(int maxEnt = 10);
    ~ArrayList();
    void add (const E& e);
    E remove(int i) throw(std::out_of_range);
    E get(int i);

private:
    int capacity; // maximum number of arrayList
    int numElement; // actual number of arrayList
    E* arr; // arrayList of type
};

//constructor
template<typename E> ArrayList<E>::ArrayList(int maxEnt) {
    capacity = maxEnt;
    arr = new E[capacity];
    numElement = 0;
}

//destructore
template<typename E> ArrayList<E>::~ArrayList<E>() {
    delete[] arr;
}

template<typename E> void ArrayList<E>::add(const E &e) {
    int i = numElement-1 ; // i is last element index of arrayList
    if (numElement == capacity){ // if full
        if (e <= arr[capacity-1]){ // input element is smaller than min
            return; // return the func
        }
    } else numElement++; // if not full, one more entry

    // increase size when inserting
    while ( i>=0 && e > arr[i]){
        arr[i+1] = arr[i]; // shift right if smaller
        i-- ;// go to left
    }
    arr[i+1] = e; // put the input in the arrayList
}

template<typename E> E ArrayList<E>::remove(int i) throw(std::out_of_range) {
    try {
        if ( (i<0) || (i >= numElement)){
            throw std::out_of_range("Idx out of range");
        }
    }
    catch (std::out_of_range &e) {
        cout<< e.what() << endl ; // print error element
    }
    E e = arr[i];
    for (int j= i+1; j<numElement;j++){
        arr[j-1]=arr[j]; //shift entries left
        numElement--; // go left
        return e; // return removed element
    }

}

template<typename E> E ArrayList<E>::get(int i) {return arr[i];}

int main(){
    ArrayList<double> doubleArrayList;
    ArrayList<int> intArrayList;
    ArrayList<char> charArrayList;
}
// c++ string arrlist 만드려면 object로
