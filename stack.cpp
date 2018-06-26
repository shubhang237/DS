#include<iostream>
#define MAX 1000
using namespace std;

struct stack{
   int *arr;
   int top;
   int size;
   stack();
   void push(int);
   int pop();
   int peek();
   bool isEmpty();
   void insertBottom(int);
   void reverseStack();
   void sortStack();
   void placeCorrect(int);
   void enqueue(int);
};

stack::stack(){
    arr = new int[MAX];
    top = -1;
    size = 0;
}

void stack::push(int x){
    if(top == -1){
        top = 0;
        size++;
        arr[top] = x;
        return;
    }

    if(top+1 == MAX){
        cout<<"Stack Overflow"<<"\n";
        return;
    }

    top = top+1;
    size++;
    arr[top] = x;
}

int stack::pop(){
    if(size == 0){
      //cout<<"Stack Underflow"<<"\n";
      return -1;
    }

    int temp = arr[top];
    top = top-1;
    size--;
    return temp;
}

int stack::peek(){
    if(top == -1){
        cout<<"No Element Present"<<"\n";
        return -1;
    }
    return arr[top];
}

bool stack::isEmpty(){
   return size == 0;
}

void NGE(int *arr,int n){
    stack *st = new stack();
    st->push(arr[0]);
    for(int i=1;i<n;i++){
       while(!st->isEmpty() && st->peek() <= arr[i]){
           cout<<st->pop()<<" --> "<<arr[i]<<"\n";
       }
       st->push(arr[i]);
    }
    while(!st->isEmpty()){
      cout<<st->pop()<<" --> "<<"-1"<<"\n";    
    }
}


void stack::insertBottom(int x){
   if(isEmpty()){
       push(x);
       return;
   }
   int t = pop();
   insertBottom(x);
   push(t);
}

void stack::reverseStack()
{
    if(isEmpty())
     return;

   int top = pop();
   reverseStack();
   insertBottom(top);
}

void stack::placeCorrect(int x){
   if(isEmpty()){
      push(x);
      return;
   }

    if(x < peek()){
        push(x);
    }
    else
    {
        int t = pop();
        placeCorrect(x);
        push(t);
    }
}

void stack::sortStack(){
   if(isEmpty())
   return;

   int temp = pop();
   sortStack();
   placeCorrect(temp);    
}

void stack::enqueue(int x){
    stack *q = new stack();
    while(!isEmpty()){
        q->push(pop());
    }
    q->push(x);
    while(!q->isEmpty()){
        push(q->pop());
    }
}

void stockspan(int arr[],int n){
   stack *st = new stack(); 
   cout<<"1"<<" ";
   st->push(0);
   for(int i=1;i<n;i++){
      while(!st->isEmpty() && arr[i] >= arr[st->peek()]){
          st->pop();
      }
      cout<<(st->isEmpty() ? i+1 : i-st->peek())<<" ";
      st->push(i);
   }   
}

int main()
{ 

    // int arr[6] = {10,4,5,90,120,80};
    // stockspan(arr,6);
    stack *s = new stack();
    s->push(12);
    s->push(7);
    s->push(24);
    s->push(87);
    s->push(42);
    s->push(78);
    //s->sortStack();
     cout<<s->pop()<<" ";
    // cout<<s->peek()<<" ";
     cout<<s->pop()<<" ";
     cout<<s->pop()<<" ";
     cout<<s->pop()<<" ";
     cout<<s->pop()<<" ";
    // cout<<s->peek()<<" ";
     cout<<s->pop()<<" ";
    // cout<<s->pop()<<" ";
    // cout<<s->pop()<<" ";
    // int *arr = new int[4];
    // arr[0] = 13;
    // arr[1] = 7;
    // arr[2] = 6;
    // arr[3] = 12;
    // int n = 4;
    // NGE(arr,n);    
    return 0;
}