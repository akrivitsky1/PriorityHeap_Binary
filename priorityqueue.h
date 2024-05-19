#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <utility>
#include "json.hpp"

typedef double                  Key;
typedef std::pair<int, int>     Value;
typedef std::pair<Key, Value>   KeyValuePair; 

class PriorityQueue {
  public:
    PriorityQueue(std::size_t max_nodes);
    bool isEmpty() const; //checks if empty
    size_t size() const; //checks size
    Key getKey(size_t i); //gets the key
    void heapifyUp(size_t i); //moves it up the heap
    void heapifyDown(size_t i); //moves it down the heap
    void removeNode(size_t i);
    KeyValuePair min(); //gives min
    KeyValuePair removeMin(); //removes min
    void insert(Key k); //insert a key value
    void insert(KeyValuePair kv);
    nlohmann::json JSON() const;

  private:
    std::vector<KeyValuePair>   nodes_;
    size_t                      max_size_;
    size_t                      size_;
    const static size_t         ROOT = 1;
};  // class PriorityQueue

#endif  // _PRIORITYQUEUE_H_
