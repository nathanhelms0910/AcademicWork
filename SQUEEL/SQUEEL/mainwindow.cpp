#include <iostream>
#include <QFormLayout>
#include <QtSql>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  this->setFixedSize(500, 500);

  // SQL Connection Stuff
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setHostName("User");
  db.setDatabaseName("library.db");
  db.setUserName("Student");
  db.setPassword("118");
  db.open();

  // Can remove now
  main_active = true;
  find_active = false;
  loan_active = false;

  // Creates a new query for
  // accessing all records
  query = new QSqlQuery(db);

  query->first();
  query->next();

  // Initializes Display Information
  title_t = new QLabel("Title:");
  author_t = new QLabel("Author:");
  pages_t = new QLabel("Pages:");
  copies_t = new QLabel("Copies:");
  isbn_t = new QLabel("Isbn:");
  callnumber_t = new QLabel("Call Number:");
  bookbinding_t = new QLabel("Binding Type: ");
  publisher_t = new QLabel("Publisher: ");

  title = new QLabel("                                        Current Books in the Library!"); 
  book_instructions = new QLabel("                                         Add or Update Books Here!"); 

  // Loan and Find members
  find = new Find;
  loan = new Loan(query);
  patron_class = new Patron(query);

  // Initializes Insertable Information
  enter_isbn = new QLineEdit();
  enter_title = new QLineEdit();
  enter_author = new QLineEdit();
  enter_callnumber = new QLineEdit();
  enter_copies = new QLineEdit();
  enter_pages = new QLineEdit();
  enter_binding = new QLineEdit();
  enter_publisher = new QLineEdit();

  // Sets place holder texts for insertable information
  enter_isbn->setPlaceholderText("Enter Isbn Here...");
  enter_title->setPlaceholderText("Enter Title Here...");
  enter_author->setPlaceholderText("Enter Author Here...");
  enter_callnumber->setPlaceholderText("Enter Call Number Here...");
  enter_copies->setPlaceholderText("Enter Number of Copies Here...");
  enter_pages->setPlaceholderText("Enter Pages Here...");
  enter_binding->setPlaceholderText("Enter Book Binding Here...");
  enter_publisher->setPlaceholderText("Enter Publisher...");

  // Create new layout
  formLayout = new QFormLayout(this);

  // Add title/instruction QLables
  formLayout->addRow(title);
  formLayout->addRow(book_instructions);

  book_instructions->hide();

  // Adds rows for displaying information
  formLayout->addRow(title_t);
  formLayout->addRow(author_t);
  formLayout->addRow(isbn_t);
  formLayout->addRow(callnumber_t);
  formLayout->addRow(copies_t);
  formLayout->addRow(pages_t);
  formLayout->addRow(bookbinding_t);
  formLayout->addRow(publisher_t);

  // Adds rows for editable information
  formLayout->addRow(enter_title);
  formLayout->addRow(enter_author);
  formLayout->addRow(enter_callnumber);
  formLayout->addRow(enter_pages);
  formLayout->addRow(enter_copies);
  formLayout->addRow(enter_isbn);
  formLayout->addRow(enter_binding);
  formLayout->addRow(enter_publisher);

  // Hides editable information until
  // user accesses very end of db table
  enter_title->hide();
  enter_author->hide();
  enter_callnumber->hide();
  enter_pages->hide();
  enter_isbn->hide();
  enter_binding->hide();
  enter_publisher->hide();
  enter_copies->hide();

  // Setting up buttons
  button_forward = new QPushButton("Forward", this);
  button_forward->setGeometry(400, 400, 100, 100);

  button_backward = new QPushButton("Back", this);
  button_backward->setGeometry(0, 400, 100, 100);

  button_submit = new QPushButton("Submit", this);
  button_submit->setGeometry(135, 400, 100, 100);
  button_submit->hide();

  button_update = new QPushButton("Update", this);
  button_update->setGeometry(265, 400, 100, 100);
  button_update->hide();

  formLayout->addRow(button_forward);
  formLayout->addRow(button_backward);
  formLayout->addRow(button_submit);
  formLayout->addRow(button_update);

  // Creates table view for displaying
  // all record information
  View = new QTableView;
  View->setLayout(formLayout);

  active_window = new QTableView;
  active_window = View;


  menu = new QMenu("Query");
  menubar = new QMenuBar();
  menubar->addMenu(menu);
  menu->addAction("Home"); 
  menu->addAction("Loans"); 
  menu->addAction("Book Search"); 
  menu->addAction("Patron Search"); 
  menu->addAction("About"); // Different scenario
  this->setMenuBar(menubar);

  // Connects buttons to SLOTS
  connect(button_forward, SIGNAL(clicked()), this, SLOT(forward()));
  connect(button_backward, SIGNAL(clicked()), this, SLOT(backward()));
  connect(button_submit, SIGNAL(clicked()), this, SLOT(submit()));
  connect(button_update, SIGNAL(clicked()), this, SLOT(update()));
  connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menu_slot(QAction*)));

  table_views = new QStackedWidget;
  table_views->addWidget(this->View);
  table_views->addWidget(find->find_view);
  table_views->addWidget(loan->loan_view);
  table_views->addWidget(patron_class->patron_view);

  find->find_view->show();

  this->setCentralWidget(table_views);
  table_views->setCurrentIndex(0);

  // Sets up query to start in active SELECT Mode
  query->exec("SELECT * FROM book");

  // Puts query points before first record
  query->first();
  query->previous();
}

MainWindow::~MainWindow()
{}

void MainWindow::menu_slot(QAction* action)
{
  if (action->text() == "Home")
  {
    query->exec("SELECT * FROM book");
    table_views->setCurrentIndex(0);
  }

  else if (action->text() == "Book Search")
  {
    query->exec("SELECT * FROM book");
    table_views->setCurrentIndex(1);
  }

  else if (action->text() == "Loans")
  {
    query->exec("SELECT * FROM loans");
    table_views->setCurrentIndex(2);
  }

  else if (action->text() == "About")
  {
   QMessageBox* about_box = new QMessageBox;
   about_box->setText("This is an implementation of a library database that allows a user to view inserted books, take out a loan, return a book, and search for books.");
   about_box->exec();
    // Message box with about box
  }

  else if (action->text() == "Patron Search")
  {
    query->exec("SELECT * FROM loans");
    table_views->setCurrentIndex(3);
  }
}

void MainWindow::forward()
{
  // If a next() record exists
  if (query->next())
  {
    // Hide the insertable information
    if (!title_t->isHidden())
    {
      // Hides editable information
      enter_title->hide();
      enter_author->hide();
      enter_callnumber->hide();
      enter_pages->hide();
      enter_isbn->hide();
      enter_binding->hide();
      enter_publisher->hide();
      enter_copies->hide();
      book_instructions->hide();
    }

    // Obtain information from record
    QString isbn = query->value(0).toString();
    QString title = query->value(1).toString();
    QString author = query->value(2).toString();
    QString callnumber = query->value(3).toString();
    QString pages = query->value(4).toString();
    QString copies = query->value(5).toString();
    QString binding = query->value(6).toString();
    QString publisher = query->value(7).toString();

    // Display information from record
    title_t->setText("Title: " + title);
    author_t->setText("Author: " + author);
    callnumber_t->setText("Call Number: " + callnumber);
    pages_t->setText("Pages: " + pages);
    isbn_t->setText("Isbn: " + isbn);
    bookbinding_t->setText("Binding: " + binding);
    publisher_t->setText("Publisher: " + publisher);
    copies_t->setText("Copies: " + copies);

  }
  
  // If next record doesn't exist
  else
  {
    // Show insertable info &
    // hide display info
    if (!title_t->isHidden())
    {
      // Shows QLineEdits 
      enter_title->show();
      enter_author->show();
      enter_callnumber->show();
      enter_pages->show();
      enter_isbn->show();
      enter_binding->show();
      enter_publisher->show();
      enter_copies->show();
      book_instructions->show();

      // Displays submit and 
      // update buttons
      button_submit->show();
      button_update->show();

      // Hides display information
      title_t->hide();
      author_t->hide();
      callnumber_t->hide();
      pages_t->hide();
      isbn_t->hide();
      bookbinding_t->hide();
      publisher_t->hide();
      copies_t->hide();
      title->hide();

    }
  }
}

void MainWindow::backward()
{
  if(query->previous())
  {
    // Hides insert info & shows display info
    if (!enter_title->isHidden())
    {
      // Hides editable information
      enter_title->hide();
      enter_author->hide();
      enter_callnumber->hide();
      enter_pages->hide();
      enter_isbn->hide();
      enter_binding->hide();
      enter_copies->hide();
      enter_publisher->hide();
      button_submit->hide();
      button_update->hide();
      book_instructions->hide();

      // Shows display information
      title_t->show();
      author_t->show();
      callnumber_t->show();
      pages_t->show();
      isbn_t->show();
      bookbinding_t->show();
      publisher_t->show();
      copies_t->show();
      title->show();
    }

    // Obtains information from record
    QString isbn = query->value(0).toString();
    QString title = query->value(1).toString();
    QString author = query->value(2).toString();
    QString callnumber = query->value(3).toString();
    QString pages = query->value(4).toString();
    QString copies = query->value(5).toString();
    QString binding = query->value(6).toString();
    QString publisher = query->value(7).toString();

    // Displays information from record to form
    title_t->setText("Title: " +  title);
    author_t->setText("Author: " + author);
    callnumber_t->setText("Call Number: " + callnumber);
    pages_t->setText("Pages: " + pages);
    isbn_t->setText("Isbn: " + isbn);
    bookbinding_t->setText("Binding: " + binding);
    publisher_t->setText("Publisher: " + publisher);
    copies_t->setText("Copies: " + copies);

  }
  else
    return;
}


void MainWindow::submit()
{
  if (enter_isbn->text() == "")
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("Not enough information to submit a new book, please make sure your book has an isbn");
    box->exec();
    return;
  }

  // Prepare the values, need to fix by using ? ? ?!
  query->prepare("INSERT INTO book (Isbn, Title, Author, Callnumber, Pages, Binding, Publisher, Copies)"
                 "VALUES (:Isbn, :Title, :Author, :Callnumber, :Pages, :Binding, :Publisher, :Copies)"); 

  // Safely insert them
  query->bindValue(":Isbn", enter_isbn->text());
  query->bindValue(":Title", enter_title->text());
  query->bindValue(":Author", enter_author->text());
  query->bindValue(":Callnumber", enter_callnumber->text());
  query->bindValue(":Pages", enter_pages->text());
  query->bindValue(":Binding", enter_binding->text());
  query->bindValue(":Publisher", enter_publisher->text());
  query->bindValue(":Copies", enter_copies->text());
  query->exec();

  QMessageBox* box = new QMessageBox;
  box->setText("Sucessful Submit!");
  box->exec();

  // Resets position in query
  // and sets query SELECT to active
  query->exec("SELECT * FROM book");
  query->last();
  if (query->next());
}

void MainWindow::update()
{
  // Prepare the values, need to fix by using ? ? ?!
  if (enter_isbn->text() == "")
  {
    // Will use this eventually, for now update only uses the isbn
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("Please enter the isbn of the book you want to update!\n");
    box->exec();
    return;
  }

  QMessageBox* box = new QMessageBox;
  QString box_msg = "The following were sucessfully updated:\n\n"; 

  QString isbn = enter_isbn->text();

  //Check if book (isbn) exists
  if(enter_title->text() != "") {
    if (query->exec("UPDATE book SET Title = '" + enter_title->text() + "' WHERE Isbn = " + isbn))
      box_msg += "Title\n";
  }  
  if(enter_author->text() != "") {
    if (query->exec("UPDATE book SET Author = '" + enter_author->text() + "' WHERE Isbn = " + isbn))
      box_msg += "Author\n";
  }  
  if(enter_callnumber->text() != "") {
    if(query->exec("UPDATE book SET Callnumber = '" + enter_callnumber->text() + "' WHERE Isbn = " + isbn))
      box_msg += "Call Number\n";
  }  
  if(enter_pages->text() != "") {
    if (query->exec("UPDATE book SET Pages = " + enter_pages->text() + " WHERE Isbn = " + isbn))
      box_msg += "Pages\n";
  }  


  if(enter_binding->text() != ""){  //added by Trenton Taylor
  if (query->exec("UPDATE book SET Binding = '" + enter_binding->text() + "' WHERE Isbn = " + enter_isbn->text()))
      box_msg += "Binding\n";
  }

  if(enter_binding->text() != "") {
    if (query->exec("UPDATE book SET Binding = '" + enter_binding->text() + "' WHERE Isbn = " + enter_isbn->text()))
      box_msg += "Binding\n";
  }
  if(enter_copies->text() != "") {
    if(query->exec("UPDATE book SET Copies = " + enter_copies->text() + " WHERE Isbn = " + enter_isbn->text()))
      box_msg += "Copies\n";
  }
  if(enter_publisher->text() != "") {
    if (query->exec("UPDATE book SET Publisher = '" + enter_publisher->text() + "' WHERE Isbn = " + enter_isbn->text()))
      box_msg += "Publisher\n";
  }  
  
  box->setText(box_msg);
  box->exec();

  query->exec("SELECT * FROM book");
  query->last();
  query->next();
}
