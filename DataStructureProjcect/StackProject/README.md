# ec2202_2021Spring_PA03

## File list
readme s20205188_03.cpp s20205188_03.out, input.txt, output.txt

## Command Line Arguments

compile: g++ -o s20205188_03.out s20205188_03.cpp

./s20205188_03.out input1 output1

## Description of your code

### Overview of my code

1. 교수님께서 언급해주신 스택에 연산자를 우선 넣을 때, 스택에 있는 연산자보다 input의 연산자의 우선순위가 낮으면 stack에서 계산 작업을 한 후 input의 연산자를 스택에 넣었습니다.

2. 만약 ')' 가 input 값으로 들어오면 '('가 나올때까지 while 문을 돌려 전처리 작업으로 괄호를 제거했습니다. 

3. 이후 괄호가 없는 계산인 +, -, *, /만 남으므로 이를 연산합니다. 만약 '('가 남아있다면 INVALID를 출력합니다. 

4. 만약 5*2+5 와 같은 것들은 오른쪽에서 왼쪽으로 연산하면 틀린 값이 나옵니다. 

   4-1. 그렇기에 괄호가 없는 계산을 진행할 때 연산자와 숫자를  pop해 변수에 담고 stack의 top과 비교합니다. 만약 stack의 top에 있는 연산자의 우선순위가 높다면 또 다른 변수에 이를 pop한 후 숫자를 또 pop해 계산을 진행합니다. 이 때 결과값을 다시 stack에 담고 첫 번째에서 꺼낸 숫자와 연산자를 stack에 돌려놓습니다.

   4-2. 3 * 2 + 5 를 예로 들면, '5'와 '+' 를 각각 변수에 담으면  연산자 stack의 top값은 '*'이므로 우선순위가 더 높습니다. 그렇기에 '2' 와 '3'을 변수에 담고 계산을 진행해 6을 숫자를 담는 stack에 넣어줍니다. 이후 '5' 와 '+' 를 다시 스택에 넣어 6 + 5 꼴로 바꿉니다. 

   4-3. 우선 순위를 다룰 때 3 - 6 - 9 와 같은 것들은 3 - -3 = 6 이런 식으로 될 수 있습니다. 그렇기에 만약 + -, *, / 와 같이 우선순위가 같은 것들 또한 4-2의 방식으로 계산해 예외처리를 진행했습니다.

5.  마지막으로 숫자 stack의 top값을 출력해 결과를 도출했습니다.



### Stack Implement

```c++
template <typename E>
class ArrayStack {
    enum { DEF_CAPACITY = 100 };      // default stack capacity
public:
    ArrayStack(int cap = DEF_CAPACITY);       // constructor from capacity
    int size() const;           // number of items in the stack
    bool empty() const;             // is the stack empty?
    const E& top() const throw(std::out_of_range); // get the top element
    void push(const E& e) throw(std::out_of_range);    // push element onto stack
    void pop() throw(std::out_of_range);      // pop the stack
    // ...housekeeping functions omitted
private:   // member data
    E* S;              // array of stack elements
    int capacity;           // stack capacity
    int t;             // index of the top of the stack
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
```



### Pop value function

- 코드 길이를 줄이기 위해서 위에서 구현한 스택에서 pop을 할 때 void형이지만  value를 return 하면서 pop하기 위해 별도의 함수를 구현했다. value라는 변수에 top 값을 담고 pop 후 value를 리턴한다. operand는 숫자를 pop하니 int형으로, operater은 char 타입을 리턴하니 char 타입을 리턴하도록 설정했다,

```c++
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
```



### Calculate

- 두 숫자 a, b가 주어지고 연산자가 주어질 때 그대로 계산을 진행하는 함수. 모든 값이 정수이므로 int 형을 리턴한다.

```c++
int calculate(int a, int b, char operater){ //calculate the number a, b. return the int type because all value is int value
    if(operater=='+') {return a+b;}
    else if(operater=='-') {return a-b;}
    else if(operater=='/') {return a/b;}
    else if(operater=='*') {return a*b;}
}
```



### Operater Weight & checkPrior

- 우선 순위를 괄호 > 곱셈, 나눗셈, 덧셈 뺄셈 순으로 두었다. 괄호를 가장 높게 둔 것은 stack에 input 될 때 input의 우선순위가 stack보다 낮으면 stack을 먼저 처리하는데 만약 괄호가 들어가면 연산을 막아 괄호를 우선적으로 연산할 수 있도록 하기 위함이다. 
- 4-3에서 언급했듯 '3-5-7'과 같은 연산을 위해 같은 우선순위를 가져도 second operation의 우선 순위를 높게 두어 연산을 앞의 연산(3-5)를 먼저 진행하게 했습니다.

```c++
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
```



### Calculator

- 계산을 진행하는 함수. 
- 자세한 과정은 overview에서 보실 수 있고 이는 그를 구현한 것입니다. 주석에서도 자세한 과정을 소개합니다.
- 다시 소개하면, stack에 token을 숫자와 연사자로 나눠 넣습니다.  넣을 때 input되는 연산자가 stack의 top에 있는 연산자보다 우선순위가 낮다면 stack의 top에 있는 연산자를 연산하고 input을 진행합니다. 만약 ')'가 들어오면, operater을 계속 pop해 '('가 나올때까지 연산을 진행해 stack에 넣을 때 괄호가 남지 않도록 합니다. 마지막으로 괄호를 모두 제거하고 input이 끝나면, 남은 연산을 진행합니다. 자세한 예외는 overview와 exception에서 다뤘습니다.
```c++
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
                operand.push(calculate(popIntValue(operand), popIntValue(operand), popCharValue(operater))); // if input priority is smaller than stack, calculate in stack
                operater.push(token.at(0)); //and then input the operater
            } else {
                operater.push(token.at(0)); //if input priority is bigger than stack, just put operater into stack.
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
```



### main 

- 파일 입출력을 위해 사용된 함수.  실질적으로 계산은 calculator function에서 진행된다. 

```c++
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
```



### Exception

- 3+4-5-4*10 과 같은 것들도 계산할 수 있도록 했습니다. 자세한 구현 및 처리 과정은 위의 Overview에서 볼 수 있습니다.

- 숫자를 넣는 코드에서  `if (token.length() > 1 || (token.at(0) >= '0' && token.at(0) <= '9')) { // if input is number, then put the number into operand stack` 에서 볼 수 있듯 음수 ''-5" 와 같은 것은 토큰의 길이가 1보다 반드시 크므로 음수도 정상적으로 받을 수 있도록 처리했습니다.



### Limitation

- 중복되는 코드를 더 줄일 수 있을 것 같다. 괄호 안을 처리하는 코드와 마지막에 괄호를 제거하고 처리하는 코드의 중복되는 부분이 많다. 코드를 짤 때 중복을 줄이는 것은 매우 중요한데, 중복을 줄이는 함수를 구현해 리펙토링을 하면 더 깔끔한 코드가 나올 수 있을 것 같다.
