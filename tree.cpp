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
   void preorder(Node<T>*);
   void inorder(Node<T>*);
   void reverseInorder(Node<T>*);
   void postorder(Node<T>*);
   int height(Node<T>*);
   int SIZE(Node<T>*);
   int sizeWithRecursion(Node<T>*);
   int diameter(Node<T>*);
   void levelOrder(Node<T>*);
   int width(Node<T>*);
   T maximum(Node<T>*);
   T minimum(Node<T>*);
   void printLeftView(Node<T>*,int,T []);
   void printAncestors(Node<T>*,Node<T>*,bool);
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
void Tree<T>::reverseInorder(Node<T> *r){
   if(r == NULL){
       return;
   }

   inorder(r->right);
   cout<<r->data<<" ";
   inorder(r->left);
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
int Tree<T>::height(Node<T> *r){
  if(r == NULL)
  return 0;

  return 1+max(height(r->left),height(r->right));
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
int Tree<T>::diameter(Node<T> *r){
   if(r == NULL)
   return 0;

   int left_diameter = diameter(r->left);
   int right_diameter = diameter(r->right);

   return max(1+height(r->left) + height(r->right),max(left_diameter,right_diameter));
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
T Tree<T>::maximum(Node<T> *r){
   if(r == NULL){
       return INT_MIN;
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
       return INT_MAX;
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
      return;
  }

  printAncestors(r->left,req,flag);
  printAncestors(r->right,req,flag);

   
  if(r == req){
      flag = true;
      return;
  }

  if(flag){
      cout<<r->data<<" ";
      return;
  }
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
   root->right->left = new Node<char>('d');
   root->right->right = new Node<char>('e');
   root->left->left = new Node<char>('g');
   root->left->right = new Node<char>('h');
//    cout<<root->data<<"\n";
//    cout<<root->left->data<<"\n";
//    cout<<root->right->data<<"\n";
//    cout<<l1->data<<"\n";
//    cout<<r1->data<<"\n";
//    cout<<l2->data<<"\n";
  Tree<char> *t = new Tree<char>();
//    t->inorder(root);
//    cout<<endl;
//    t->preorder(root);
//    cout<<endl;
//    t->postorder(root);
//    cout<<endl;
//    t->levelOrder(root);
//    cout<<endl;
//    cout<<t->maximum(root);
//    cout<<endl;
//    cout<<t->minimum(root);
//    cout<<endl;
//    cout<<t->sizeWithRecursion(root);
//    cout<<endl;
//    cout<<t->height(root)<<"\n";
//    cout<<t->diameter(root)<<"\n";
//    reverseInorderWithoutRecursion(root);
//    cout<<endl;
//    char arr[100];
//    for(int i=0;i<100;i++){
//        arr[i] = -1;
//    }
//    t->printLeftView(root,0,arr);
cout<<t->width(root)<<"\n";

  return 0;
}

