#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QLabel>
#include <QMessageBox>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QSqlQueryModel>
#include <QTableView>
#include <QStackedWidget>

#include <loan.h>
#include <find.h>
#include <patron.h>

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


  private:
    QSqlDatabase db;
    QSqlQuery* query;

    QTableView* active_window;

    QFormLayout *formLayout;
    QTableView *View;
    QTableView* patron_view;
    QFormLayout* patron_layout;

    QStackedWidget* table_views;

    QMenu* menu;
    QMenuBar* menubar;

    QLabel* title;
    QLabel* book_instructions;
    
    // Editable line edits
    QLineEdit* enter_isbn;
    QLineEdit* enter_title;
    QLineEdit* enter_author;
    QLineEdit* enter_callnumber;
    QLineEdit* enter_pages;
    QLineEdit* enter_binding;
    QLineEdit* enter_publisher;
    QLineEdit* enter_copies;
    QMessageBox about_box;


    // Labels for displaying record info
    QLabel* title_t;
    QLabel* author_t;
    QLabel* pages_t;
    QLabel* isbn_t;
    QLabel* callnumber_t;
    QLabel* publisher_t;
    QLabel* bookbinding_t;
    QLabel* copies_t;

    // Push buttons to traverse data base
    QPushButton* button_forward;
    QPushButton* button_backward;
    QPushButton* button_submit;
    QPushButton* button_update;

    Find* find;
    Loan* loan;
    Patron* patron_class;

    bool find_active;
    bool loan_active;
    bool main_active;

  public slots:
    void forward();
    void backward();
    void submit();
    void update();
    void menu_slot(QAction* action);
};

#endif // MAINWINDOW_H
