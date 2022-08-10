#ifndef LOAN_H
#define LOAN_H

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


class Loan : public QObject
{
  Q_OBJECT
  public:
    Loan(QSqlQuery* query_t);
    ~Loan();

    QTableView* loan_view;
    QFormLayout* loan_layout;

    QSqlQuery* query;

    QLabel* loan_instructions;
    QLabel* title;

    QLineEdit* enter_title;
    QLineEdit* enter_isbn;
    QLineEdit* enter_loaner;

    QLabel* title_t;
    QLabel* isbn_t;
    QLabel* loaner_t;

    QMenu* menu;
    QMenuBar* menubar;

    QPushButton* forward_button;
    QPushButton* backward_button;
    QPushButton* return_button;
    QPushButton* withdraw_button;

    void show();

  private:

  public slots:
    void loan_forward();
    void loan_backward();
    void withdraw_book();
    void return_book();
};
#endif // LOAN_H
