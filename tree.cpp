#include<iostream>
#include<climits>
#include<stack>
#include<queue>
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
   Node<T> *root;
   Tree();

   //all traversals
   void preorder(Node<T>*);
   void inorder(Node<T>*);
   void postorder(Node<T>*);
   void levelOrder(Node<T>*);
   void reverseInorder(Node<T>*);

   // paramters of tree
   int height(Node<T>*);
   int diameter(Node<T>*);
   int width(Node<T>*);
   int sizeWithRecursion(Node<T>*);
   int SIZE(Node<T>*);
   T maximum(Node<T>*);
   T minimum(Node<T>*);

   //print views
   void printLeftView(Node<T>*,int,T []);
   void printAncestors(Node<T>*,Node<T>*,int);
   void printNodesAtK(Node<T>*,int k);
};

template<class T>
Tree<T>::Tree(){
  root = NULL;
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
void Tree<T>::preorder(Node<T> *r){
   if(r == NULL){
       return;
   }

   cout<<r->data<<" ";
   preorder(r->left);
   preorder(r->right);
}


template<class T>
void Tree<T>::postorder(Node<T> *r){
   if(r == NULL){
       return;
   }

   postorder(r->left);
   postorder(r->right);
   cout<<r->data<<" ";
}

template<class T>
void Tree<T>::levelOrder(Node<T> *r){
  if(r == NULL)
  return;

  queue<Node<T>*>q;
  q.push(r);
  while(!q.empty()){
      Node<T> *temp = q.front();
      cout<<temp->data<<" ";
      q.pop();
     
      if(temp->left)
      q.push(temp->left);

      if(temp->right)
      q.push(temp->right);
  }
}


template<class T>
void Tree<T>::reverseInorder(Node<T> *r){
   if(r == NULL){
       return;
   }

   inorder(r->right);
   cout<<r->data<<" ";
   inorder(r->left);
}

template<class T>
int Tree<T>::height(Node<T> *r){
  if(r == NULL)
  return 0;

  return 1+max(height(r->left),height(r->right));
}

template<class T>
int Tree<T>::diameter(Node<T> *r){
   if(r == NULL)
   return 0;

   int left_diameter = diameter(r->left);
   int right_diameter = diameter(r->right);

   return max(1+height(r->left) + height(r->right),max(left_diameter,right_diameter));
}


template<class T>
int Tree<T>::width(Node<T> *r){
  if(r == NULL)
  return 0;

  queue<Node<T>*> q;
  q.push(r);
  int count = 0;
  int i = 0;
  int max_count = INT_MIN;
  while(!q.empty()){
      Node<T> *temp = q.front();
      q.pop();
      i++;

      if(i == count){
          max_count = max(max_count,count);
          i=0;
          count=0;
      }
     
      if(temp->left){
        q.push(temp->left);
        count++;
      }

      if(temp->right){
          q.push(temp->right);
          count++;
      }
  }
 return max_count;
}


template<class T>
int Tree<T>::SIZE(Node<T> *r){
  if(r == NULL)
  return 0;

  queue<Node<T>*>q;
  q.push(r);
  int count = 0;
  while(!q.empty()){
      Node<T> *temp = q.front();
      count++;
      q.pop();
     
      if(temp->left)
      q.push(temp->left);

      if(temp->right)
      q.push(temp->right);
  }
  return count;
}

template<class T>
int Tree<T>::sizeWithRecursion(Node<T> *r){
  if(r == NULL)
  return 0;
 
  int left_size = sizeWithRecursion(r->left);
  int right_size = sizeWithRecursion(r->right);

  return left_size + right_size + 1;
}

template<class T>
T Tree<T>::maximum(Node<T> *r){
   if(r == NULL){
       return '!';
   }
  
   if(r->left == NULL && r->right == NULL)
      return r->data;

   T max_left = maximum(r->left);
   T max_right = maximum(r->right);

   return max(r->data,max(max_left,max_right));
}

template<class T>
T Tree<T>::minimum(Node<T> *r){
   if(r == NULL){
       return '!';
   }
  
   if(r->left == NULL && r->right == NULL)
      return r->data;

   T min_left = minimum(r->left);
   T min_right = minimum(r->right);

   return min(r->data,min(min_left,min_right));
}

template<class T>
void Tree<T>::printLeftView(Node<T> *r,int height,T arr[100]){
   if(r == NULL)
   return;

   if(arr[height] == -1){
       arr[height] = r->data;
       cout<<arr[height]<<" ";
   }

   printLeftView(r->left,height+1,arr);
   printLeftView(r->right,height+1,arr);
}

template<class T>
void Tree<T>::printAncestors(Node<T> *r,Node<T> *req,bool flag){
  
  if(r == NULL){
      cout<<"3"<<endl;
      return;
  }

  if(r == req){
      cout<<"1"<<endl;
      flag = true;
      return;
  }

  printAncestors(r->left,req,flag);
  printAncestors(r->right,req,flag);

}

template<class T>
void inorderWithoutRecursion(Node<T> *r){
   stack<Node<T>*> s;
   s.push(r);
   while(!s.empty()){
       if(r->left){
           s.push(r->left);
           r = r->left;
       }
       else
       {
           Node<T> *temp = s.top();
           cout<<temp->data<<" ";
           s.pop();
           if(temp->right){
               s.push(temp->right);
           }
       }
   }
}

template<class T>
void reverseInorderWithoutRecursion(Node<T> *r){
   stack<Node<T>*> s;
   s.push(r);
   while(!s.empty()){
       if(r->right){
           s.push(r->right);
           r = r->right;
       }
       else
       {
           Node<T> *temp = s.top();
           cout<<temp->data<<" ";
           s.pop();
           if(temp->left){
               s.push(temp->left);
           }
       }
   }
}

template<class T>
void Tree<T>::printNodesAtK(Node<T> *r,int k){
    if(r == NULL)
    return;

    if(k == 0){
    cout<<r->data<<" ";
    return;
    }

    printNodesAtK(r->left,k-1);
    printNodesAtK(r->right,k-1);
}

int main()
{
//    Node<int> *root = new Node<int>();
//    root->data = 14;
//    Node<int> *l1 = new Node<int>();
//    l1->data = 17;
//    Node<int> *r1 = new Node<int>();
//    r1->data = 111;
//    Node<int> *l2 = new Node<int>();
//    l2->data = 46;
//    root->left = l1;
//    root->right = r1;
//    l1->left = l2;

  Node<char> *root = new Node<char>('a');
   root->left = new Node<char>('b');
   root->right = new Node<char>('c');
   root->left->left = new Node<char>('d');
   root->left->right = new Node<char>('e');
   root->right->left = new Node<char>('f');
   root->right->right = new Node<char>('g');
   Tree<char> *t = new Tree<char>();
   t->inorder(root);
   cout<<endl;
   t->preorder(root);
   cout<<endl;
   t->postorder(root);
   cout<<endl;
   t->levelOrder(root);
   cout<<endl;
   cout<<t->maximum(root);
   cout<<endl;
   cout<<t->minimum(root);
   cout<<endl;
   cout<<t->sizeWithRecursion(root);
   cout<<endl;
   cout<<t->height(root)<<"\n";
   cout<<t->diameter(root)<<"\n";
   reverseInorderWithoutRecursion(root);
   cout<<endl;
   char arr[100];
   for(int i=0;i<100;i++){
       arr[i] = -1;
   }
   //t->printLeftView(root,0,arr);
   t->printNodesAtK(root,1);
   t->printAncestors(root,root->left,false);

  return 0;
}

