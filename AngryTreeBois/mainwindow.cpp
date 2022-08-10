// Implementation file for mainwindow

#include "mainwindow.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QImage>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  avl_tree = new Avl();
  this->setFixedSize(900, 800);
  scene = new QGraphicsScene(this);
  view = new QGraphicsView(scene);
  view->setScene(scene);

  toolbar = new QToolBar(this);
  toolbar->setMinimumHeight(36);
  toolbar->setMinimumWidth(36);
  toolbar->setMovable(false);
  toolbar->addAction("Select");
  toolbar->addAction("Remove Color");
  toolbar->addAction("Color Count");
  toolbar->addAction("Border");
  toolbar->addAction("Swap");
  toolbar->addSeparator();

  this->addToolBar(Qt::RightToolBarArea, toolbar);

  menubar = new QMenuBar(view);

  filemenu = new QMenu("File&");
  filemenu->addAction("Load&");
  filemenu->addAction("Save&");
  filemenu->addSeparator();

  menubar->addMenu(filemenu);

  remove = false;
  select = false;
  border = false;

  window_image = nullptr;

  connect(filemenu, SIGNAL(triggered(QAction*)), this, SLOT(menu_clicked(QAction*)));
  connect(toolbar, SIGNAL(actionTriggered(QAction*)), this, SLOT(tool_clicked(QAction*)));
  setCentralWidget(view);
  view->show();
}

MainWindow::~MainWindow()
{}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
  QPoint click_location = event->pos();
  QPointF fpoint = view->mapToScene(click_location);
  int x = fpoint.x();
  int y = fpoint.y();

  if (select == true)
  {
    // Do select stuff
  }

  else if(swap == true)
  {
    QRgb old_color = window_image->pixel(x, y);
    QList<QPoint> color_swap;
    color_swap = avl_tree->find(old_color)->pixels();
   QColorDialog octarine;
   QColor new_color;
  if(octarine.exec())
  {
new_color = octarine.selectedColor();
avl_tree->insert(new_color.rgb());
avl_tree->find(new_color.rgb())->set_pixel_list(color_swap);
avl_tree->remove(old_color);
update_view();
  
  }

  }

  else if (remove == true)
  {
    if (window_image == nullptr)
      return;
    avl_tree->remove(window_image->pixel(x, y));
    update_view();
  }
  else if(border==true)
  {
    Node* cur = new Node();
    if (window_image == nullptr)
      return;
    if (hasBorder == false)
    {
      hasBorder = true;
      int hei = window_image->height();
      int wid = window_image->width();
      QPoint changeMe;
      QColor theSeeker;
      if (avl_tree->find(theSeeker.black())==nullptr)
      {
        avl_tree->insert(theSeeker.black());
      }

      QList<QPoint>& where_it_at = cur->the_overseer();
      QPoint start;

      for(int i =0; i<wid;++i)
      {
        changeMe.setY(0);
        changeMe.setX(i);
        QRgb tmp = cur->key();
        where_it_at.push_back(changeMe);
        cur->set_key(theSeeker.black());
        avl_tree->find(cur->key())->add_pixel(changeMe);
        for(int w=0; w<avl_tree->find(tmp)->pixels().size();++w)
        {
          if(avl_tree->find(tmp)->pixels()[w] == changeMe)
            avl_tree->find(tmp)->pixels().removeAt(w);
        }
        changeMe.setY(hei-1);
        where_it_at.push_back(changeMe);
        avl_tree->find(cur->key())->add_pixel(changeMe);
        for(int w=0; w<avl_tree->find(tmp)->pixels().size();++w)
        {
          if(avl_tree->find(tmp)->pixels()[w] == changeMe)
            avl_tree->find(tmp)->pixels().removeAt(w);
        }
      }

      for(int j =0; j<hei; ++j)
      {
        changeMe.setX(0);
        changeMe.setY(j);
        QRgb tmp = cur->key();
        where_it_at.push_back(changeMe);
        where_it_at.push_back(changeMe);
        cur->set_key(theSeeker.black());
        avl_tree->find(cur->key())->add_pixel(changeMe);
        for(int w=0; w<avl_tree->find(tmp)->pixels().size();++w)
        {
          if(avl_tree->find(tmp)->pixels()[w] == changeMe)
            avl_tree->find(tmp)->pixels().removeAt(w);
        }
        changeMe.setX(wid-1);
        where_it_at.push_back(changeMe);
        avl_tree->find(cur->key())->add_pixel(changeMe);
        for(int w=0; w<avl_tree->find(tmp)->pixels().size();++w)
        {
          if(avl_tree->find(tmp)->pixels()[w] == changeMe)
            avl_tree->find(tmp)->pixels().removeAt(w);
        }
      }
      update_view();
    }
  }

  show();
  return;
}

void MainWindow::tool_clicked(QAction* action)
{
  if (action->text() == "Select")
  {
    select = true;
    remove = false;
    border = false;
    swap = false;
  }
  
  else if (action->text() == "Remove Color")
  {
    remove = true;
    select = false;
    border = false;
    swap = false;
  }
  else if (action->text() == "Border")
  {
    border = true;
    remove = false;
    select = false;
    swap = false;
  }
  else if(action->text() == "Swap")
  {
    border = false;
    remove = false;
    select = false;
    swap = true;
  }
  else if (action->text() == "Color Count")
  {
    if (window_image == nullptr)
      return;

    tree_colors.clear();
    remove = false;
    select = false;
    border = false;
    swap = false;

    QMessageBox new_box;
    text = QString();

    new_box.setText("COLOR COUNT SUMMARY");
    count_colors(avl_tree->root());

    // Sort the colors
    for (int i = 0; i < tree_colors.size(); ++i)
    {
        for (int j = i + 1; j < tree_colors.size(); ++j)
        {
            if (tree_colors[i]->key() >= tree_colors[j]->key())
            {
                auto tmp = tree_colors[j];
                tree_colors[j] = tree_colors[i];
                tree_colors[i] = tmp;
            }
        }
    }

    text += "TOTAL COLORS: " + QString::number(tree_colors.size()) + "\n";
    // Adds the colors to the message box
    for (int i = 0; i < tree_colors.size(); ++i)
    {
        text += "Rgb: " + QString::number(tree_colors[i]->key()) 
        + "  pixels: " + QString::number(tree_colors[i]->pixels().size()) + "\n";
    }

    new_box.setInformativeText(text);

    // Executes the message box
    new_box.exec();
  }

}
void MainWindow::menu_clicked(QAction* action)
{
  if (action->text() == "Save&")
  {
    QString image_path = QFileDialog::getSaveFileName(this, "Open File", "", "PNG (*.png);;JPEG (*.jpg)");
    std::cout << "Attempting to save file...\n";
    if (window_image == nullptr)
    {
      std::cout << "You have no image to save\n";
      return;
    }
    else if (image_path.toStdString() == "")
      return;

    if (window_image->save(image_path))
      std::cout << "File Saved Sucessfully\n";
    else
      std::cout << "File Save Unsucessful\n";
  }

  else if (action->text() == "Load&")
  {
    QString image_path = QFileDialog::getOpenFileName(this, "Open File", "", "PNG (*.png);;JPEG (*.jpg)");

    // Prevents clearing scene if no image is loaded in
    if (image_path.toStdString() == "")
      return;

    // Prevents multi-load image crashes
    if (window_image != nullptr)
    {
        delete window_image;
        window_image = nullptr;
        scene->clear();
        delete avl_tree;
	hasBorder = false;
    }

    avl_tree = new Avl();
    QString test_path = image_path;
    window_image = new QImage(image_path);
    build_tree(window_image);
    avl_tree->print(*window_image);
    scene->addPixmap(QPixmap::fromImage(*window_image));
  }
}

// Builds the tree with a given image
void MainWindow::build_tree(QImage*& image)
{
  // Read in every pixel (height x width)
  for (int i = 0; i < image->height(); ++i)
  {
    for (int j = 0; j < image->width(); ++j)
    {
      // Obtain pixel's position and color
      QPoint pixel_pos(j, i);
      QRgb pixel_color(image->pixel(pixel_pos));

      // If color doesn't exist in tree, add it as a node
      if (avl_tree->find(pixel_color) == nullptr)
      {
        avl_tree->insert(pixel_color);
        avl_tree->find(pixel_color)->add_pixel(pixel_pos);
      }
      else
        avl_tree->find(pixel_color)->add_pixel(pixel_pos);
    }
  }
  // Ensures image can hold tree's image
  window_image = new QImage(image->width(), image->height(), image->format());
}

void MainWindow::update_view()
{
  scene->clear();
  avl_tree->print(*window_image);
  scene->addPixmap(QPixmap::fromImage(*window_image));

}

void MainWindow::count_colors(Node* cur)
{
    if (cur == nullptr)
      return;

    tree_colors.append(cur);

    if (cur->m_left != nullptr)
        count_colors(cur->m_left);

    if(cur->m_right != nullptr)
        count_colors(cur->m_right);
}
