#include <iostream>
#include <QSizePolicy>
#include "window.h"
#include "view.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRectF>
#include <QAction>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QToolBar>
#include  <QMessageBox>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>
Window::Window() : QMainWindow()
{


  
  m_Layout = new QVBoxLayout;
  m_tool = new QToolBar(this);
  m_scene = new QGraphicsScene(this);
  m_scene->addRect(0, 0, 800, 800, QPen(Qt::black), QBrush(Qt::white));
  m_view = new MyView();
  m_view->setScene(m_scene);




  setCentralWidget(m_view);



  m_bar  = new QMenuBar(this);
  m_menu = new QMenu(tr("File"));
  m_colorMenu = new QMenu(tr("Change Colors"));

  QAction *quitAction = new QAction(tr("&Quit"), this);
  quitAction->setShortcuts(QKeySequence::Quit);
  connect(quitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));

  QAction *newAction = new QAction(tr("&New"), this);
  newAction->setShortcuts(QKeySequence::New);
  connect(newAction, SIGNAL(triggered()),m_scene, SLOT(clear()));

  QAction *saveAction = new QAction(tr("&Save"), this);
  saveAction->setShortcuts(QKeySequence::Save);
  saveAction->setToolTip(tr("Save drawing to a file"));
  connect(saveAction, SIGNAL(triggered()),m_scene, SLOT(saveToFile()));
  
  setMenuBar(m_bar);
  m_bar->addMenu(m_menu);
  m_bar->addMenu(m_colorMenu);

  m_menu->addAction(newAction);
  m_menu->addAction("Open", (MyView*)m_view, SLOT(Open()));
  m_menu->addAction(saveAction);
  m_menu->addAction("Print", (MyView*)m_view, SLOT(Print()));
  m_menu->addAction(quitAction);

  m_tool->addAction("Circle", (MyView*)m_view, SLOT(Circle()));
  m_tool->addAction("Rectangle", (MyView*)m_view, SLOT(Rectangle()));
  m_tool->addAction("Triangle", (MyView*)m_view, SLOT(Triangle()));
  m_tool->addAction("Line", (MyView*)m_view, SLOT(line()));
  m_tool->addAction("Resize", (MyView*)m_view, SLOT(resize_Slot()));

  m_colorMenu->addAction("Red", (MyView*)m_view, SLOT(Red()));
  m_colorMenu->addAction("Blue", (MyView*)m_view, SLOT(Blue()));
  m_colorMenu->addAction("Green", (MyView*)m_view, SLOT(Green()));
  m_colorMenu->addAction("Purple", (MyView*)m_view, SLOT(Purple()));
  m_colorMenu->addAction("Orange", (MyView*)m_view, SLOT(Orange()));
  m_colorMenu->addAction("Yellow", (MyView*)m_view, SLOT(Yellow()));
  m_colorMenu->addAction("Black", (MyView*)m_view, SLOT(Black())); 

  addToolBar(m_tool);
  this->show();
  this->resize(800,800);

  //qspinner and qslider
}

Window::~Window()
{
  delete m_bar;
  delete m_menu;
  delete m_scene;
  delete m_view;
  // delete m_rectangle;
  //  delete m_circle;
  delete m_Layout;
  //  delete m_triangle;
  delete m_tool;
}
