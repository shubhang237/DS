#include<iostream>
using namespace std;

struct Node{
   Node *next;
   int data;

   
};

Node* insertEnd(Node *head,int x){
    if(head ==  NULL){
        head = (struct Node*)malloc(sizeof(struct Node));
        head->data = x;
        return head;
    }

    Node *temp  = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    Node *newNode  = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    temp->next  = newNode;
    return head;
}


Node* insertFront(Node *head,int x){
    if(head ==  NULL){
        head = (struct Node*)malloc(sizeof(struct Node));
        head->data = x;
        return head;
    }

    Node *newNode  = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next  = head;
    head = newNode;
    return head;
}

Node* insertAfter(Node *head,int pos,int x){
    if(head ==  NULL){
        cout<<"Could Not Insert As Element Not found"<<"\n";
        return head;
    }

    Node *newNode  = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    Node *temp = head;
    bool flag = false;
    int count = 0;
    while(temp !=  NULL){
        if(count == pos){
        flag = true;
        break;
        }
        count++;
        temp = temp->next;
    }
    if(flag){
        Node *temp2 = temp->next;
        temp->next = newNode;
        newNode->next = temp2;
    }
    else
    {
        cout<<"Could Not Insert As Element Not Found"<<"\n";
    }
    return head;
}


Node* DeleteKey(Node *head,int key){
   if(head == NULL){
       cout<<"Could Not Delete Key Not Found"<<"\n";
       return head;
   }

   if(head->data == key){
       Node *t = head;
       head = head->next;
       free(t);
       return head; 
   }
    
   Node *temp = head;
   Node *prev = head;
   while(temp != NULL && temp->data != key){
       prev = temp;
       temp = temp->next;
   }

   if(temp == NULL){
       cout<<"Could Not Delete Key Not Found"<<"\n";
       return head;
   }
   else
   prev->next = temp->next;
   
   free(temp);

   return head;
}

Node* DeletePosition(Node *head,int pos){
   if(head == NULL){
       cout<<"Could Not Delete Key Not Found"<<"\n";
       return head;
   }
   
   if(pos == 0){
       Node *t = head;
       head = head->next;
       free(t);
       return head;
   }

   Node *temp = head;
   Node *prev = head;
   while(temp != NULL && pos > 0){
      prev = temp;
      temp = temp->next;
      pos--;
   }

   if(temp ==  NULL){
       cout<<"Could Not Delete Key Not Found"<<"\n";
       return head;
   }

   prev->next = temp->next;

   free(temp);

   return head;   
}

void printLL(Node *head){
    while(head != NULL){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
    return;
}

int countNodes(Node *head){
    Node *temp = head;
    int count = 0;
    while(temp != NULL){
      count++;
      temp = temp->next;
    }
    return count;
}

int countNodesR(Node *temp){
    if(temp ==  NULL){
        return 0;
    }

    return 1+countNodesR(temp->next);
}

Node* swap(Node *head,int key1,int key2){
    Node *p1 = NULL,*c1 = head,*n1 = c1->next;
    Node *p2 = NULL,*c2 = head,*n2 = c2->next;
    while(c1 !=  NULL && c1->data != key1){
        p1 = c1;
        c1 = c1->next;
        if(c1){
           n1 = c1->next; 
        }
    }

    while(c2 !=  NULL && c2->data != key2){
        p2 = c2;
        c2 = c2->next;
        if(c2){
           n2 = c2->next; 
        }
    }

    if(c1 == NULL || c2 == NULL){
      cout<<"swapping not possible"<<"\n";
      return head;
    }
    
    if(c1 == c2->next || c2 == c1->next){
        if(p2)
        p2->next = n2;
        else
        head = n2;
        c2->next = p2;
        if(p1)
        p1->next = c2;
        else
        head = c2;
        return head; 
        
    }

    
    if(p2)
    p2->next = c1;
    else
    head = c1;
    c1->next = n2;
    if(p1)
    p1->next = c2;
    else
    head = c2;
    c2->next = n1;

    return head;
}

Node* reverseLL(Node *head){
    Node *curr = head;
    Node *prev = NULL;
    while(curr != NULL){
        Node *forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw; 
    }
    return prev;
}

Node* mergeList(Node *temp1,Node *temp2){
    Node *temp = NULL;
    Node *head;
    while(temp1 && temp2){
        if(temp == NULL){
            Node *t;
            if(temp1->data < temp2->data){
               t = temp1;
               temp1 = temp1->next;
               t->next = NULL;
               temp = t;
               head = temp;
            }
            else
            {
               t = temp2;
               temp2 = temp2->next;
               t->next = NULL;
               temp = t;
               head = temp;
            }
        }
        else
        {
            Node *t;
            if(temp1->data < temp2->data){
               t = temp1;
               temp1 = temp1->next;
               t->next = NULL;
               temp->next = t;
               temp = t;
            }
            else
            {
               t = temp2;
               temp2 = temp2->next;
               t->next = NULL;
               temp->next = t;
               temp = t;
            }
        }
    }

    if(temp1){
       temp->next =temp1;
    }

    if(temp2){
       temp->next =temp2;
    }

    return head;
}

Node * mergeSort(Node *head){
    if(head == NULL){
        return head;
    }

    if(head->next == NULL){
        return head;
    }
    
    Node *slow = head;
    Node *fast = head;
    Node *prev = NULL;
    while(fast && fast->next){
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if(prev)
    prev->next = NULL;

    Node *t1 = mergeSort(head);
    Node *t2 = mergeSort(slow);
    return mergeList(t1,t2);
}

Node* groupReverse(Node *head,int k){
   if(!head)
   return head;

   int count=0;
   Node *temp = head;
   Node *prev = NULL;
   while(temp && count < k){
      prev = temp; 
      temp = temp->next;
      count++;
   }
   if(prev)
   prev->next = NULL;
   prev = head;
   head = reverseLL(head);
   Node *temp2 = groupReverse(temp,k);
   prev->next = temp2;
   return head;
}

Node* DetectLoopAndRemove(Node *temp){
    if(!temp)
    return temp;

    Node *slow = temp;
    Node *fast = temp;
    bool flag  = false;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow)
        {
            flag = true;
            break;
        }
    }

    if(!flag)
    return temp;
    // fastest method 
    slow = temp;
    while(slow->next != fast->next){
      slow = slow->next;
      fast = fast->next;
    }
    fast->next = NULL;

    // brute force method
    //  Node *head = temp;
    // while(true){
    //     Node *t = fast;
    //     while(t->next != fast){
    //         if(t->next == head)
    //         {
    //            t->next = NULL;
    //            return temp; 
    //         }
    //         t = t->next;
    //     }
    //     head = head->next;
    // }
    return temp;
} 

Node* addedLL(Node *temp1,Node *temp2){
   int num1 = 0;
   int num2 = 0;
   int i = 1;
   while(temp1){
       num1 += temp1->data*i;
       temp1 = temp1->next;
       i = i*10;
   }
   i = 1;
   while(temp2){
       num2 += temp2->data*i;
       temp2 = temp2->next;
       i = i*10;
   }

   Node *head = NULL;
   int sum = num1 + num2;
   Node *temp = NULL;
   while(sum > 0){
       if(!temp){
           temp = (struct Node*)malloc(sizeof(struct Node));
           temp->data = sum%10;
           head = temp;
       }
       else
       {
           Node *newNode = (struct Node*)malloc(sizeof(struct Node));
           newNode->data = sum%10;
           temp->next = newNode;
           temp = newNode;
       }
       sum = sum/10;
   }
   return head; 
}

Node* rotateLL(Node *temp,int k){
  if(k >= countNodes(temp))
  return temp;

  Node* t = temp;
  while(k > 1){
      t = t->next;
      k--;
  }
  Node*t1 = t->next;
  t->next = NULL;
  Node *t2 = t1;
  while(t2->next){
      t2 = t2->next;
  }
  t2->next = temp;
  return t1;
}

int main()
{ 
//   Node *h1 =  NULL,*h2 = NULL;
//   h1 = insertEnd(h1,2);
//   h1 = insertEnd(h1,7);
//   h1 = insertEnd(h1,8);
//   printLL(h1);
//   h2 = insertEnd(h2,1);
//   h2 = insertEnd(h2,2);
//   h2 = insertEnd(h2,8);
//   printLL(h2);
//   Node *head = addedLL(h1,h2);
//   printLL(head);
//   Node *merged = mergeList(h1,h2);
//   printLL(merged);
   
  Node *head;
  head = insertEnd(head,10);
  head = insertEnd(head,20);
  printLL(head);
  head = insertEnd(head,30);
  head = insertFront(head,7);
  printLL(head);
  head = insertEnd(head,40);
  head = insertFront(head,5);
  printLL(head);
  head = insertAfter(head,4,35);
  printLL(head);
  head = DeleteKey(head,40); 
  printLL(head);
  head = DeletePosition(head,6);
  printLL(head);
  cout<<countNodes(head)<<endl;
  cout<<countNodesR(head)<<endl;
  head = swap(head,10,30);
  printLL(head);
  head = reverseLL(head);
  printLL(head);
  head = mergeSort(head);
  printLL(head);
  head = groupReverse(head,4);
  printLL(head);
  head = rotateLL(head,3);
  printLL(head);

// Node *t1 = (struct Node*)malloc(sizeof(struct Node));
// t1->data = 10;
// Node *t2 = (struct Node*)malloc(sizeof(struct Node));
// t2->data = 20;
// Node *t3 = (struct Node*)malloc(sizeof(struct Node));
// t3->data = 30;
// Node *t4 = (struct Node*)malloc(sizeof(struct Node));
// t4->data = 40;
// Node *t5 = (struct Node*)malloc(sizeof(struct Node));
// t5->data = 50;
// t1->next = t2;
// t2->next = t3;
// t3->next = t4;
// t4->next = t5;
// t5->next = t2;
// t1 = DetectLoopAndRemove(t1);
// printLL(t1);

  return 0;
}