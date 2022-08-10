// Implementation file for node

#include "node.h"
#include <iostream>

Node::Node(): m_left{nullptr}, m_right{nullptr}, m_key{0}, m_height{0}  
{
  m_pixel_list = QList<QPoint>();
}

Node::Node(QRgb key) : m_left{nullptr}, m_right{nullptr}, m_key{key}, m_height{0}
{
}

Node::~Node()
{
  m_pixel_list.clear();
  if (m_right)
    delete m_right;
  if (m_left)
    delete m_left;
}

int Node::height()
{
  return m_height;
}

void Node::set_height(int height)
{
  m_height = height;
}

QRgb Node::key()
{
  return m_key;
}

void Node::set_key(QRgb key)
{
  m_key = key;
}

QList<QPoint> Node::pixels()
{
  return m_pixel_list;
}

void Node::set_pixel_list(QList<QPoint> pixel_list)
{
  m_pixel_list = pixel_list;
}

QList<QPoint>& Node::the_overseer()
{
  return m_pixel_list;
}
void Node::add_pixel(QPoint pixel_location)
{
  m_pixel_list.push_back(pixel_location);
}
