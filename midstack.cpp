#include<iostream>
#include<string.h>
using namespace std;

template <class T>
struct Node
{
   Node<T> *next;
   Node<T> *prev;
   T data;
};

template <class T>
struct stackLL
{
   Node<T> *top;
   Node<T> *mid;
   int size;
   stackLL();
   void push(T);
   T pop();
   T peek();
   T deleteMid();
   T findMid();
   bool isEmpty();
   void printStack();
};

template <class T>
stackLL<T>::stackLL(){
    top = NULL;
    mid = NULL;
    size = 0;
}

template <class T>
void stackLL<T>::push(T x){
   Node<T>*newNode = (struct Node<T>*)malloc(sizeof(struct Node<T>));
   newNode->data = x;
   if(top == NULL){
       top = newNode;
       mid = newNode;
       size++;
       return;
   }

   newNode->next = top;
   if(top)
   top->prev = newNode;
   top = newNode;
   if(size%2 == 0){
       mid = mid->prev;
   }
   size++;
}

template <class T>
T stackLL<T>::pop(){
    if(!top){
        return '|';
    }

    Node<T>* t = top;
    top = top->next;
    size--;  
    if(size%2 == 0){
        mid = mid->next;
    }
    T temp = t->data; 
    return temp;
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
T stackLL<T>::findMid()
{
    if(!mid)
    return '|';

    return mid->data;
}

template <class T>
T stackLL<T>::deleteMid()
{
    if(!mid)
     return '|';

    Node<T> *p = mid->prev;
    Node<T> *f = mid->next;
    if(p){
        if(size%2 == 0){
            mid = mid->prev;
        }
        mid->prev = NULL;
        mid->next = NULL;
        p->next = f;
        if(f)
        f->prev = p;
    }
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
   ss->push('a');
   ss->push('s');
   ss->push('z');
   ss->push('y');
   ss->push('q');
   ss->push('w');
   ss->printStack();
   cout<<ss->findMid()<<"\n";
   ss->pop();
   ss->pop();
   ss->printStack();
   cout<<ss->findMid()<<"\n";
   ss->pop();
   ss->printStack();
   cout<<ss->findMid()<<"\n";

    return 0;
}