//Welcome to main
#include "node.h"
#include "interacting.h"
#include "minHeap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<Node*> closedSet;
bool finishFound =false;

void movement(Interacting* interaction, Node* cur, Node* temp, minHeap* heap)
{
  //vector<Node*> closedSet;
  double gScore;
  double fScore;
  if (temp != nullptr)
  {
//    cout<<temp->getX()<<" , "<<temp->getY()<<endl;
    gScore = cur->getGscore();
    if (gScore+1 < temp->getGscore())
    {
      temp->setPrev(cur);
      temp->setGscore(gScore+1);
      fScore = gScore+1 + interaction->calcMann(temp->getX(), temp->getY());
      temp->setFscore(fScore);
    }
    if(find(closedSet.begin(), closedSet.end(), temp) == closedSet.end() && temp->getId() != '#')
    {
      heap->add(temp);
      //heap->print(interaction);
      if (temp->getId()=='F')
	finishFound=true;
    }
  }
}

int main(int argc, char* argv[])
{
  Interacting* interaction;
  minHeap* heap = new minHeap();
  string filename; 
  //vector<Node*> closedSet;
  Node* cur;
  vector<vector<Node*>>map;
  int pathLength =0;

  if(argc < 2){
    cerr << "Syntax: ./Euclidean <filename" << endl;
    exit(1);
  }
  filename=argv[1];

  ifstream inFile(filename);

  auto beginning = high_resolution_clock::now();
  if(inFile.is_open()) 		//TODO 		//move to minHeap
  {
    string stringcheese;

    int secondnum;
    int firstnum;
    inFile>>firstnum>>secondnum>>ws;
    cout<<firstnum<<" "<<secondnum<<endl;

    string tempmap [firstnum];
    int x = 0;

    while(getline(inFile, stringcheese)){
      tempmap[x]=stringcheese;
      x++;
    }


    interaction = heap->createMap(firstnum, secondnum, tempmap);
    if (interaction == nullptr)
    {
      return -1;
    }

    Node* start = interaction->getStart();
    start->setGscore(0);
    heap->add(start);
    while(heap->size() != 0)
    {
      cur = heap->min();
      if (interaction->isEnd(cur))
      {
	break;
      }
      closedSet.push_back(cur);
      Node* temp;
      temp = interaction->grabNode(cur->getX()+1,cur->getY());   //right node
      movement(interaction,cur,temp,heap);
      temp = interaction->grabNode(cur->getX()-1,cur->getY());   //left node
      movement(interaction,cur,temp,heap);
      temp = interaction->grabNode(cur->getX(),cur->getY()+1);   //up node
      movement(interaction,cur,temp,heap);
      temp = interaction->grabNode(cur->getX(),cur->getY()-1);   //down node
      movement(interaction,cur,temp,heap);
    }
  }

  else if(!inFile.is_open())
  {
    cout << "Where's the map?? " << filename << endl;
    return -1;
  }
  int count = 0;
  auto endingTime = high_resolution_clock::now();
  while (cur != nullptr){
    if(finishFound==false)
    {
      cout << "*\n*\n*\n*\nMap Unsolvable"<<endl;
      return 1;
    }
    if(cur->getId() == '.')
    {
      cur->setId('*');
	cout << cur->getId() << endl;
      count++;
    }
    cur = cur->getPrev();
  }
  heap->print(interaction);

  auto time = duration_cast<microseconds>(endingTime - beginning); 
  cout << "Time to print map " << time.count() << " microseconds" << endl;
  cout << "Length of shortest path: " << count << endl;
  inFile.close();

  return 0;
}
