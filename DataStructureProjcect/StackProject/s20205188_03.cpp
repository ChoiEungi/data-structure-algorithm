#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
ifstream inputfile; // ifstream: used to read from files
ofstream outputfile; // ofstream: used to create files and write on files

template <typename E>
class ArrayStack {
    enum { DEF_CAPACITY = 100 };		// default stack capacity
public:
    ArrayStack(int cap = DEF_CAPACITY);		// constructor from capacity
    int size() const;				// number of items in the stack
    bool empty() const;				// is the stack empty?
    const E& top() const throw(std::out_of_range);	// get the top element
    void push(const E& e) throw(std::out_of_range);	// push element onto stack
    void pop() throw(std::out_of_range);		// pop the stack
    // ...housekeeping functions omitted
private:	// member data
    E* S;					// array of stack elements
    int capacity;				// stack capacity
    int t;					// index of the top of the stack
};

template <typename E>
ArrayStack<E>::ArrayStack(int cap)
        : S(new E[cap]), capacity(cap), t(-1) { }       // constructor from capacity

template <typename E> int ArrayStack<E>::size() const
{ return (t + 1); }                             // number of items in the stack

template <typename E> bool ArrayStack<E>::empty() const
{return (t < 0); }                             // is the stack empty?

template <typename E>                           // return top of stack
const E& ArrayStack<E>::top() const throw(std::out_of_range) {
    try {
        if (empty()) {
            throw std::out_of_range("Top of empty stack");
        }
    } catch (std::out_of_range &e) {
    }
    return S[t];
}

template <typename E>                           // push element onto the stack
void ArrayStack<E>::push(const E& e) throw(std::out_of_range) {
    if (size() == capacity) throw std::out_of_range("Push to full stack");
    S[++t] = e;
}

template <typename E>                           // pop the stack
void ArrayStack<E>::pop() throw(std::out_of_range) {
    if (empty()) throw std::out_of_range("Pop from empty stack");
    --t;
}

int popIntValue(ArrayStack<int> &stack){ //return the int value and remove the value in stack to reduce the code. The stack type is int.
    int value = stack.top();
    stack.pop();
    return value;
}

char popCharValue(ArrayStack<char> &stack){ //return the char value and remove the value in stack to reduce the code. the stack type is char
    char value = stack.top();
    stack.pop();
    return value;
}

int calculate(int a, int b, char operater){ //calculate the number a, b. return the int type because all value is int value
    if(operater=='+') {return a+b;}
    else if(operater=='-') {return a-b;}
    else if(operater=='/') {return a/b;}
    else if(operater=='*') {return a*b;}
}

//give the priority on operater.
int operaterWeight(char operater){
    int weight = 0;
    if(operater=='+'||operater=='-') {weight=1;}
    else if(operater=='*'||operater=='/') {weight=2;}
    else if(operater=='('||operater==')') {weight=3;}
    return weight;
}

// if operater prior of stack in top is bigger than input, return true.
bool checkPrior(char first_op, char second_op){ return (operaterWeight(first_op)<=operaterWeight(second_op)) ;}


void calculator(std::stringstream &ss){
    ArrayStack<int> operand;    // A = [ ], size = 0
    ArrayStack<char> operater;
    int n;
    int first_num, second_num, third_num;
    char first_oper, second_oper;
    string token;
    while (getline(ss, token, ' ')) {
        if (token.length() > 1 || (token.at(0) >= '0' && token.at(0) <= '9')) { // if input is number, then put the number into operand stack
            istringstream isNum(token);
            isNum >> n; // string to int
            operand.push(n);
        } else { //put the operater stack but, when bigger priority operater will be put, then calculate the value in stack.
            if ((checkPrior(token.at(0), operater.top()) && operater.top() != '(') && !operater.empty()) {
                if (operand.top() == 0 && operater.top() == '/') {
                    operand.pop();
                    if (operand.top() >= 0) {
                        if (!operater.empty()&&operater.top()=='-'){
                            outputfile << "-INF" << endl;
                        }
                        else {outputfile << "INF" << endl;}
                    }
                    else outputfile << "-INF" << endl;
                    return ;
                }
                operand.push(calculate(popIntValue(operand), popIntValue(operand), popCharValue(operater)));
                operater.push(token.at(0));
            } else {
                operater.push(token.at(0));
            }
        }


        //remove ( ). for example, 3 + ( 4 * 2 + 3 ) -> 3 + 11 i.e. put '11'(calculation result of value in bracket) into operand
        if (token.at(0) == ')') {
            operater.pop(); // remove ')'
            while (true) { // calculate all of value in bracket
                if (operater.top() == '(') {
                    operater.pop(); // remove '('
                    break;
                }
                first_num = popIntValue(operand); //pop the first value
                first_oper = popCharValue(operater); // pop the first operater

                if (first_num == 0 && first_oper == '/') {
                    second_num = operand.top();
                    if (second_num >= 0) {
                        if (!operater.empty()&&operater.top()=='-'){
                            outputfile << "-INF" << endl; // if '-' operater is in front of 'positive Integer/0', return the -INF
                        }
                        else{outputfile << "INF" << endl;} // if '+' operater or is in front of 'positive Integer/0' or operater is empty, return the INF
                    }
                    else {
                        if (!operater.empty()&&operater.top()=='-'){
                            outputfile << "INF" << endl; // if '-' operater is in front of 'negative Integer/0', return the INF
                        }
                        else{outputfile << "-INF" << endl;} // if '+' operater or is in front of 'negative Integer/0' or operater is empty, return the -INF
                    }
                    return ;
                }
                /* if second operater priority is bigger than first one, then calculate second one earlier.
                 * for example in '3 * 5 + 2', first operater is '+' and second one is '*' we need to calculate * first. so we change equation to '15 + 2' */
                if (checkPrior(first_oper, operater.top()) && operater.top() != '(') {
                    second_num = popIntValue(operand);
                    third_num = popIntValue(operand);
                    second_oper = popCharValue(operater);
                    operand.push(calculate(third_num, second_num, second_oper));

                    operand.push(first_num);
                    operater.push(first_oper);
                }
                else {//if first operater priority is bigger than second one, then just calculate.
                    second_num = popIntValue(operand);
                    operand.push(calculate(second_num, first_num, first_oper));
                }

            }


        }
    }

    while (operand.size() != 1) { //pop the operand and operater until operand size is 1.(this value is the calculation value of given equation.)
        first_num = popIntValue(operand); //pop the first value
        first_oper = popCharValue(operater); // pop the first operater

        if (first_oper == '(') {
            outputfile << "INVALID" << endl; // if the ( is choosen in last calculation. End the function because we removed the pair of bracket previous while loop.
            return ; // if INVALID, end the function
        }

        if (first_num == 0 && first_oper == '/') {
            second_num = operand.top();
            if (second_num >= 0) {
                if (!operater.empty()&&operater.top()=='-'){
                    outputfile << "-INF" << endl; // if '-' operater is in front of 'positive Integer/0', return the -INF
                }
                else{outputfile << "INF" << endl;} // if '+' operater or is in front of 'positive Integer/0' or operater is empty, return the INF
            }
            else {
                if (!operater.empty()&&operater.top()=='-'){
                    outputfile << "INF" << endl; // if '-' operater is in front of 'negative Integer/0', return the INF
                }
                else{outputfile << "-INF" << endl;} // if '+' operater or is in front of 'negative Integer/0' or operater is empty, return the -INF
            }
            return ;
        }

        /* if second operater priority is bigger than first one, then calculate second one earlier.
         * for example in '3 * 5 + 2', first operater is '+' and second one is '*' we need to calculate * first. so we change equation to '15 + 2' */
        if (checkPrior(first_oper, operater.top()) && operater.top() != '(') {
            second_num = popIntValue(operand);
            third_num = popIntValue(operand);
            second_oper = popCharValue(operater);
            operand.push(calculate(third_num, second_num, second_oper));

            operand.push(first_num); // second one and third one is calculated, but first one is not calculated. so we put back first one and operater
            operater.push(first_oper);
        } else {
            second_num = popIntValue(operand); // if first operater priority is bigger than second one, then just calculate.
            operand.push(calculate(second_num, first_num, first_oper));
        }

    }

    if (operater.top() == '(') { // if '(' in floor of stack, return the INVALID.
        outputfile << "INVALID" << endl;
        return ;
    }
    outputfile << operand.top() <<endl; // return the calculation value of give equation.
}

int main(int argc, char* argv[]){ // File I/O

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
            stringstream ss(line); // string tokenizer
            calculator(ss); //calculator function.
        }
    }
    outputfile.close();
    return 0;

}
