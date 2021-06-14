#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector> //to use vector (dynamic array)

using namespace std;

ifstream inputfile; // ifstream: used to read from files
ofstream outputfile; // ofstream: used to create files and write on files

void raiseDigit(vector<unsigned long long int>& num) {
    // Increase the number of digits to make each index in the array,
    // except for the first index, have only one digit.
    int size = num.size(); // to calculate the length of number
    for (int i = size-2; i >=0; i--)
    {
        num[i] += num[i + 1] / 10;
        num[i + 1] %= 10;

        // num[5] = 15 -> num[4] += 1 and num[5] = 5 (15%10=5)
    }
    //Remove the remaining zeros from the front.
    // ex) 0123 -> 123
    while (num.size() > 1 && num.back() == 0){
        num.pop_back();

    }
}

//Multiplication of each digit
vector<unsigned long long int> multiply(const vector<unsigned long long int>& a, const vector<int>& b){
    int a_size = a.size();
    int b_size = b.size();
    vector<unsigned long long int> c(a_size+b_size+1, 0); // initalize the number of a_size+b_size+1 element to 0

    for (int i =0; i < a_size; i++){
        for(int j=0; j<b_size; j++){
            c[i + j] += a[i] * b[j];
            // Declare an array "c" that has digits as an index and multiply them by digits.
            // ex) in 12*12 = 24+120 == 144 c[1]=100 c[2]=40 c[3]=4 sum(c) = 144
        }
    }
    raiseDigit(c); //change real number by using vector
    return c;
}

void calculate(string input_n, string input_k) {
    //string to int and put int in vector
    string string_n = input_n;     //input num
    string string_k = input_k;     // input num
    bool negative_flag = false; //check n<0 it could be negative
    bool reciprocal_flag = false; // check k<0, it could be reciprocal

    unsigned long long int n;
    int k;
    istringstream isa (string_k);
    isa >> k;
    // string to int (k)

    if (string_n=="0" && string_k=="0"){ //0^0=undefined
        outputfile << "undefined"<<endl;
        return ;
    }
    if (string_n=="0" && string_k!="0"){ // 0^k =0 (k!=0)
        outputfile << 0<<endl;
        return ;
    }

    if (string_n!="0" && string_k=="0"){ // One number of zero squared is 1.
        outputfile<<1<<endl;
        return ;
    }



    if (string_n.at(0)=='-' && k%2!=0){
        negative_flag = true; //check negative
    }

    if (string_n.at(0)=='-'){ //erase string '-'. we will handle only positive integer in code
        string_n.erase(0,1);
    }


    if (k<0){
        reciprocal_flag = true; //check reciprocal;
        k = -k;
    }

    int cnt = 0;
    if (string_n.at(string_n.size()-1)=='0'){ // end of the num is 0
        int temp = string_n.size()-1;
        while (true){
            if (string_n.at(temp)!='0'){
                string_n.erase(temp+1, string_n.size()-1);
                break;
            }
            cnt ++;
            temp --;
        }
    }
    cnt *= k;

    vector<string> num;
    num.push_back(string_n); //put string_n into array to calculate in while loop

    istringstream iss (string_n);
    iss >> n;
    // string to int (n)

    vector<unsigned long long int> n_value ; //put int_n into array to calculate integer number
    n_value.push_back(n);

    while(true){
        if (k==1){ // if,k==1 break
            break;
        }
        string a = num.back(); //for inital calculation

        vector<int> v;
        int p;

        //put string a into digit number
        //ex) "1234" --> v = {1,2,3,4}
        for (int i=0;i<a.size();i++){
            p = a.at(i)-'0';
            v.push_back(p);
        } //change string to int. each digit put into vector(dynamic array) v

        vector<unsigned long long int> val;
        a = ""; //initalize string a to update the previous value
        val = multiply(n_value,v);

        for(int i=0;i<val.size();i++){
            // int to string to print the result
            ostringstream convert;
            convert << val[i];
            a += convert.str();
            num.push_back(a);
        }
        k--;

    }
    if (negative_flag==true){ //if negative, add "-"
        outputfile << "-";
    }
    if (reciprocal_flag==true){ //if k<0, add "1/"
        outputfile << "1/";
    }
    outputfile << num.back(); //print the result

    if (cnt>0){
        for (int i=0;i<cnt;i++){
            outputfile << "0"; //if end value is 0 it would add as much as cnt.
        }
    }
    outputfile << "\n"; //change the line.
    return ;  // end the function

}

int main (int argc, char* argv[]){
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
        while (getline(inputfile, line)) {
            string token;
            stringstream ss(line); // string tokenizer
            string arr[2]; //arr[0] is n and arr[1] is k
            int i =0;
            while (getline(ss, token, '\t')) {
                arr[i] = token;
                i++;
            }

            calculate(arr[0],arr[1]) ; // write to the output file
        }

    }
    inputfile.close();
    outputfile.close();
    return 0;
}

// n<18,446,744,073,709,551,615(max value of unsigned long long int)
// limitation: if inital n^2 > 18,446,744,073,709,551,615, then we can't calculate becuase that value cannot save in value.
// max value of k is 3000~-3000. if abs(k)>3000, Program has been forced to exit due to overcalculation. we can get the value of 2^3000 :)

