#include<iostream>
using namespace std;

struct Node{
    int data;
    Node *next;
};

struct CircularLL
{
    Node *start;
    Node *end;
    int size;
    CircularLL(){
        start = NULL;
        end = NULL;
        size = 0;
    }
    void InsertEnd(int);
    void InsertFront(int);
    void InsertPos(int,int);
    void InsertSorted(int);
    void printLL();
};

void CircularLL :: InsertEnd(int data){
    if(!start && !end){
        Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        start = end = newNode;
        size++;
        return;
    }

    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    end->next = newNode;
    end = newNode;
    end->next = start;
    size++;
}

void CircularLL :: InsertFront(int data){
    if(!start && !end){
        Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        start = end = newNode;
        size++;
        return;
    }

    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    end->next = newNode;
    newNode->next = start;
    start = newNode;
    size++;
}

void CircularLL :: InsertPos(int data,int pos){

    if(pos > size){
        cout<<"could Not add"<<endl;
        return;
    }

    if(pos == 0){
        InsertFront(data);
        size++;
        return;
    }
    
    
    if(!start && !end){
        Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        start = end = newNode;
        size++;
        return;
    }

    if(pos == size){
        InsertEnd(data);
        size++;
        return;
    }

    Node *prev;
    Node *temp = start;
    while(pos > 0){
       prev = temp;
       temp = temp->next;
       pos--;
    }
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    prev->next = newNode;
    newNode->next = temp;
    size++;
}


void CircularLL::InsertSorted(int data){
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;  

    if(!start){
      start = end = newNode;
      return;
    }

    Node *temp = start;
    Node *prev = NULL;
    while(data > temp->data){
        prev = temp;
        temp = temp->next;
        if(prev->next == start){
          prev->next = newNode;
          newNode->next = start;
          end = newNode;
          return;
        }
    }

    if(!prev){
      newNode->next = start;
      end->next = newNode;
      start = newNode;
      return;  
    }

    if(prev->next == start){
        prev->next = newNode;
        newNode->next = start;
        end = newNode;
        return;
    }

    Node *t = prev->next;
    prev->next = newNode;
    newNode->next = t;
}


void CircularLL :: printLL(){
    Node *temp = NULL;
    while(temp != end){
        if(temp == NULL)
        temp = start;
        else{
        temp = temp->next;
        }
        cout<<temp->data<<" ";
    }
    cout<<endl;
}

void printLL(Node *t){
    if(t == NULL){
     return;
    }
    
    Node *temp = t;
    cout<<temp->data<<" ";
    while(temp->next != t){
        temp = temp->next;
        cout<<temp->data<<" ";
    }
    cout<<endl;
    
}

void splitHalf(Node **t1,Node **t2,Node *head){
    Node *temp = head;
    *t1 = head;
    int count = 0;
    while(temp->next != head){
        temp = temp->next;
        count++;
    }
    Node *t = head;
    int i =0;
    while(i < count/2){
        t = t->next;
        i++;
    }
    *t2 = t->next;
    t->next = *t1;
    temp->next = *t2; 
}

int main()
{
   CircularLL *cl = new CircularLL();
   cl->InsertSorted(10);
   cl->InsertSorted(5);
   cl->InsertSorted(3);
   cl->printLL();
   cl->InsertSorted(4);
   cl->printLL();
   cl->InsertSorted(6);
   cl->InsertSorted(25);
   cl->InsertSorted(50);
   cl->InsertSorted(7);
   //cl->InsertEnd(60);
   //cl->InsertFront(5);
   //cl->InsertPos(3,5);
   //cout<<cl->size<<endl;
   //Node *t1 = NULL;
   //Node *t2 = NULL;
  // splitHalf(&t1,&t2,cl->start);
   //cout<<t1->next->next->next->data<<" ";
   cl->printLL();
   //printLL(t2);
   
return 0;
}