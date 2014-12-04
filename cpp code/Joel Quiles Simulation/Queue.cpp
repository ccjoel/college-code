//Queue.cpp
#include <new>
using namespace std;
#include "Queue.h"
Queue::Queue()
: myFront(0), myBack(0)
{}

Queue::Queue(const Queue & original){
   myFront = myBack = 0;
   if (!original.empty()){
      myFront = myBack = new Queue::Node(original.front());
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0){
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

Queue::~Queue(){ 
  Queue::NodePointer prev = myFront,ptr;
  while (prev != 0){
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

const Queue & Queue::operator=(const Queue & rightHandSide){
   if (this != &rightHandSide){
      this->~Queue();           
      if (rightHandSide.empty())
         myFront = myBack = 0;
      else{       
         myFront = myBack = new Queue::Node(rightHandSide.front());
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0){
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

bool Queue::empty() const{ 
   return (myFront == 0); 
}

void Queue::enqueue(const QueueElement & value){
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else{
      myBack->next = newptr;
      myBack = newptr;
   }
}

void Queue::display(ostream & out) const{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

QueueElement Queue::front() const{
   if (!empty())
      return (myFront->data);
   else{
      cerr << "*** Queue esta vacio\n";
      QueueElement * temp = new(QueueElement);  
      QueueElement garbage = *temp;
      delete temp;
      return garbage;
   }
}

void Queue::dequeue(){
   if (!empty()){
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)
         myBack = 0;
   }   
   else
      cerr << "*** Queue esta vacio! ***\n";
}
