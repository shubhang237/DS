#include<iostream>
#include<string.h>
using namespace std;

template <class T>
struct Node
{
   Node<T> *next;
   T data;
};

template <class T>
struct stackLL
{
   Node<T> *top;
   int size;
   stackLL();
   void push(T);
   T pop();
   T peek();
   bool isEmpty();
   void printStack();
};

template <class T>
stackLL<T>::stackLL(){
    top =  NULL;
    size = 0;
}

template <class T>
void stackLL<T>::push(T x){
    if(top == NULL){
        Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
        newNode->data = x;
        top = newNode;
        size++;
        return;
    }

    Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
    newNode->data = x;
    newNode->next = top;
    top = newNode;
    size++;
    return; 
}

template <class T>
T stackLL<T>::pop(){
    if(top == NULL){
        cout<<"Stack Underflow"<<"\n";
        return -1;
    }

    Node<T>*t = top;
    top = top->next;
    T temp = t->data;
    size--;
    free(t);
    return temp;
}

template <class T>
T stackLL<T>::peek(){
    if(top == NULL){
        cout<<"No Element Present"<<"\n";
        return -1;
    }
    T temp = top->data;
    return temp;
}

template <class T>
bool stackLL<T>::isEmpty()
{
    return size == 0;
}

template <class T>
void stackLL<T>::printStack(){
    Node<T>*temp = top;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

int Prec(char ch){

    switch(ch)
    {
        case '^': return 5;
        case '/': return 4;
        case '*': return 3;
        case '+': return 2;
        case '-': return 1;
    }
}

int getPrecedence(char a,char b){
     
    int precA = Prec(a);
    int precB = Prec(b);
    if(precA > precB){
        return 1;
    }
    else if(precA < precB){
        return -1;
    }
    else 
        return 0;
         
}

string infixTopostfix(string str){
    string res = "";
    stackLL<char> *st = new stackLL<char>();
    for(int i=0;i<str.length();i++){
        if(((str.at(i)-'a') >= 0 && (str.at(i)-'a') < 26) || ((str.at(i)-'A') >= 0 && (str.at(i)-'A') < 26)){
             //cout<<"1"<<"\n";
             res = res + str.at(i);
             //cout<<res<<"\n";
        }  
        else if(str.at(i) == '^' || str.at(i) == '/' || str.at(i) == '*' || str.at(i) == '+' || str.at(i) == '-' || str.at(i) == ')' || str.at(i) == '(' ){
            if(st->isEmpty() || str.at(i) == '('){
                //cout<<"2"<<"\n";
                st->push(str.at(i));
               // st->printStack();
            }
            else if(str.at(i) == ')')
            {
                    //cout<<"3"<<"\n";
                    while(!st->isEmpty() && st->peek() != '('){
                        res = res + st->pop();
                      //  cout<<res<<"\n";
                    }
                    st->pop();
                    //st->printStack();
            }
            else 
            {
                if(getPrecedence(str.at(i),st->peek()) == 1 || st->peek() == '('){
                    //cout<<"4"<<"\n";
                    st->push(str.at(i));
                    //st->printStack();
                }
                else
                {
                   // cout<<"5"<<"\n";
                   // st->printStack();
                    if(getPrecedence(str.at(i),st->peek()) <= 0){
                        res = res + st->pop();
                    //    cout<<res<<"\n";
                        i--;
                        continue;
                    }
                    st->push(str.at(i));
                    //st->printStack();
                }
            }
        }
    }
    //abcd^e-fgh*+^*+i-
     //cout<<"6"<<endl;
    while(!st->isEmpty()){
        res = res + st->pop();
        // cout<<res<<"\n";
    }
    return res;
}

int postToEvaluate(string str){
   stackLL<int>*st = new stackLL<int>();
   for(int i=0;i<str.length();i++){
     if(str.at(i) - '0' >= 0 && str.at(i) -'0' <= 9){
         st->push(str.at(i)-'0');
     }
     else {
         int a = st->pop();
         int b = st->pop();
         double res;
         if(str.at(i) == '/')
         { 
             res = b/a; 
         }
         else if(str.at(i) == '*')
         {
             res = a*b;
         }
         else if(str.at(i) == '+')
         {      
             res = a+b;
         }
         else if(str.at(i) == '-')
         {
             res = b-a;
         }
         st->push(res);
     }
   }
   int ans = st->peek();
   return ans;
}

string reverseString(string str){
    stackLL<char>*st = new stackLL<char>();
    for(int i=0;i<str.length();i++){
      st->push(str.at(i));
    }
    string res = "";
    while(!st->isEmpty()){
        res = res + st->pop();
    }
    return res;
}

bool checkBalancedParanthesis(string str)
{
   stackLL<char>*st = new stackLL<char>();
   for(int i=0;i<str.length();i++){
       if(str.at(i) == '(' || str.at(i) == '{' || str.at(i) == '[' ){
          st->push(str.at(i));
       }
       else 
       {
          if(str.at(i) == ')'){
              if(st->peek() == '(')
              st->pop();
              else 
              return false;
          }

          if(str.at(i) == '}'){
              if(st->peek() == '{')
              st->pop();
              else 
              return false;
          }


          if(str.at(i) == ']'){
              if(st->peek() == '[')
              st->pop();
              else 
              return false;
          }
       }
   }
   return st->isEmpty();
}

int main()
{
   //cout<<infixTopostfix("a+b*(c^d-e)^(f+g*h)-i")<<"\n";
    cout<<postToEvaluate("231*+9-")<<"\n";
    cout<<reverseString("GeeksQuiz")<<"\n";
    cout<<checkBalancedParanthesis("[(])");   
    return 0;
}