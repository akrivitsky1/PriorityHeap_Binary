#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size): //constructor making the queue
    nodes_(max_size + 1, KeyValuePair()),
    max_size_(max_size),
    size_(0) {}

void PriorityQueue::insert(Key k) { //insert pair of keys
    insert(std::make_pair(k, std::make_pair(0, 0))); //base pair of 0,0
}

void PriorityQueue::insert(KeyValuePair kv) { //inserts in heap
    if (size_ == max_size_) { //cannot be greater than max size
        std::cerr << "Error: priority queue is full" << std::endl; //error message
        return;
    }
    nodes_[++size_] = kv; //add one more node
    heapifyUp(size_); //heapify it up
}

KeyValuePair PriorityQueue::min() { //gives back min
    if (isEmpty()) {
        std::cerr << "Error: priority queue is empty" << std::endl;
        return KeyValuePair();
    }
    return nodes_[ROOT]; //returns nodes root
}

KeyValuePair PriorityQueue::removeMin() { //remove Min
    if (isEmpty()) { //no heap elements
        std::cerr << "Error: priority queue is empty" << std::endl;
        return KeyValuePair();
    }
    KeyValuePair min_node = nodes_[ROOT]; //need min node pair
    removeNode(ROOT); //removes node pair
    return min_node; //returns min_node
}

bool PriorityQueue::isEmpty() const { //if size is 0 return true
    return size_ == 0;
}

size_t PriorityQueue::size() const { //return size
    return size_;
}
nlohmann::json PriorityQueue::JSON() const {
nlohmann::json result;
for (size_t i = 1; i <= size_; i++) {
nlohmann::json node;
KeyValuePair kv = nodes_[i];
node["key"] = kv.first;
node["value"] = kv.second;
if (i != ROOT) {
node["parent"] = std::to_string(i / 2);
}
if (2 * i <= size_) {
node["leftChild"] = std::to_string(2 * i);
}
if (2 * i + 1 <= size_) {
node["rightChild"] = std::to_string(2 * i + 1);
}
result[std::to_string(i)] = node;
}
result["metadata"]["max_size"] = max_size_;
result["metadata"]["size"] = size_;
return result;
}

void PriorityQueue::heapifyUp(size_t i) { 
    if (i == ROOT) return; //if i is root
    size_t parent_index = i / 2; //parent_index is now half of i
    if (getKey(i) < getKey(parent_index)) { //if less than parent index
        std::swap(nodes_[i], nodes_[parent_index]); //swap the nodes
        heapifyUp(parent_index); //recursively do it
    }
}
void PriorityQueue::heapifyDown(size_t i) { //heapifying down
    size_t leftChild = 2 * i; //if left child is 2 * index i
    size_t rightChild = 2 * i + 1; //right child 2 * i +1
    size_t smallest = i; //smallest i

if (leftChild <= size_ && nodes_[leftChild].first < nodes_[i].first) { //left child less than current node
    smallest = leftChild; //smallest is left child
}

if (rightChild <= size_ && nodes_[rightChild].first < nodes_[smallest].first) { //right child is less than current node
    smallest = rightChild; //smallest is right child
}

if (smallest != i) { //swap the current node with what is smaller 
    std::swap(nodes_[i], nodes_[smallest]);
    heapifyDown(smallest); //recursively calls it
}
}

void PriorityQueue::removeNode(size_t i) { //removes the most recent node
    nodes_[i] = nodes_[size_];
    size_--;
    heapifyDown(i);
}

Key PriorityQueue::getKey(size_t i) { //gets the key at a node
    return nodes_[i].first;
}