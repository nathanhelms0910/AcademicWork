#include <QWidget>
#include <QSlider>
#include <QMainWindow>
#include <QSizePolicy>
#include "view.h"
#include <QToolBar>
#ifndef __WINDOW_H
#define __WINDOW_H

class QGraphicsScene;
class QPushButton;
class QVBoxLayout;
class QPoint;
class QMouseEvent;
class QToolBar;
class QLabel;
class QLineEdit;
class QMessageBox;
class QHBoxLayout;

class Window : public QMainWindow
{
  Q_OBJECT
  private:
    QGraphicsScene* m_scene;
    MyView* m_view;
    QMenuBar *m_bar;
    QMenu *m_menu;
    QToolBar *m_tool;
    QMenu *m_colorMenu;
    
    
    QPushButton* m_triangle;
    QPushButton* m_circle;
    QPushButton* m_rectangle;
    QPushButton* m_red;
    QPushButton* m_blue;
    QPushButton* m_green;
    QPushButton* m_orange;
    QPushButton* m_purple;
    QPushButton* m_yellow; 

    QPushButton* m_black;
    QVBoxLayout* m_Layout;
    QSize iconSize() const;
    void setIconSize(const QSize &iconSize);
//tie to resize button, click it, new window pops up with slider. User slides it to increase size of drawin items

public slots:
  //void shape_Size();
// void resize_Slot(); 
  public:
  int exitActive;
    Window();
    ~Window();
};
#endif
