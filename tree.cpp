#include<iostream>
#include<climits>
#include<stack>
#include<string>
#include<queue>
#include<map>
using namespace std;

template<class T>
struct Node{
   T data;
   Node<T> *left;
   Node<T> *right;
   Node<T> *next;
   Node(T);
};

template<class T>
Node<T>::Node(T x){
   left = NULL;
   right = NULL;
   next = NULL;
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
   int maxWidthAtLevel(Node<T>*,int);
   Node<T>* getLCA(Node<T>*,T,T);

   //print views
   void printLeftView(Node<T>*,int,T []);
   void printNodesAtK(Node<T>*,int k);
   void printZigZag(Node<T>*);
   void connectNodesAtSameLevel(Node<T>*);
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
   }
}
 
/* Function to traverse binary tree without recursion and 
   without stack */
template<class T>
void MorrisTraversal(Node<T> *r)
{
  Node<T> *pre,*curr = r;
  while(curr != NULL){
      if(curr->left == NULL){
          cout<<curr->data<<" ";
          curr = curr->right;
      }
      else
      {
          pre = curr->left;
          while(pre->right != NULL && pre->right != curr)
                pre = pre->right;
    
              if(pre->right == NULL){
                  pre->right = curr;
                  curr = curr->left;
              }
              else
              {
                 pre->right = NULL;
                 cout<<curr->data<<" ";
                 curr = curr->right;
              }
      }
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
int Tree<T>::maxWidthAtLevel(Node<T> *r,int level){
    if(r == NULL)
    return 0;
    
    if(level == 1)
    return 1;

    return maxWidthAtLevel(r->left,level-1)+maxWidthAtLevel(r->right,level-1);
}

template<class T>
int Tree<T>::width(Node<T> *r){

// level order traversal using queue
  if(r == NULL)
  return 0;

  queue<Node<T>*> q;
  q.push(r);
  int count = 0;
  int max_count = INT_MIN;
  while(!q.empty()){

      count = q.size(); 
      max_count = max(max_count,count);

    while(count--){   
      Node<T> *temp = q.front();
      q.pop();

      if(temp->left){
        q.push(temp->left);
      }

      if(temp->right){
          q.push(temp->right);
      }
    }
  }

 return max_count;
   
   //recursive width approach
    // int h = height(r);
    // int max_width = INT_MIN;
    // for(int i=1;i<=h;i++){
    //     max_width = max(max_width,maxWidthAtLevel(r,i));
    // }
    // return max_width;
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

template<class T>
void Tree<T>::printZigZag(Node<T> *r){
    if(r == NULL)
    return;

    int count = 0;
    queue<Node<T>*> q;
    q.push(r);
    int i = 0;
    while(!q.empty()){
       vector<Node<T>*> vc;        
       count = q.size();  
          while(count--){
              Node<T> *temp = q.front();
              vc.push_back(temp);
              q.pop();

              if(temp->left)
              q.push(temp->left);


              if(temp->right)
              q.push(temp->right);

          }

          if(i%2 == 0){
            for(int j=0;j<vc.size();j++){
                cout<<vc[j]->data<<" ";
            }
          }
          else
          {
             for(int j=vc.size()-1;j>=0;j--){
                cout<<vc[j]->data<<" ";
            }
          }
          i++;
    }

}


template<class T>
void Tree<T>::connectNodesAtSameLevel(Node<T> *r){
    if(r == NULL)
    return ;

    int count = 0;
    queue<Node<T>*>q;
    q.push(r);
    while(!q.empty()){
        count = q.size();
        int i = 0;
        //vector<Node<T>*> vc;
        Node<T> *temp;
        while(count--){
           if(i > 0){
               temp->next = q.front();
           }
           temp = q.front();
        //    vc.push_back(temp);
           q.pop();

           if(temp->left)
           q.push(temp->left);

           if(temp->right)
           q.push(temp->right);
           i++;
        }
        // for(int i=1;i<vc.size();i++){
        //     vc[i-1]->next = vc[i];
        // }
    }
}

template<class T>
Node<T>* Tree<T>::getLCA(Node<T> *r,T key1,T key2){
    if(r == NULL)
    return r;

    if(key1 == r->data || key2 == r->data)
    return r;

    Node<T> *left_ans = getLCA(r->left,key1,key2);
    Node<T> *right_ans = getLCA(r->right,key1,key2);
    
    if(left_ans && right_ans)
        return r;

    return left_ans != NULL ? left_ans : right_ans;
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
//    //t->printLeftView(root,0,arr);
//    t->printNodesAtK(root,1);
Node<char> *ans = t->getLCA(root,'d','f');
cout<<endl;
cout<<ans->data<<"\n";
//cout<<t->width(root)<<endl;
MorrisTraversal(root);
cout<<endl;
t->printZigZag(root);
t->connectNodesAtSameLevel(root);
cout<<endl;
Node<char> *temp = root->left;
while(temp){
    cout<<temp->data<<" ";
    temp = temp->next;
}
  return 0;
}

