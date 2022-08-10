// Implementation file for avl tree
#include <iostream>
#include <QColor>
#include "avl.h"
Avl::Avl() : m_root{nullptr}, m_height{0}
{}

Avl::~Avl()
{
    delete m_root;
}

Avl::Avl(Node* root) : m_root{root}, m_height{1}
{}

//This is the code for the balancing function. It appeases the trees by making sure it stays a good BST. It should be called every time there is an insertion or a remove. If not, we have big problems
void Avl::appease_the_trees(Node*& cur, QRgb key)
{ //Morgan Magner 09/30/2020
  int max_height = max(height(cur->m_left), height(cur->m_right));
  cur->set_height(max_height+1);
  if (height(cur->m_left) - height(cur->m_right) > 1)
  {
    Node* left = cur->m_left;
    Node* left_gchild = left->m_left;
    Node* right_gchild = left->m_right;

    if (height(left_gchild) > height(right_gchild))
    {
      right_single_rotation(cur);
    }
    else
    {
      left_right_double_rotation(cur);
    }
  }
  else if (height(cur->m_right) - height(cur->m_left) > 1)
  {
    Node* right = cur->m_right;
    Node* right_gchild = right->m_right;
    Node* left_gchild = right->m_left;

    if (height(right_gchild) > height(left_gchild))
    {
      left_single_rotation(cur);
    }
    else
    {
      right_left_double_rotation(cur);
    }
  }
}

// Wrapper function for insert
void Avl::insert(QRgb key)
{
  insert(m_root, key);
}

// Wrapper function for remove 
void Avl::remove(QRgb key)
{
  if (m_root == nullptr)
    return;

  remove(m_root, key);
}

// Wrapper function for find 
Node* Avl::find(QRgb key)
{
  if (m_root == nullptr)
    return nullptr;

  return find(m_root, key);
}

// Wrapper function for print 
void Avl::print(QImage& image)
{
  if (m_root == nullptr)
    return;
  for(int y = 0; y < image.height(); ++y)
  {
    for(int x = 0; x < image.width(); ++x)
    {
      if(find(image.pixel(x,y)) == nullptr)
      {
	image.setPixel(x,y,QColor(Qt::white).rgb());
      }
    }
  }
  print(m_root, image);
}

// For debugging, marmorstein's code
void Avl::debug() const
{
	std::cout << "digraph tree {" << std::endl;
	std::cout << "\tgraph [truecolor = true, bgcolor = \"transparent\" ];" << std::endl;
	debug(m_root);
	std::cout << "}" << std::endl;
}

// For debugging, marmorstein's code
void Avl::debug(Node* cur) const
{
	if (!cur) return;
	std::cout << "\t" << "node" << cur->key() << " " << "[ label = \"" << cur->key()  << " [" << cur->height() << "]\", fillcolor = blue, color = black, style = filled, fontcolor = white, fontsize = 24 ];" << std::endl;
	if (cur->m_left) {
		debug(cur->m_left);
		std::cout << "\tnode" << cur->key() << " -> " << "node" << cur->m_left->key() << "[ K = 0.1 ];" << std::endl;
	}
	else {
		std::cout << "left_null" << cur->key() << " [label=\"\", shape = none ];" << std::endl;
		std::cout << "\tnode" << cur->key() << " -> " << "left_null" << cur->key() << "[arrowhead = tee];" << std::endl;
	}

	if (cur->m_right) {
		debug(cur->m_right);
		std::cout << "\tnode" << cur->key() << " -> " << "node" << cur->m_right->key() << "[ K = 0.1 ];" << std::endl;
	}
	else {
		std::cout << "right_null" << cur->key() << " [label=\"\", shape = none ];" << std::endl;
		std::cout << "\tnode" << cur->key() << " -> " << "right_null" << cur->key() << "[arrowhead = tee];" << std::endl;
	}
}

void Avl::insert(Node*& cur, QRgb key)
{
  Node* n = new Node(key);

  if(cur == nullptr)
  {
    cur = n;
    return;
  }
  
  else if (key <= cur->key())
  {
    insert(cur->m_left,key);
  }
  else
  {
    insert(cur->m_right,key);
  }

  appease_the_trees(cur, key);
}

//This min function really is a funky boi. His only reason to exist is to help the ACTUAL remove function...
Node* Avl::min(Node* const cur) const
{
  if (cur == nullptr)
    return nullptr;
  else if (cur->m_left == nullptr)
    return cur;
  return min(cur->m_left);
}

//The actual meat and potatoes of removing nodes from the program
void Avl::remove(Node*& cur, const QRgb key)
{
  Node* temp = new Node;
  if (cur == nullptr)
    return;

  // Searching for the node
  else if(key < cur->key())
    remove(cur->m_left, key);

  else if(key > cur->key())
    remove(cur->m_right, key);

  else 
  {

    // Node has two children
    if (cur->m_left != nullptr && cur->m_right != nullptr)
    {
      // Find left-most node of right subtree
      temp = min(cur->m_right);
      
      // Transfer key and pixel list from temp to cur
      cur->set_key(temp->key()); 
      cur->set_pixel_list(temp->pixels());

      // Remove left-most node of right subtree
      remove(cur->m_right, temp->key());

     // delete temp;
    }
    
    // Node has no children
    else if (cur->m_left == nullptr && cur->m_right == nullptr)
    {
      cur->pixels().clear();
      delete cur;
      cur = nullptr;
    }
    
    // Node has one child
    else
    {
      if (cur->m_right == nullptr)
        cur = cur->m_left;
      else
        cur = cur->m_right;
    }

    if (cur == nullptr)
      return;
  }
}

// Print the tree
void Avl::print(Node* cur, QImage& image)
{
  // Sets every pixel on tree's image to its proper color
  for (int i = 0; i < cur->pixels().size(); ++i)
    image.setPixel(cur->pixels()[i], cur->key());

  if (cur->m_left != nullptr)
    print(cur->m_left, image);

  if (cur->m_right != nullptr)
    print(cur->m_right, image);
}

// Returns height of tree
int Avl::height()
{
  return m_height;
}

// Sets height of the tree
void Avl::set_height(int height)
{
  m_height = height;
}

// Returns tree's root node
Node*& Avl::root()
{
  return m_root;
}

// Sets root node of this tree
void Avl::set_root(Node* root)
{
  m_root = root;
}

// Search for node in tree with rgb key
Node* Avl::find(Node* cur, QRgb key)
{
  //added by Trenton Taylor on 09/29/20
  if(cur == nullptr || cur->key() == key)
  {
    return cur;
  }

  if(key < cur -> key())
  {
    return find(cur->m_left, key);
  }

  return find(cur->m_right, key);
}

void Avl::right_single_rotation(Node*& gparent)
{ //Morgan Magneer 09/30/2020
  Node* left = gparent->m_left;
  Node* tmp = left->m_right;
  left->m_right = gparent;
  gparent->m_left = tmp;


  int maxheight;

  maxheight = max(height(gparent->m_right), height(gparent->m_left));
  gparent->set_height(maxheight + 1);

  maxheight = max(height(left->m_left), height(left->m_right));
  left->set_height(maxheight + 1);


  gparent = left;
  
}

void Avl::left_single_rotation(Node*& gparent)
{
  //added by Trenton Taylor on 09/30/20
Node* right = gparent->m_right;
Node* tmp = right->m_left;
right->m_left = gparent;
gparent->m_right = tmp;


int maxheight;

maxheight = max(height(gparent->m_left), height(gparent->m_right));
gparent->set_height(maxheight + 1);

maxheight = max(height(right->m_left), height(right->m_right));
right->set_height(maxheight + 1);

gparent = right;

}

void Avl::right_left_double_rotation(Node*& gparent)
{ //Morgan Magner 09/30/2020
  Node* right = gparent->m_right;
  Node* RR = right->m_left;

  Node* tmp = RR->m_left;

  right->m_left = RR->m_right;
  RR->m_right = right;
  RR->m_left = gparent;

  gparent->m_right = tmp;

  int maxheight;

  maxheight = max(height(gparent->m_right), height(gparent->m_left));
  gparent->set_height(maxheight + 1);

  maxheight = max(height(right->m_right), height(right->m_left));
  right->set_height(maxheight + 1);

  maxheight = max(height(RR->m_right), height(RR->m_left));
  RR->set_height(maxheight + 1);
  gparent = RR;
}

void Avl::left_right_double_rotation(Node*& gparent)
{
Node* left = gparent->m_left;
Node* LR = left->m_right;

Node* tmp = LR->m_right;

left->m_right = LR->m_left;

LR->m_left = left;
LR->m_right = gparent;

gparent->m_left = tmp;
int maxheight;

maxheight = max(height(gparent->m_left), height(gparent->m_right));
gparent->set_height(maxheight + 1);

maxheight = max(height(left->m_left), height(left->m_right));
left->set_height(maxheight + 1);

maxheight = max(height(LR->m_left), height(LR->m_right));
LR->set_height(maxheight + 1);
gparent = LR;
}
