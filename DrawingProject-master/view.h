#include <QGraphicsView>
#include <QObject>
#ifndef __VIEW_H
#define __VIEW_H
class MyView : public QGraphicsView
{
  enum Shape{S_RECTANGLE, S_CIRCLE, S_TRIANGLE, S_LINE, S_RESIZE};
  enum Color{};
  Q_OBJECT
  private:
    int m_color;
  const  int size_x = 100;
  const  int size_y = 100;
  const  int rect_x = 250;
  const  int rect_y = 100;
  qreal m_clickx;
  qreal m_clicky;
  public:
    Shape current_Shape;
    MyView();
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
  public slots:
    void Rectangle(); 
    void Circle(); 
    void Triangle(); 
    void line();
    void Red();
    void Green();
    void Blue();
    void Orange();
    void Purple();
    void Yellow();
    void Black();
    void resize_Slot();
    void clear();
    void Save();
    void Print();
    void quit();
    void newWindow();
    void Open();
    void saveToFile();
    void loadFromFile();

signals: 
    void resizeSignal();

};
#endif
