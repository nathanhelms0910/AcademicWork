#ifndef FIND_H
#define FIND_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QTableView>
#include <QFormLayout>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>

class Find : public QObject
{
  Q_OBJECT
  public:
    Find();
    ~Find();

    QTableView* find_view;
    QFormLayout* find_layout;
    QPushButton* find_submit;

    // Line edits for find
    QLineEdit* find_isbn;
    QLineEdit* find_title;
    QLineEdit* find_author;
    QLineEdit* find_callnumber;
    QLineEdit* find_pages;
    QLineEdit* find_binding;
    QLineEdit* find_publisher;
    QLineEdit* find_copies;

    QMenu* menu;
    QMenuBar* menubar;


    void show();

  private:

  public slots:
    void find();
};


#endif // FIND_H
