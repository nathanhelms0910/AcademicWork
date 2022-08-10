#include "loan.h"
#include <iostream>

Loan::Loan(QSqlQuery* query_t)
{
  return_button = new QPushButton("Return Book");
  withdraw_button = new QPushButton("Withdraw Book");

  forward_button = new QPushButton("Forward");
  forward_button->setGeometry(200, 200, 100, 100);

  backward_button = new QPushButton("Backward");
  backward_button->setGeometry(0, 200, 100, 100);

  loan_layout = new QFormLayout;

  title = new QLabel("                                                 Current Book Loans!"); 
  loan_instructions = new QLabel("                                     Withdraw or Return a Book Here!"); 
  loan_layout->addRow(title);
  loan_layout->addRow(loan_instructions);
  loan_instructions->hide();

  //loan_title = new QLineEdit;
  enter_isbn = new QLineEdit;
  enter_loaner = new QLineEdit;

  this->query = query_t;

  // Setting placeholder text
  // loan_title->setPlaceholderText("Title:");
  enter_isbn->setPlaceholderText("Enter Isbn Here...");
  enter_loaner->setPlaceholderText("Enter Patron Here...");


  // NOTE: Probably should display name and author of book that the loaner has out
  isbn_t = new QLabel("Isbn: ");
  loaner_t = new QLabel("Patron: ");

  // Add line edits to the layout
  // loan_layout->addRow(loan_title);
  loan_layout->addRow(enter_isbn);
  loan_layout->addRow(enter_loaner);
  loan_layout->addRow(isbn_t);
  loan_layout->addRow(loaner_t);

  // Add push buttons to the layout
  loan_layout->addRow(forward_button);
  loan_layout->addRow(backward_button);
  loan_layout->addRow(return_button);
  loan_layout->addRow(withdraw_button);

  enter_isbn->hide();
  enter_loaner->hide();
  return_button->hide();
  withdraw_button->hide();


  // Set the layout
  loan_view = new QTableView;
  loan_view->setGeometry(200, 200, 400, 400);
  loan_view->setLayout(loan_layout);
  
  connect(return_button, SIGNAL(clicked()), this, SLOT(return_book()));
  connect(withdraw_button, SIGNAL(clicked()), this, SLOT(withdraw_book()));
  connect(forward_button, SIGNAL(clicked()), this, SLOT(loan_forward()));
  connect(backward_button, SIGNAL(clicked()), this, SLOT(loan_backward()));
}

Loan::~Loan()
{
}

void Loan::loan_forward()
{
  // If a next() record exists
  if (query->next())
  {
    // Are the QLabels not hidden?
    if (!isbn_t->isHidden())
    {
      // Hide the QLineEdits
      enter_isbn->hide();
      enter_loaner->hide();
    }

    // Obtain information from record
    QString isbn = query->value(0).toString();
    QString patron = query->value(1).toString();

    // Display information from record
    isbn_t->setText("Isbn: " + isbn);
    loaner_t->setText("Patron: " + patron);
  }

  // If a next record doesn't exist
  else
  {
    // Show insertable info &
    // hide display information
    if (!isbn_t->isHidden())
    {
      // Display QLineEdits
      enter_isbn->show();
      enter_loaner->show();
      loan_instructions->show();

      // ALlowing inserting records
      // into the loans database
      return_button->show();
      withdraw_button->show();

      // Hides display information
      isbn_t->hide();
      loaner_t->hide();

      title->hide();
    }
  }
}

void Loan::loan_backward()
{
  // If a previous record exists
  if (query->previous())
  {
    // Are the QLineEdits not hidden?
    if (!enter_isbn->isHidden())
    {
      // Hides insertable information
      enter_isbn->hide();
      enter_loaner->hide();
      return_button->hide();
      withdraw_button->hide();
      loan_instructions->hide();

      // Shows display information
      isbn_t->show();
      loaner_t->show();
      title->show();
    }

    // Obtains information from record
    QString isbn = query->value(0).toString();
    QString patron = query->value(1).toString();

    // Display information from record
    isbn_t->setText("Isbn: " + isbn);
    loaner_t->setText("Patron: " + patron);
  }

  // No previous record exists
  else
    return;
}

void Loan::withdraw_book()
{

  query->exec("SELECT * FROM loans");

  // Check for entered ISBN
  if (enter_isbn->text() == "")
  {
    QMessageBox* box = new QMessageBox;
    box->setText("Plase enter an Isbn");
    box->exec();
    return;
  }

  query->prepare("INSERT INTO loans (Isbn, Patron)"
                 "VALUES (:Isbn, :Patron)");

  // Safely add them
  query->bindValue(":Isbn", enter_isbn->text());
  query->bindValue(":Patron", enter_loaner->text());
  query->exec();
  query->exec("SELECT * FROM loans");
  query->last();
  query->next();

  QMessageBox* box = new QMessageBox;
  box->setText("Sucessful withdrawal!");
  box->exec();
}

void Loan::return_book()
{
  // No information is entered
  if (enter_isbn->text() == "")
  {
    QMessageBox* box = new QMessageBox;
    box->setText("Please enter an Isbn");
    box->exec();
    return;
  }

  //query->exec("SELECT * FROM loans WHERE Isbn = " + enter_isbn->text());
  //int check_copies = 0;
  //check_copies = query->value(5).toInt();
  // Check if name matches up with patron, need both for proper return
  /*if (check_copies <= 0)
  {
    QMessageBox* box = new QMessageBox;
    box->setText("This book already has too many copies out, please try again later!");
    box->exec();
    return;
  }
  else
  {
    check_copies++;
    QString new_copies(check_copies);
    //query->exec("UPDATE book SET Copies = " + new_copies + " WHERE Isbn = " + enter_isbn->text());
  }*/

  query->exec("SELECT * FROM loans"); // FROM book

  if(query->exec("DELETE FROM loans WHERE Isbn = '" + enter_isbn->text() + "' AND Patron = '" + enter_loaner->text() + "'"))
  {
    QMessageBox* box = new QMessageBox;
    box->setText("Sucessful book return!");
    box->exec();
  }

  query->exec("SELECT * FROM loans"); // FROM book
  query->last();
  query->next();
}

void Loan::show()
{
  loan_view->show();
}
