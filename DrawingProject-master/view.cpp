#include "view.h"
#include <QtMath>
#include <QKeyEvent>
#include <iostream>
#include <QPoint>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <iostream>
#include <QLine>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QGraphicsItem>
#include <QWidget>
#include <QList>
using namespace std;
MyView::MyView() : QGraphicsView()
{ }
QList<QGraphicsItem*> shapes = m_scene()->items();
void MyView::clear()
{
}

void MyView::Save()
{
}

void MyView::Open()
{
}

void MyView::Print()
{
}
void MyView::quit()
{
  
}
void MyView::newWindow()
{
}

void MyView::saveToFile()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Drawing"), "", tr("Drawing (*.drg);; All Files (*)"));
  if(fileName.isEmpty())
  {
   return;
   else {
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Unable to open file"), file.errorString());
      return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << shapes;

}

void MyView::loadFromFile()
{
}


void MyView::Rectangle()
{
  current_Shape = S_RECTANGLE;
}

void MyView::Circle()
{
  current_Shape = S_CIRCLE;
}

void MyView::Triangle()
{
  current_Shape = S_TRIANGLE;
}

void MyView::line()
{
  current_Shape = S_LINE; 
}
void MyView::Red()
{
  m_color = 0xFF2D00;
}

void MyView::Blue()
{
  m_color = 0x1200FF;
}

void MyView::Green()
{
  m_color = 0x008000;
}

void MyView::Yellow()
{
  m_color = 0xF9FF00;
}

void MyView::Purple()
{
  m_color = 0xA700FF;
}

void MyView::Orange()
{
  m_color = 0xFFA500;
}

void MyView::Black()
{
  m_color = 0x0;
}

void MyView::resize_Slot()
{
  current_Shape = S_RESIZE;
}


void MyView::mousePressEvent(QMouseEvent *event)
{

  QPoint p = event->pos();
  QPointF q = mapToScene(p);
  qreal x = q.x();
  qreal y = q.y();
  QPen drawPen(m_color);
  drawPen.setWidth(1);

QPolygonF polygon;
polygon << QPointF(x + 30, y + 30) << QPointF( x - 30, y - 30) << QPointF(x - 30, y);



  if(current_Shape == S_RECTANGLE) {
    this->scene()->addRect(QRectF(x-2, y-2, rect_x, rect_y), drawPen, QBrush(m_color)); //edit here for the points being drawn
  }

  else if(current_Shape == S_CIRCLE) {
    this->scene()->addEllipse(x-2, y-2, size_x, size_y, drawPen, QBrush(m_color)); //edit here for the points being drawn
    //show();


  }

  else if(current_Shape == S_TRIANGLE)
  {

    this->scene()->addPolygon(polygon, drawPen, QBrush(m_color));
  
  } 


  else if(current_Shape == S_LINE) {

    this->scene()->addLine(x-2, y-2, x-200, y-200, drawPen);
    //show();
  }
  else if(current_Shape == S_RESIZE)
  {
    m_clickx = x;
    m_clicky = y;

  }

}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
  if(current_Shape == S_RESIZE)
  {  
    QPoint p = event->pos();
    QPointF q = mapToScene(p);
    QGraphicsItem* resize_Shape = itemAt(m_clickx, m_clicky);
    if(resize_Shape != nullptr)
    {
      qreal x = q.x();
      qreal y = q.y();
      qreal dx = m_clickx - x;
      qreal dy = m_clicky - y;
      qreal d = qSqrt(dx * dx + dy * dy) / scene()->sceneRect().width();


      resize_Shape->setScale(d);
      cout << "x is: " << x << endl;
      cout << "y is: " << y << endl;
      cout << "dx is: " << dx << endl; 
      cout << "dy is: " << dy << endl;
      cout << "d is: " << d << endl;
      cout << "width is: " << scene()->sceneRect().width() << endl;
    }
  }
}
