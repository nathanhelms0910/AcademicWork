//This part of the project will interpret the map and start to solve the map

#include <vector>
#include <cmath>
#include "interacting.h"
#include "node.h"
#include "minHeap.h"

//Euclidean Distance:  sqrt(pow(x2-x1,2)+pow(y2-y1,2))
//Manhattan Distance:  abs(x2-x1)+abs(y2-y1)

Interacting::Interacting()
{
  map_m;                            //FIXME                 //CHANGE ME WITH WHAT MAP WE GET FROM INTERACTING 
  eucl_m = -8;
  mann_m = -8;
  finishCoords_m[0] = 1000;
  finishCoords_m[1] = 1000;
  startCoords_m[0] = 1000;
  startCoords_m[1] = 1000;
  maxWidth = 1000;
  maxHeight = 1000;
}

Interacting::~Interacting()
{
}

vector<vector<Node*>> Interacting::getMap()
{
  return map_m;
}

bool Interacting::isValid(Node* next)
{
  if (next->getId() == '#')
    return false;
  return true;
}

/* Morgan Magner 11/10/2020
 * this function should be able to run a compare of all of the avaliable directions of our "current" node.
 * It will return the node with the smallest Hscore. If it returns nullptr, we need to backtrack a little.
 * (If this is our first node or all options have been searched, this will tell us that it can't be solved).
 * It will also have the fun bonus point where if it is the first compare we are doing, it will add the 
 * node to the openSet to ensure that our starting point keeps it full.
*/

Node* Interacting::Compare(Node* current)           //TODO            //This function is still a work in progress. Will need to check against open and closed sets!!
{
/*  Node* tmp = nullptr;
  Node* tempNext = nullptr;
  if (tempNext == nullptr)
  {
    tempNext = current;
    //openSet.push_back(current);
  }
  else
  {
    Node* directions[4] = {current->getUp(),current->getDown(),current->getLeft(),current->getRight()};
    for (int i =0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
	if (directions[i] == nullptr)
	  break;
	if (directions[j] == nullptr)
	  j++;
	else if (tmp == nullptr)
	  tmp = directions[i];
	else if (HScore(directions[i]) < HScore(directions[j]))
	  tmp = directions[i];
	else
	  tmp = directions[j];
      }
    }
  }
  return tmp;
  */
}

Node* Interacting::grabNode(int x, int y)
{
//  if (x < 0 || x>=maxWidth)
  if(y < 0 || y >= maxWidth)
    return nullptr;
  //else if (y<0 || y>=maxHeight)
  else if(x < 0 || x >= maxHeight)
    return nullptr;
  Node* current = map_m[x][y];
  return current;
}

Node* Interacting::getStart()
{
  Node* returnMe = map_m[startCoords_m[0]][startCoords_m[1]];
  return returnMe;
}

Node* Interacting::getEnd()
{
  Node* returnMe = map_m[finishCoords_m[0]][finishCoords_m[1]];
  return returnMe;
}

void Interacting::setFinish(int numX, int numY)
{
  finishCoords_m[0] = numX;
  finishCoords_m[1] = numY;
}
void Interacting::setStart(int numX, int numY)
{
  startCoords_m[0] = numX;
  startCoords_m[1] = numY;
}

void Interacting::setMap(vector<vector<Node*>> setMe)
{
  for (vector<Node*> vecNode : setMe)
  {
    map_m.push_back(vecNode);
    maxWidth = vecNode.size();
  }
  maxHeight = map_m.size();
}

bool Interacting::isEnd(Node* cur)
{
  if (cur->getX() == finishCoords_m[0] && cur->getY() == finishCoords_m[1])
    return true;
  return false;
}

double Interacting::calcEucl(int nodesX, int nodesY)
{
  eucl_m = sqrt(pow(finishCoords_m[0]-nodesX,2)+pow(finishCoords_m[1]-nodesY,2));
  return eucl_m;
}

double Interacting::calcMann(int nodesX, int nodesY)
{
  mann_m = abs(finishCoords_m[0]-nodesX)+abs(finishCoords_m[1]-nodesY);
  return mann_m;
}
