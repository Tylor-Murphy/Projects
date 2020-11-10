#pragma once
#include <iostream>
using std::cout;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::ostringstream;
// DO NOT MODIFY
//
// Node
//
struct Node {
  string key{};
  int value{};
  Node *next = nullptr;
  Node *prev = nullptr;
  Node() = default;
  Node(string, int, Node * = nullptr, Node * = nullptr);
  bool operator==(const Node &) const;
  friend ostream &operator<<(ostream &out, const Node &n) {
    out << n.key << ":" << n.value;
    return out;
  }
};

Node::Node(string key_, int value_, Node *prev_, Node *next_) {
  key = key_;
  value = value_;
  prev = prev_;
  next = next_;
}

bool Node::operator==(const Node &n) const {
  if ((key == n.key) && (value == n.value)) {
    return true;
  } else {
    return false;
  }
}

// DO NOT MODIFY
//
// DLL
//
class DLL {
private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_t sz_ = 0;

public:
  DLL() = default;
  DLL(vector<Node>);
  DLL(const DLL &);
  DLL &operator=(DLL list);
  ~DLL();
  Node *get_head();
  Node *get_tail();
  size_t get_size();
  Node add_back(string, int);
  Node add_front(string, int);
  Node add_after(string, string, int);
  Node search(string);
  Node remove_front();
  Node remove_back();
  Node remove_key(string);
  int update_value(string, int);
  friend ostream &operator<<(ostream &out, const DLL &list) {
    auto itr = list.head_;
    ostringstream oss;
    for (; itr != nullptr; itr = itr->next) {
      oss << itr->key << ":" << itr->value << ", ";
    }
    string ans = oss.str();
    ans = ans.substr(0, ans.size() - 2);
    out << ans;
    return out;
  }
};

Node *DLL::get_head() { return head_; }
Node *DLL::get_tail() { return tail_; }
size_t DLL::get_size() { return sz_; }

DLL::~DLL() {
  while (head_)
    delete std::exchange(head_, head_->next);
}

DLL & DLL::operator =(DLL list) {
  using std::swap;
  swap(head_,list.head_);
  swap(tail_,list.tail_);
  swap(sz_,list.sz_);
  return *this;
}

DLL::DLL(const DLL &list) {
  for (Node *p = list.head_; p; p = p->next)
    add_back(p->key, p->value);
}

DLL::DLL(vector<Node> vec) {
  for (const auto &node : vec)
    add_back(node.key, node.value);
}

/* BEGIN MODIFICATION BELOW */

// adds to back of list
Node DLL::add_back(string str, int num) {
  // making new node
  Node *new_node = new Node(str, num);
  // Case 1 (1 thing in list)
  if(tail_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  }
  // Case 2(more than 1 thing in list)
  else if(tail_ != nullptr) {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  }
  //increase size
  sz_++;
  // return node added to back
  return *new_node;
}

// adds to front of list
Node DLL::add_front(string str, int num) {
    // Make new node
    Node *new_node = new Node(str, num);
    // 1 thing in list
    if(head_ == nullptr) {
        head_ = new_node;
        tail_ = new_node;
    }
    // mutliple things in list
    else if(tail_ != nullptr) {
        head_->prev = new_node;
        new_node->next = head_;
        head_ = new_node;
    }
    //increase size
    sz_++;
    //return node added to front
    return *new_node;
}

// adds node after a specified location
Node DLL::add_after(string add_key, string str, int num) {
    // make new node
    Node* new_node = new Node(str, num);
    bool treasure_key = false;
    for(auto it = head_; it != nullptr; it = it->next) {
        if(it->key == add_key) {
            if(it == tail_) {
                it->next = new_node;
                new_node->prev = it;
                tail_ = new_node;
                sz_++;
            }
            else {
                auto it_next = it->next;
                it_next->prev = new_node;
                it->next = new_node;
                new_node->next = it_next;
                new_node->prev = it;
                sz_++;
            }
        treasure_key = true;
        }
    }
    if(treasure_key) {
        return *new_node;
    }
    else{
        Node *empty_node = new Node("", 0);
        return *empty_node;
    }
    
}
// removes node from back of list
Node DLL::remove_back() {
    // see if list is empty
    if(tail_ == nullptr && head_ == nullptr) {
        Node *empty_node = new Node("", 0);
        return *empty_node;
    }
    // only 1 node
    else if(tail_ == head_) {
        auto remove_bck = tail_;
        head_ = nullptr;
        tail_ = nullptr;
        sz_--;
        return *remove_bck;
    }
    // multiple nodes
    else{
        auto remove_bck = tail_;
        tail_->prev->next = nullptr;
        tail_ = tail_->prev;
        sz_--;
        return *remove_bck;
    }
}

// removes node from front of list
Node DLL::remove_front() {
    // empty
    if(tail_ == nullptr && head_ == nullptr) {
        Node *empty_node = new Node("", 0);
        return *empty_node;
    }
    // 1 node
    else if(tail_ == head_) {
        auto remove_frnt = tail_;
        head_ = nullptr;
        tail_ = nullptr;
        sz_--;
        return *remove_frnt;
    }
    // mutiple nodes
    else{
        auto remove_frnt = head_;
        head_->next->prev = nullptr;
        head_ = head_->next;
        sz_--;
        return *remove_frnt;
    }
}

// find a remove a node throughout the list
Node DLL::remove_key(string to_remove) {
    auto *remove_ky = new Node("", 0);
    bool treasure_key = false;
    for(auto it = head_; it != nullptr; it = it->next) {
        if(it->key == to_remove){
            if(it == tail_) {
                it->prev->next = nullptr;
                tail_ = it->prev;
            }
            else if(it == head_) {
                it->next->prev = nullptr;
                head_ = it->next;
            }
            else{
                it->prev->next = it->next;
                it->next->prev = it->prev;
            }
        treasure_key = true;
        sz_--;
        remove_ky = it;
        return *remove_ky;
        }
    }
    if(treasure_key) {
        return *remove_ky;
    }
    else{
        Node *empty_node = new Node("", 0);
        return *empty_node;
    }
    
}
// searches for a key in the list
Node DLL::search(string find_key) {
    Node *found_treasure = new Node("", 0);
    for(auto it = head_; it != nullptr; it = it->next) {
        if(it->key == find_key) {
            found_treasure = it;
        }
    }
    return *found_treasure;
}


// undates value with the associated key given
int DLL::update_value(string find_key, int new_value) {
    bool treasure_key = false;
    for(auto it = head_; it != nullptr; it = it->next) {
        if(it->key == find_key) {
            it->value = new_value;
            treasure_key = true;
        }
    }
    if(treasure_key) {
        return new_value;
    }
    else {
        return -1;
    }

}
