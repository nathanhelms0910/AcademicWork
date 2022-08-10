// Header file for node

#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QList>
#include <QPoint>

class Node
{
  public:
    Node();
    Node(QRgb key);
    ~Node();

    // Left and right subtree nodes 
    Node* m_left;
    Node* m_right;

    // Returns/Sets height of this node
    int height();
    void set_height(int depth);

    // Returns/Sets rgb color of this node
    QRgb key();
    void set_key(QRgb key);

    // Returns/Sets list of pixel locations
    QList<QPoint> pixels();
    void set_pixel_list(QList<QPoint> pixel_list);

    // Adds pixel to the list;
    void add_pixel(QPoint pixel_location);

    QList<QPoint>& the_overseer();

  private:
    QRgb m_key;
    QList<QPoint> m_pixel_list;
    int m_height;
};

#endif // NODE_H
