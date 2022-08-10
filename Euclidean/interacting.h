#ifndef INTERACTING_H
#define INTERACTING_H

//This part of the project will interpret the map and start to solve the mapi
#include <vector>
#include "node.h"
#include <iostream>

class Interacting
{
  public:
    Interacting();
    ~Interacting();
    //double FScore(Node* current);
    Node* Compare(Node* current);
    Node* grabNode(int x, int y);
    Node* getStart();
    Node* getEnd();
    vector<vector<Node*>> getMap();
    bool moveForward(Node* current);
    bool isValid(Node* current);
    bool isEnd(Node* cur);
    //void movement(Node* current);
    //void aStar();
    void setMap(vector<vector<Node*>> setMe);
    void setFinish(int num1, int num2);
    void setStart(int num1, int num2);
    double calcEucl(int nodesX, int nodesY);
    double calcMann(int nodesX, int nodesY);
  protected:

  private:
    std::vector<vector<Node*>> map_m;
    double eucl_m;
    double mann_m;
    int finishCoords_m[2];
    int startCoords_m[2];
    int maxWidth;
    int maxHeight;
};

#endif
