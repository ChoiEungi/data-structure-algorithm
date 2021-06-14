# ec2202_2021Spring_PA02

## File list
Example: readme s20205188_02.cpp s20205188_02.out, input1.txt, input2.txt ,output1.txt,output2.txt

## Command Line Arguments
Example: ./s20205188_02.out input1.txt output1.txt
./s20205188_02.out input2.txt output2.txt




## Description of your code
### Class/struct

- To store user information. it is used to element of double linked list

```c++
class GameEntry {          // a game score entry
public:
    GameEntry(const string& n="", int s=0, float k=0); // constructor
    string getName() const;          // get player name
    int getStudentId() const;        // get player id
    float getScore() const;             // get player score
private:
    string name;            // student's name
    int studentId;           // student's ID
    float score;               //student's score
};

GameEntry::GameEntry(const string& n, int s,float k)   // constructor
        : name(n), studentId(s),score(k) { } 
string GameEntry::getName() const { return name; }
float GameEntry::getScore() const { return score; }
int GameEntry::getStudentId() const { return studentId; }
```



- Double linked list node it have the element and address value. we used the overriding constructor to make node.

```c++
struct DNode {
    GameEntry data;
    DNode* next, * prev;
    DNode() { //constructor
        next=prev=NULL;
        data;
    }
    DNode(GameEntry& i, DNode* ptr) //add the node by using overriding constructor
    {
        data = i;
        prev = ptr;
        next = ptr->next;
        next->prev= prev->next = this;
          
    }
    void selfDelete() { //destructor
        prev->next = next;
        next->prev = prev;
        delete this;
        
        
    }
};
```



 ### Function 

```c++
struct DLinkedList {
    DNode* head;
    DNode* tail;
    int count;
    ofstream outfile;
    DLinkedList() { // DLinkedList constructor
        
        head = new DNode();
        tail = new DNode();
        head->next = tail; //connect head and tail
        tail->prev = head;
    }
    ~DLinkedList() {
        while (head->next != tail)
            head->next->selfDelete();
        delete head;
        delete tail;      
        
    }
    void Add(GameEntry& a) { //add the node order by gpa desc
        float player_score = a.getScore();
        int player_student_id = a.getStudentId();
        bool flag =false; //to prevent inserting two same value
        DNode* tmp = head->next;
        while (tmp != tail) {
            GameEntry& compare = tmp->data;
            if (player_score - compare.getScore()>0) {
                new DNode(a, tmp->prev);
                flag = true;
                break;
            }

            else if(player_score==compare.getScore()&&player_student_id<compare.getStudentId()){
                new DNode(a,tmp->prev); // if the gpa is same, then add the node order by student_id asc
                flag = true;
                break;
            }

            else  {tmp=tmp->next;} // if the gpa of node is smaller than compare node, then the address of node change to the adress of ddl next node
        }

        if (tmp == tail && flag ==false)  {new DNode(a, tail->prev);}

    }
    void firstAdd(GameEntry& i) { 
        new DNode(i, head); // at first we need to add the head node
    }

    void Remove(int inputId) { 
        DNode* tmp = head->next;
        while (tmp != tail) {
            GameEntry& i2 = tmp->data;
            if (i2.getStudentId() == inputId) { //if student id is same with input_id then remove the node
                tmp->selfDelete();
                break;
            }
            else { tmp = tmp->next; } //if id of the node don't correct, then change the address to next node in ddl.
        }
    }

    void Print(DLinkedList* DLL) { //print highest 5 the node
        DNode* tmp = head->next;
        for (int i = 1; i <= 5; i++) {
            GameEntry entry = tmp->data;
            string student_name = entry.getName();
            float student_score = entry.getScore();
            int studentId = entry.getStudentId();
            outputfile << i<< '\t' << studentId<<'\t'<< student_name <<'\t'<<student_score<< endl;
            if(tmp->next!=tail) tmp = tmp->next;
          
        }
        outputfile<<'\n' ;
    }
};
```



### main function

- file I/O

```c++
int main (int argc, char* argv[]){
    DLinkedList* ddl = new DLinkedList;
    if(argc < 3) {
        outputfile <<"Usage: " << argv[0] << "inputfile output_file" <<endl;
    }
    inputfile.open(argv[1]);
    if(inputfile.fail())
        outputfile << "Cannot open inpufile" <<endl;

    outputfile.open(argv[2]);
    if(outputfile.fail())
        outputfile << "Cannot open outputfile" << endl;
    


    if(inputfile.is_open()) {
        string line;
        bool first_check = false;
        while (getline(inputfile, line)){
            GameEntry line_info;
            string token;
            stringstream ss(line); // string tokenizer
            int i =0;
            string command_token;
            string student_name;
            int student_id;
            float gpa;
            while (getline(ss, token, '\t')) {
                

                if (i==0){
                    command_token =token;
                      
                }
                else if(i==1){
                    student_name = token;
                                        
                }
                else if(i==2){
                    istringstream isgpa(token);
                    isgpa>>gpa;
                    
                }
                i++;
             }
             if (command_token.at(0) >='0' && command_token.at(0)<='9' && first_check==false) { //first line
                    istringstream isid(command_token);
                    isid >> student_id;
       
                    GameEntry line_info(student_name,student_id,gpa);
                    ddl->firstAdd(line_info);
                    first_check=true;
             }
             else if (command_token.at(0) >='0' && command_token.at(0)<='9' && first_check==true) { //second line and add line
                    istringstream isid(command_token);
                    isid >> student_id;
                    GameEntry line_info(student_name,student_id,gpa);
                    ddl->Add(line_info);
             }       
             else if(command_token.at(0)=='r'){ //remove line
                istringstream isid (student_name);
                isid >> student_id;
                ddl->Remove(student_id);
             }
 
             else if(command_token.at(0)=='p'){ //print line
                 ddl->Print(ddl);
             }
  

        }

    }
    inputfile.close();
    outputfile.close();
    return 0;
}
```

### Exceptions 

Add, remove function Time Complexity = O(n) n is length of double linked list.

So time complexity is O(nm) where m is number of txt file line except print.



### Limitations

- Late due to file I/O (segement error, core dumped) but I could leran that flow of coding and patient is important.
- did not use class in making node and DLinkedList. If I use class, I could help to understand OOP in C++.
- I learned that we need to access pointer carefully in Linux. If we access the address of null pointer, then it cause segement error. 
