#ifndef PATRON_H
#define PATRON_H

#include <QWidget>
#include <QObject>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFormLayout>
#include <QSqlQuery>
#include <QMenu>
#include <QMenuBar>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

class Patron : QObject
{
  Q_OBJECT
  
  public:
    Patron(QSqlQuery* q);
    ~Patron();

    QFormLayout* patron_layout;
    QTableView* patron_view;
    
    QSqlQuery* query;

    QLineEdit* patron;
    QLineEdit* patron_author;

    QPushButton* patron_submit;

  public slots:
    void patron_search();
};
#endif // PATRON_H
