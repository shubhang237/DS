#include<iostream>
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

int main(){
    Tree<int> *t = new Tree<int>();
    Node<int> *root = NULL;
    root = t->insert(root,10);
    root = t->insert(root,5);
    root = t->insert(root,20);
    root = t->insert(root,15);
    root = t->insert(root,18);
    root = t->insert(root,12);
    root = t->insert(root,25);
    root = t->insert(root,30);
     t->inorder(root);
    cout<<endl<<t->search(root,12);
    cout<<endl<<t->minE(root);
    root = t->DeleteNode(root,root->right->left->right);
    cout<<"\n";
    t->inorder(root);
    cout<<endl<<InorderSuccesorKey(root,25,-1);
    cout<<endl<<InorderPredecessorKey(root,5,-1);
    return 0;
}