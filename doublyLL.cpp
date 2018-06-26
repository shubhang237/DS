#include <iostream>
using namespace std;

struct Node{
    Node *next;
    Node *prev;
    int data;
};

struct NodeT{
    NodeT *left;
    NodeT *right;
    int data;
};

struct DoublyLL{
    Node *front;
    Node *last;
    DoublyLL(){
        front = NULL;
        last = NULL;
    }
    void InsertFront(int);
    void InsertEnd(int);
    void InsertBefore(Node*,int);
    void InsertAfter(Node*,int);
    void DeleteNode(Node*);
    void ReverseLL();
    void printDLL();
    void printReverseDLL();
};

void DoublyLL::InsertFront(int data){
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    if(!front){
    front = last = newNode;
    return;
    }
    newNode->next = front;
    front->prev = newNode;
    front = newNode;
}


void DoublyLL::InsertEnd(int data){
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    if(!front){
    front = last = newNode;
    return;
    }
    last->next = newNode;
    newNode->prev = last;
    last = newNode;
}

void DoublyLL::InsertBefore(Node *t,int data){
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    if(!t->prev){
        t->prev = newNode;
        newNode->next = t;
        front = t;
        return;
    }

    Node *temp = t->prev;
    temp->next = newNode;
    newNode->next = t;
}


void DoublyLL::InsertAfter(Node *t,int data){
    Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    if(!t->next){
        t->next = newNode;
        newNode->prev = t;
        last = newNode;
        return;
    }

    Node *temp = t->next;
    t->next = newNode;
    newNode->next = temp;
}

void DoublyLL::DeleteNode(Node *t){
    if(!t->prev)
    {
        Node *t1 = t->next;
        t1->prev = NULL;
        front = t1;
        free(t);
        return;
    }

    Node *temp = t->prev;
    temp->next = t->next;
    Node *temp1 = t->next;
    if(temp1)
    temp1->prev = temp;
    free(t);
}

void DoublyLL::ReverseLL(){
   if(!front)
   return;

   Node *temp = front->next;
   front->next = NULL;
   front->prev = temp;
   last = front;
   while(temp){
       Node *forw = temp->next;
       if(!forw)
       front = temp;
       Node *back = temp->prev;
       temp->next = back;
       temp->prev = forw;
       temp = forw;
   }
}


void DoublyLL::printDLL(){
    Node *temp = front;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}


void DoublyLL::printReverseDLL(){
    Node *temp = last;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->prev;
    }
    cout<<endl;
}

void printDLL(DoublyLL *dll){
    Node *temp = dll->front;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void treeToList(NodeT *root,DoublyLL **dl){
    if(root == NULL)
    return;

    treeToList(root->left,dl);
    if((*dl)->front == NULL){
        Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = root->data;
        (*dl)->front = (*dl)->last = newNode;
    } 
    else
    {
        Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = root->data;
        (*dl)->last->next = newNode;
        newNode->prev = (*dl)->last;
        (*dl)->last = newNode;
    }
    treeToList(root->right,dl);
}

Node* merge(Node *t1,Node *t2){
    Node *temp = NULL;
    Node *help = NULL;
    Node *head = NULL;
    while(t1 && t2){
        if(t1->data < t2->data){
            if(temp == NULL)
            {
                temp = t1;
                head = temp;
                t1 = t1->next;
                temp->next = NULL;
                if(t1)
                t1->prev = NULL;
            }
            else
            {
                help = t1;
                t1 = t1->next;
                help->next = NULL;
                if(t1)
                t1->prev = NULL; 
                temp->next = help;
                help->prev = temp;
                temp = temp->next;
            }
        }
        else
        {
            if(temp == NULL)
            {
                temp = t2;
                head = temp;
                t2 = t2->next;
                temp->next = NULL;
                if(t2)
                t2->prev = NULL;
            }
            else
            {
                help = t2;
                t2 = t2->next;
                help->next = NULL;
                if(t2)
                t2->prev = NULL; 
                temp->next = help;
                help->prev = temp;
                temp = temp->next;
            }

        }
    }

    if(t1){
       temp->next = t1;
       t1->prev = temp;
    }

    if(t2){
        temp->next = t2;
        t2->prev = temp;
    }

    return head;
}

Node* mergeSort(Node *head){
    if(!head){
    return head;
    }

    if(!head->next){
    return head;
    }
  
    Node *slow = head;
    Node *fast = head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    Node *p = slow->prev;
    if(p)
    p->next = NULL;
    slow->prev = NULL;
   
     Node *left = mergeSort(head);
     Node *right = mergeSort(slow);
     head =  merge(left,right);
     return head;
}

int main()
{

    DoublyLL *dll = new DoublyLL();
    dll->InsertFront(18);
    dll->InsertFront(21);
    dll->InsertFront(13);
    dll->InsertFront(25);
   // dll->printDLL();
    //DoublyLL *dll1 = new DoublyLL();
    dll->InsertFront(15);
    //dll->printDLL();
    dll->InsertFront(17);
    dll->InsertFront(2);
    dll->InsertFront(1);
    //dll->printDLL();
  //  dll->front = merge(dll->front,dll1->front);
    //dll->printDLL();
    dll->front = mergeSort(dll->front);
    dll->printDLL();
    // //dll->printReverseDLL();
    // Node *temp = dll->front->next->next;
    // dll->DeleteNode(temp);
    // dll->printDLL();
    // dll->ReverseLL();
    // dll->printDLL();
     // NodeT *root = (struct NodeT*)malloc(sizeof(struct NodeT));
    // root->data = 10;
    // NodeT *newNode =  (struct NodeT*)malloc(sizeof(struct NodeT));
    // newNode->data = 8;
    // root->left = newNode;
    // newNode =  (struct NodeT*)malloc(sizeof(struct NodeT));
    // newNode->data = 12;
    // root->right = newNode;
    // treeToList(root,&dll);
    // printDLL(dll);
    
     return 0;
}