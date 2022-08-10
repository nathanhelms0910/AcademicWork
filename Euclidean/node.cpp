//This is our node friend. Everyone say hello to Mr.Node
#include "node.h"
#include <string>
using namespace std;

Node:: Node(){
  x_m = 888;
  y_m = 888;
  gscore_m = 888.88;
  fscore_m = 888.88;
  id_m = 'x';
  previous_m = nullptr;
}
Node:: ~Node()
{
  delete previous_m;
}

void Node::setGscore(double hello)
{
  gscore_m=hello;
}

double Node::getGscore()
{
  return gscore_m;
}

void Node::setFscore(double hello)
{
  fscore_m=hello;
}

double Node::getFscore()
{
  return fscore_m;
}

/*double Node::getHscore(int finishsX, int finishsY)
{
  eucl_m = sqrt(pow(finishsX-x_m,2)+pow(finishsY-y_m,2));
}*/

void Node::setX(int hello)
{
  x_m=hello;
}

int Node::getX()
{
  return x_m;
}

void Node::setY(int hello)
{
  y_m=hello;
}

int Node::getY()
{
  return y_m;
}

void Node::setId(char hello)
{
 id_m=hello;
}

char Node::getId()
{
  return id_m;
}

Node* Node::getPrev()
{
  return previous_m;
}

void Node::setPrev(Node* temp)
{
  previous_m=temp;
}
