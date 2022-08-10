//welcome to the minhead
#include "minHeap.h"
#include "interacting.h"
#include <vector>
#include <map>

using namespace std;

minHeap::minHeap()
{
  //m_foundFinish=false;
  m_array.push_back(nullptr);
}

//minHeap::~minHeap()
//{

//}
Interacting* minHeap:: createMap(int height, int width, string tempmap [])
{
  Node* temp;
  Interacting* grabber = new Interacting();
  int start_X;
  int start_Y;
  int finish_X;
  int finish_Y;

  bool foundStart=false;
  bool foundFinish=false;
  bool moreThanOne=false;

  vector<vector<Node*>> map;
    for(int i=0; i<width; ++i){
    //for(int i=0; i<height; ++i){ 

      vector<Node*> lines;
      for(int j=0;j<height; ++j){
      //for(int j=0;j<width; ++j){ 
        temp = new Node;
        temp->setX(i);
        temp->setY(j);

        cout<<tempmap[i].substr(j,1);
	temp->setId(tempmap[i][j]);

         if(temp->id_m == 'S' && foundStart ==false)
          {
	     foundStart=true;
             start_X = temp->x_m;
             start_Y = temp->y_m;
	     grabber->setStart(start_X,start_Y);
          }
	 else if(temp->id_m == 'S' && foundStart ==true)
	 {
	   moreThanOne=true;
	 }
         if(temp->id_m == 'F' && foundFinish==false)
         {
	   foundFinish=true;
           finish_X = temp->x_m;
           finish_Y = temp->y_m;
	   grabber->setFinish(finish_X, finish_Y);
         }
	 else if(temp->id_m == 'F' && foundFinish==true)
	 {
	   moreThanOne=true;
	 }

        lines.push_back(temp);
      }
      map.push_back(lines);
      cout<<endl;
    }
    
    
    if (moreThanOne==false && foundStart == true && foundFinish==true)
    {
      cout << "Start coordinates: (" << start_X << ", " << start_Y << ")" <<endl;

      int obstCount=0;
     // if (start_X+1 =< height)
      if(start_X+1 < width)
      {
	temp = map[start_X+1][start_Y];
	if (temp->getId()=='#')
	  obstCount++;
      }

      if (start_X-1 >=0)
      {
	temp = map[start_X-1][start_Y];
	if (temp->getId()=='#')
	  obstCount++;
      }

      //if (start_Y+1 <= width-1)
      if(start_Y+1 <= height-1)
      {
	temp= map[start_X][start_Y+1];
	if (temp->getId()=='#')
	  obstCount++;
      }

      if (start_Y-1 >=0)
      {
	temp = map[start_X][start_Y-1];
	if (temp->getId()=='#')
	  obstCount++;
      }

      cout << "\tObstacles: " << obstCount << endl;
      cout << "Finish coordinates: (" << finish_X << ", " << finish_Y << ")" << endl;

      obstCount=0;
      //if (finish_X+1 <= height-1)
	if (finish_X+1 <= width-1)
      {
	temp = map[finish_X+1][finish_Y];
	if (temp->getId()=='#')
	  obstCount++;
      }

      if (finish_X-1 >=0)
      {
	temp = map[finish_X-1][finish_Y];
	if (temp->getId()=='#')
	  obstCount++;
      }

      //if (finish_Y+1 <= width-1)
	if (finish_Y+1 <= height-1)
      {
	temp= map[finish_X][finish_Y+1];
	if (temp->getId()=='#')
	  obstCount++;
      }

      if (finish_Y-1 >=0)
      {
	temp = map[finish_X][finish_Y-1];
	if (temp->getId()=='#')
	  obstCount++;
      }

      cout << "\tObstacles: " << obstCount << endl;

      grabber->setMap(map);
      return grabber;
    }
    else if (foundStart == false)
    {
      cout<<"Please add a starting point and try again"<<endl;
    }
    else if (foundFinish == false)
    {
      cout<<"Please add an ending point and try again"<<endl;
    }
    else
    {
      cout<<"Too many start or end points. Please edit your map and try again"<<endl;
    }
    return nullptr;
}
map<pair <int,int>,bool> setChecker;
void minHeap::add(Node*n)
{
  int pos = m_array.size();
  pair<int,int>coords = make_pair(n->getX(), n->getY());

  if(setChecker[coords] == true)
    return;

  setChecker[coords]=true;
  m_array.push_back(n);
  while(pos > 1 && m_array[pos/2]->fscore_m > n->fscore_m)
  {
    m_array[pos] = m_array[pos/2];
    m_array[pos/2] = n;
    pos = pos/2;
  }
}

Node* minHeap::min()
{
  if(m_array.size() < 2)
  {
    return NULL;
  }

  Node* min_Val = m_array[1];

  m_array[1] = m_array[m_array.size() - 1];
  m_array.resize(m_array.size() - 1);
  int pos = 1;
  int lchild = pos * 2;
  int rchild = pos * 2 + 1;
  while(lchild < m_array.size()) //check for accuracy, needs testing 
  {
    Node* cur = m_array[pos];

    if(m_array[lchild]->fscore_m > m_array[rchild]->fscore_m)
    {
      if(m_array[rchild]->fscore_m > m_array[pos]->fscore_m)
	break;

      m_array[pos] = m_array[rchild];
      m_array[rchild] = cur;
      pos = rchild;
    }
    else
    {
      if(m_array[lchild]->fscore_m > m_array[pos]->fscore_m)
	break;

      m_array[pos] = m_array[lchild];
      m_array[lchild] = cur;
      pos = lchild;

    }
  lchild = pos * 2;
  rchild = pos * 2 + 1;

  }



  return min_Val;
}



void minHeap::print(Interacting* interacting) const
{
  vector<vector<Node*>>map;
  map = interacting->getMap();
  for(vector<Node*> temp:map)
  {
    for(Node* nodes:temp)
    {
      cout<<nodes->getId();
    }
    cout<<endl;
  }
}

int minHeap::size() const
{
  return m_array.size() - 1; 
}

/*bool minHeap::finishFound()
{
  return m_foundFinish;
}*/
