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
   Node<T> *topM;
   int size;
   stackLL();
   void push(T);
   T pop();
   T peek();
   T getMin();
   bool isEmpty();
   void printStack();
};

template <class T>
stackLL<T>::stackLL(){
    top = NULL;
    topM = NULL;
    size = 0;
}

template <class T>
void stackLL<T>::push(T x){
   Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
   newNode->data = x;
   if(top == NULL){
       top = newNode;
       Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
       newNode->data = x;
       topM = newNode;
       size++;
       return;
   }

   newNode->next = top;
   top = newNode;
   size++;
   if(topM && topM->data > x){
     Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
     newNode->data = x;
     topM = topM->next;
     newNode->next = topM;
     topM = newNode;
  }
  else
  {
     Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
     newNode->data = topM->data;
     newNode->next = topM;
     topM = newNode;
  }
}

template <class T>
T stackLL<T>::pop(){
    if(!top){
        return '|';
    }

    Node<T>*t = top;
    top = top->next;
    size--;   
    if(topM)     
    topM = topM->next;
    return t->data;
}

template <class T>
T stackLL<T>::peek()
{
    if(top == NULL){
        return '|';
    }
    return top->data;
}

template <class T>
T stackLL<T>::getMin()
{
    if(!topM)
     return '|';

    return topM->data;
}

template <class T>
bool stackLL<T>::isEmpty()
{
    return size==0;
}


template <class T>
void stackLL<T>::printStack()
{
    Node<T>*temp = top;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<"\n";
}

int main()
{
   stackLL<char> *ss = new stackLL<char>();
   //ss->push('a');
   ss->push('s');
   ss->push('z');
   ss->push('y');
   ss->push('q');
   ss->push('w');
   ss->printStack();
   cout<<ss->getMin()<<"\n";
   ss->pop();
   ss->pop();
   ss->printStack();
   cout<<ss->getMin()<<"\n";
   ss->pop();
   ss->printStack();
   cout<<ss->getMin()<<"\n";

    return 0;
}