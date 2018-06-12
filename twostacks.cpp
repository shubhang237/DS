#include<iostream>
#define MAX 1000
using namespace std;

struct stackTwo{
  int top1;
  int top2;
  int size1;
  int size2;
  int *arr;
  stackTwo();
  void push1(int);
  void push2(int);
  int pop1();
  int pop2();
  bool isEmpty1();
  bool isEmpty2();
};

stackTwo::stackTwo()
{
    top1 = -1;
    top2 = MAX;
    size1 = 0;
    size2 = 0;
    arr = new int[MAX];
}

void stackTwo::push1(int x){
    if(top1+1 == top2){
      cout<<"Stack Overflow"<<"\n";
      return;
    }

    top1 = top1+1;
    arr[top1] = x;
    size1++;
}

void stackTwo::push2(int x){
    if(top2-1 == top1){
      cout<<"Stack Overflow"<<"\n";
      return;
    }

    top2 = top2-1;
    arr[top2] = x;
    size2++;
}

int stackTwo::pop1()
{
   if(top1 == -1){
      cout<<"Stack Underflow"<<"\n";
      return -1;
   }

   int temp = arr[top1];
   top1 = top1-1;
   size1--;
   return temp;
}

int stackTwo::pop2()
{
   if(top2 == MAX){
      cout<<"Stack Underflow"<<"\n";
      return -1; 
   }

   int temp = arr[top2];
   top2 = top2+1;
   size2--;
   return temp;
}

bool stackTwo::isEmpty1(){
    return size1 == 0;
}


bool stackTwo::isEmpty2(){
    return size2 == 0;
}

int main()
{
   stackTwo *ts = new stackTwo();
   ts->push1(10);
   ts->push1(20);
   ts->push1(30);
   ts->push1(40);
   ts->push2(90);
   ts->push2(80);
   ts->push2(70);
   ts->push2(60);
   cout<<ts->pop1()<<"\n";
   cout<<ts->pop2()<<"\n";
   cout<<ts->pop1()<<"\n";
   cout<<ts->pop2()<<"\n";
   cout<<ts->pop1()<<"\n";
   cout<<ts->pop2()<<"\n";
   cout<<ts->pop1()<<"\n";
   cout<<ts->pop2()<<"\n";
   cout<<ts->isEmpty1()<<"\n";
   cout<<ts->isEmpty2()<<"\n";
  return 0;
}