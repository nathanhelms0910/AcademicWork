//This is our node friend. Everyone say hello to Mr.Node
//hello Mr. Node
#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node{
  public:
    Node();
    ~Node();
    void setGscore(double hello);
    double getGscore();
    void setFscore(double hello);
    double getFscore();
    //double getHscore(int finishsX, int finishsY);
    void setX(int hello);
    int getX();
    void setY(int hello);
    int getY();
    void setId(char hello);
    char getId();
    Node* getPrev();
    void setPrev(Node* temp);
    char id_m;
    int x_m;
    int y_m;
    double fscore_m;
  private:
    double gscore_m;
    Node* previous_m;
};

#endif
