#include "patron.h"
#include <iostream>

Patron::Patron(QSqlQuery* q)
{
      patron_layout = new QFormLayout;
      patron_view = new QTableView;

      patron = new QLineEdit;
      patron_author = new QLineEdit;

      patron->setPlaceholderText("Enter Patron Name Here...");
      patron_author->setPlaceholderText("Enter Author Name Here...");

      patron_submit = new QPushButton("Submit");
      connect(patron_submit, SIGNAL(clicked()), this, SLOT(patron_search()));

      query = q;

      patron_layout->addRow(patron);
      patron_layout->addRow(patron_author);
      patron_layout->addRow(patron_submit); 
      patron_view->setLayout(patron_layout);
}

Patron::~Patron()
{}

void Patron::patron_search()
{ 
  QSqlQueryModel* query_model = new QSqlQueryModel;
  QTableView* patron_table = new QTableView;

  QString check_author = patron_author->text();
  QString check_patron = patron->text();
  
  if (check_author == "" && check_patron == "")
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("You must enter both a patron name and an author name!");
    box->exec();
    return;
  }

  std::vector<QString> isbns;
  if(!query->exec("SELECT Isbn FROM loans WHERE Patron = '" + check_patron + "'"))
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("No patron found by that name!");
    box->exec();
    return;
  }

  if (query->first())
  {
    isbns.push_back(query->value(0).toString());
    while (query->next())
      isbns.push_back(query->value(0).toString());
  }

  if (isbns.size() == 0)
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("No patron found by that name!");
    box->exec();
    return;
  }
  
  QString exec_str = "Isbn = " + isbns[0];

  if (isbns.size() > 1)
  {

    for (int i = 1; i < isbns.size(); ++i)
      exec_str += " OR Isbn = " + isbns[i];
  }

  std::cout << exec_str.toStdString() << " <-- here\n";

  query_model->setQuery("SELECT * FROM book WHERE " + exec_str + " AND Author = '" + check_author + "'");

  if (!query_model->query().first())
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("No patrons or authors found, please try again.\n");
    box->exec();
    return;
  }

  QTableView* display_view = new QTableView;
  display_view->setGeometry(300, 300, 720, 400);
  display_view->setModel(query_model);
  display_view->show();
}
