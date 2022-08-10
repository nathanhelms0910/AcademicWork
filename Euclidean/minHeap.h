//this is our heap
#ifndef MINHEAP_H
#define MINHEAP_H

#include "node.h"
#include "interacting.h"
#include <vector>
#include <iostream>
class minHeap {
  private: 
    std::vector<Node*> m_array;
    bool m_foundFinish;
  public:
    minHeap();
    Interacting* createMap(int num1, int num2, string tempmap[]);
    void add(Node* n);
    Node* min();
    void print(Interacting* interaction) const;
    int size() const;
    bool finishFound();
};

#endif
