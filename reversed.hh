#include <iostream>
#include <cassert>
#include <list>

struct LNode {
  int data_;
  LNode* next_ = nullptr;
};

LNode* creat_node(int data){
    LNode* newnode = new LNode;
    newnode->data_ = data;
    return newnode;
  }


struct linkedlist{
  LNode* head;
  linkedlist() {
    head = NULL;
  }
  LNode* gethead(){
    return head;
  }
  void print_list(){
    while (head) {
      std::cout << head->data_ << " ";
      head = head->next_;
    }
    std::cout << std::endl;
  }


  void reverse_list(){
        LNode* prev = NULL;
        LNode* cur = head;
        LNode* next = head->next_;
        while (next) {
            cur->next_ = prev;
            prev = cur;
            cur = next;
            next = cur->next_;
        }
        cur->next_ = prev;
    // LNode* next = NULL;
    // LNode* prev = NULL;
    // LNode* temp = NULL;
    // temp = head;
    // while(temp != NULL){
    //   next = temp->next_;
    //   std::cout<<next->data_<<"\n";
    //   temp->next_= prev;
    //   prev = temp;
    //   temp = next;
    // }
    // head = prev;
    // std::cout<<head<<"\n";
  }


  void push(int integer){
    LNode* temp = creat_node(integer);
    temp->next_ = head;
    head = temp;
  }

  LNode* reverse_list_r(LNode* node){
    LNode* temp;
    if(node->next_ == NULL){
      head = node;
      return node;
    }else{
      temp = reverse_list_r(node->next_);
    }
    temp->next_ = node;
    return node;
  }

};
