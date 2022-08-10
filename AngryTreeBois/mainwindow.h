// Header file for mainwindow
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QToolBar>
#include <QMenu>
#include <QFile>
#include <QFileDialog>
#include <QMenuBar>
#include <QColor>
#include <QRgb>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDialog>
#include <QColorDialog>

#include <avl.h>
#include <node.h>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void build_tree(QImage*& image);
    void update_view();

    void count_colors(Node* cur);

    //Trenton's swap function definition
   // void color_Swap(QColor A, QColor B);

  protected:
    void mousePressEvent(QMouseEvent* event);

  public slots:
    void menu_clicked(QAction* action);
    void tool_clicked(QAction* action);

  private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Avl* avl_tree;
    QImage* window_image;

    QMenu* filemenu;
    QMenuBar* menubar;
    QToolBar* toolbar;

    QVector<Node*> tree_colors;
    QString text;

    bool remove;
    bool select;
    bool border;
    bool swap;

    bool hasBorder;
};

#endif // MAINWINDOW_H
