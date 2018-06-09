#include<iostream>
using namespace std;

template<class T>
struct Node
{
  T data;
  Node *next;
  Node(T x);
};

template<class T>
Node<T> :: Node(T x){
    data = x;
    next = NULL;
}


template<class T>
struct LL
{
   Node <T> *head;
   public:
   void Insert(T x);
   void printLL();
};


template<class T>
void LL<T> :: Insert(T data){
   
   if(!head){
       head = new Node<T>(data);
       return;
   }
   
   Node <T> *temp = head;
   while(temp->next != NULL){
       temp = temp->next;
   }
   temp->next = new Node<T>(data);
}

template<class T>
void LL<T> :: printLL(){
    Node <T> *temp  = head;
   while(temp != NULL){
       cout<<temp->data<<" ";
       temp = temp->next;
   }
   cout<<endl;
}
/*
template<class T>
bool num<T> :: Greater(){
  if(this->a > this->b){
      return true;
  }
  else
    return false;
} 

*/

int main()
{     
   LL <char>*l = new LL<char>();
   l->Insert('a');
   l->Insert('b');
   l->Insert('c');
   l->Insert('d');
   l->printLL();
    
   return 0;
}