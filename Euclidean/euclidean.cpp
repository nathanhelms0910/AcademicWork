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
#include <sys/time.h>
#include <sys/resource.h>
#include <numeric>
using namespace std;
using namespace std::chrono;

vector<Node*> closedSet;
bool finishFound = false;
vector<int> timesmadeez;

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
      fScore = gScore+1 + interaction->calcEucl(temp->getX(), temp->getY());
      temp->setFscore(fScore);
    }
    if(find(closedSet.begin(), closedSet.end(), temp) == closedSet.end() && temp->getId() != '#')
    {
      heap->add(temp);
      ///////////////////////////////////////////////////////////////////////////
      if(temp->getId() == 'F')
	finishFound=true;
      //heap->print(interaction);
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
  struct rusage usage;
  struct timeval start, end;

  if(argc < 2){
    cerr << "Syntax: ./Euclidean <filename" << endl;
    exit(1);
  }
filename=argv[1];

ifstream inFile(filename);
auto beginning = high_resolution_clock::now();
getrusage(RUSAGE_SELF, &usage);
start = usage.ru_utime;
  
if(inFile.is_open()) 		//TODO 		//move to minHeap
  {
    string stringcheese;

    int secondnum;
    int firstnum;

    inFile>>firstnum>>secondnum>>ws;
    //inFile>>secondnum>>firstnum>>ws;

    cout<<firstnum<<" "<<secondnum<<endl;

    string tempmap [firstnum];
    int x = 0;

    while(getline(inFile, stringcheese)){
      tempmap[x]=stringcheese;
      x++;
    }


    interaction = heap->createMap(firstnum, secondnum, tempmap);
    //interaction = heap->createMap(secondnum, firstnum, tempmap);
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

    if (finishFound== false)
    {
      cout << "*\n*\n*\n*\nMap Unsolvable"<<endl;
      return -1;
    }


    if(cur->getId() == '.')
    {
      cur->setId('*');
      //cout<<cur->getPrev()->getId()<<endl;
      cout << cur->getId() << endl;
      count++;
    }
    // cout << "HELP ME" << endl;


    //cur->setId('*');

    cur = cur->getPrev();
  }
  heap->print(interaction);

  // auto time = duration_cast<microseconds>(endingTime - beginning); 
  getrusage(RUSAGE_SELF, &usage);
  end = usage.ru_utime;
  int time_count = end.tv_usec - start.tv_sec;
  timesmadeez.push_back(time_count);
  float average = accumulate( timesmadeez.begin(), timesmadeez.end(), 0.0/timesmadeez.size());
  cout << "Time to print map " << time_count << " microseconds" << endl;
  cout << "Length of shortest path: " << count << endl;
  

 /* ofstream file_Time;

  file_Time.open("time.txt");
  if(file_Time.is_open()){
    file_Time << time_count << endl;
  }
  file_Time.close();*/
  inFile.close();

  return 0;
}
