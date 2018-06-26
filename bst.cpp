#include<iostream>
#include<vector>
#include<climits>
using namespace std;

template<class T>
struct Node{
   T data;
   Node<T> *left;
   Node<T> *right;
   Node(T);
};

template<class T>
Node<T>::Node(T x){
   left = NULL;
   right = NULL;
   data = x;
}

template<class T>
struct Tree
{
   Tree();
   Node<T>* insert(Node<T>*,T);
   bool search(Node<T>*,T);
   void inorder(Node<T>*);
   T minE(Node<T>*);
   Node<T>* DeleteNode(Node<T>*,Node<T>*);
};

template<class T>
Tree<T>::Tree(){

}


template<class T>
Node<T>* Tree<T>::insert(Node<T> *r,T x){
    if(r == NULL){
        r = new Node<T>(x);
        return r;
    }

    if(x < r->data)
    r->left = insert(r->left,x);
    else if(x > r->data)
    r->right = insert(r->right,x);
    
    return r;
}

template<class T>
bool Tree<T>::search(Node<T> *r,T x){
    if(r == NULL){
        return false;
    }

    if(x < r->data)
    return search(r->left,x);
    else if(x > r->data)
    return search(r->right,x);
    else
    return true;
}

template<class T>
void Tree<T>::inorder(Node<T> *r){
   if(r == NULL){
       return;
   }

   inorder(r->left);
   cout<<r->data<<" ";
   inorder(r->right);
}

template<class T>
T Tree<T>::minE(Node<T>* r){
    
    Node<T> *temp = r;
    while(temp && temp->left){
         temp = temp->left;
    }

    if(temp){
        return temp->data;
    }
    else
        return '!';
}

template<class T>
Node<T>* replaceInorderSuccesor(Node<T> *r){
    Node<T> *temp = r->right;
    Node<T> *prev = NULL;
    while(temp->left){
        prev = temp;
        temp = temp->left;
    }
    if(prev)
    prev->left = NULL;

    return temp;
}

template<class T>
Node<T>* replaceInorderPredecessor(Node<T> *r){
    Node<T> *temp = r->left;
    Node<T> *prev = NULL;
    while(temp->right){
        prev = temp;
        temp = temp->right;
    }
    if(prev)
    prev->right = NULL;

    return temp;
}

template<class T>
Node<T>* Tree<T>::DeleteNode(Node<T>* r,Node<T>  *t){
    if(r == NULL)
    return r;

    if(r->data > t->data){
        r->left = DeleteNode(r->left,t);
    }
    else if(r->data < t->data){
        r->right = DeleteNode(r->right,t);
    }
    else
    {
        if(r == t){
            if(r->left == NULL && r->right == NULL)
            return NULL;
            else if(r->left == NULL){
               Node<T> *temp = replaceInorderSuccesor(r);
               temp->right = r->right != temp ? r->right : NULL;
               return temp; 
            }
            else if(r->right == NULL){
               Node<T> *temp = replaceInorderPredecessor(r);
               temp->left = r->left != temp ? r->left : NULL;
               return temp; 
            }
            else{
               Node<T> *temp = replaceInorderSuccesor(r);
               temp->left = r->left != temp ? r->left : NULL;
               temp->right = r->right != temp ? r->right : NULL;
               return temp;
            }
            
        }
    }
    return r;
}


template<class T>
T InorderSuccesorKey(Node<T> *r,T data,T ans){
      if(r == NULL)
      return -1;

      if(r->data < data){
         return InorderSuccesorKey(r->right,data,r->data);
      }
      else if(r->data > data){
          return InorderSuccesorKey(r->left,data,r->data);
      }
      else
      {
         Node<T> *temp = r->right;
         while(temp && temp->left){
             temp = temp->left;
         }
         T res = temp ? temp->data : ans;
         return res > data ? res : -1;  
      }
}

template<class T>
T InorderPredecessorKey(Node<T> *r,T data,T ans){
    if(r == NULL)
      return -1;

      if(r->data < data){
         return InorderPredecessorKey(r->right,data,r->data);
      }
      else if(r->data > data){
          return InorderPredecessorKey(r->left,data,r->data);
      }
      else
      {
         Node<T> *temp = r->left;
         while(temp && temp->right){
             temp = temp->right;
         }
         T res = temp ? temp->data : ans;  
         return res < data ? res : -1;
      }
}

template<class T>
void prepareInorder(Node<T> *r,vector<Node<T>*> *list){
    if(r == NULL)
    return;

   prepareInorder(r->left,list);
   list->push_back(r);
  // cout<<r->data<<" ";
   //cout<<(*list)[list->size()-1]->data<<" ";
   prepareInorder(r->right,list); 
}

template<class T>
T smallestKNode(Node<T> *r,int k){
   if(r == NULL)
   return -1;

   vector<Node<T>*> *inorder = new vector<Node<T>*>();
   prepareInorder(r,inorder);
   //cout<<(*inorder).size()<<endl;
   if(k > (*inorder).size())
   return -1;

   return (*inorder)[k-1]->data;  
}

template<class T>
void mergeBst(Node<T> *r1,Node<T> *r2){
    if(r1 == NULL && r2 == NULL)
    return;

    if(r1 == NULL){
        mergeBst(r1,r2->left);
        mergeBst(r1,r2->right);
        return;
    }
    
    if(r2 == NULL){
        mergeBst(r1->left,r2);
        mergeBst(r1->right,r2);
        return;
    }

    if(r1->data < r2->data){
       cout<<r1->data<<" ";
       mergeBst(r1->left,r2);
       mergeBst(r1->right,r2);
    }
    else
    {
       cout<<r2->data<<" ";
       mergeBst(r1,r2->left);
       mergeBst(r1,r2->right); 
    }
}

int main(){
    Tree<int> *t = new Tree<int>();
    Node<int> *r1 = NULL;
    r1 = t->insert(r1,4);
    r1 = t->insert(r1,2);
    r1 = t->insert(r1,6);
    Node<int> *r2 = NULL;
    r2 = t->insert(r2,3);
    r2 = t->insert(r2,1);
    r2 = t->insert(r2,5);
    mergeBst(r1,r2);
    // root = t->insert(root,10);
    // root = t->insert(root,5);
    // root = t->insert(root,20);
    // root = t->insert(root,15);
    // root = t->insert(root,18);
    // root = t->insert(root,12);
    // root = t->insert(root,25);
    // root = t->insert(root,30);
    // cout<<smallestKNode(root,8)<<"\n";
    // t->inorder(root);
    // cout<<endl;
    // cout<<t->search(root,12)<<endl;
    // cout<<t->minE(root)<<endl;
    // root = t->DeleteNode(root,root->right->left->right);
    // t->inorder(root);
    // cout<<endl;
    // cout<<InorderSuccesorKey(root,25,-1)<<endl;
    // cout<<InorderPredecessorKey(root,5,-1);
    
    return 0;
}