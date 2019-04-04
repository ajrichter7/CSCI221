#include <iostream>
#include <cassert>
#include <list>
#include "reversed.hh"

LNode* create_LNode(const int& data,
                    LNode* next){
                      LNode* head = new LNode;
                      head -> data_ = data;
                      head -> next_ = next;
                      return head;
                    }
//////////////////////////////////////////////////////////////////////////////
void print_list(LNode* head)
{
  while (head) {
    std::cout << head->data_ << " ";
    head = head->next_;
  }
  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
// Reverse a list iteratively
void reverse_list(LNode* head)
{
  LNode* prev = NULL;
  LNode* nextptr = NULL;
  while(head){
    nextptr = head->next_;
    head->next_ = prev;
    prev = head;
    head = nextptr;
  }
  head = prev;
}
//////////////////////////////////////////////////////////////////////////////
void push(int integer){
  LNode *temp = new LNode(integer);
  temp->next_ = head;
  head = temp;
}
//////////////////////////////////////////////////////////////////////////////
// Reverse a list recursively
// void reverse_list_r(const LNode* head)
// {
//
//   if (head->next_ == nullptr){
//     int ndata = head->data_;
//     recursively_reversed.push_back(ndata);
//     return recursively_reversed;
//   }else{
//     return reverse_list_r(head->next_);
//   }
// }
