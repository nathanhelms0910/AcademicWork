// Header file for avl tree

#ifndef AVL_H
#define AVL_H

#include <QObject>
#include <QWidget>
#include <QRgb>
#include <QString>
#include <QFileDialog>
#include <QColor>

#include "node.h"

class Avl
{
  public:
    Avl();
    Avl(Node* root);
    
    // Wrapper functions
    void insert(QRgb key);
    void remove(QRgb key);
    Node* find(QRgb key);
    void print(QImage& image);

    ~Avl();
      //edited by Trenton on 09/30/20

    // Remove's helper function
    Node* min (Node* const cur) const;
    
    // AVL Tree Functions
    void insert (Node*& cur, QRgb key);
    void remove(Node*& cur, const QRgb key);
    Node* find(Node* cur, QRgb key);
    void print(Node* cur, QImage& image);
    
    // Height/Root Accessor/Mutators
    int height();
    void set_height(int height);
    Node*& root();
    void set_root(Node* root);

    // Our balancing function
    void appease_the_trees(Node*& cur, QRgb key); 

    // Rotations
    void right_single_rotation(Node*& gparent);
    void left_single_rotation(Node*& gparent);
    void right_left_double_rotation(Node*& gparent);
    void left_right_double_rotation(Node*& gparent);

    // For Debugging, marmorstein's code
    void debug() const;
    void debug(Node* cur) const;

    // Helper function
    static int max(const int a, const int b)
    {
      return a >= b ? a : b;
    }

    // Helper function
    static int height(Node* n)
    {
      if (n == nullptr)
        return 0;
      return n->height();
    }
    
  private:
    Node* m_root;
    int m_height;
};

#endif // AVL_H
