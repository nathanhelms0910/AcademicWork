#include "find.h"
#include <iostream>

Find::Find()
{
  // Initialize layout
  find_layout = new QFormLayout;

  // Initialize Insertable Information
  find_isbn = new QLineEdit;
  find_title = new QLineEdit;
  find_author = new QLineEdit;
  find_callnumber = new QLineEdit;
  find_pages = new QLineEdit;
  find_binding = new QLineEdit;
  find_publisher = new QLineEdit;
  
  // This is one really long string of empty spaces
  QLabel* title = new QLabel("                                                      Find A Book Here"); 

  find_layout->addRow(title);

  // Initalize and connect pushbutton
  find_submit = new QPushButton("Submit");
  connect(find_submit, SIGNAL(clicked()), this, SLOT(find()));

  // Set place holder texts for all line edits
  find_isbn->setPlaceholderText("Enter Isbn Here...");
  find_title->setPlaceholderText("Enter Title Here...");
  find_author->setPlaceholderText("Enter Author Here...");
  find_callnumber->setPlaceholderText("Enter Call Number Here...");
  find_pages->setPlaceholderText("Enter Pages Here...");
  find_binding->setPlaceholderText("Enter Binding Here...");
  find_publisher->setPlaceholderText("Enter Publisher Here...");

  // Add line edits to the layout
  find_layout->addRow(find_isbn);
  find_layout->addRow(find_title);
  find_layout->addRow(find_author);
  find_layout->addRow(find_callnumber);
  find_layout->addRow(find_pages);
  find_layout->addRow(find_binding);
  find_layout->addRow(find_publisher);

  // Add push button to find layout
  find_layout->addRow(find_submit);

  // Create table view with layout
  find_view = new QTableView;
  find_view->setGeometry(200, 200, 400, 400);
  find_view->setLayout(find_layout);
}

Find::~Find()
{}

void Find::find()
{
  QSqlQueryModel* find_model = new QSqlQueryModel;
  QTableView* find_table = new QTableView;

  QString check_title = find_title->text();
  QString check_author = find_author->text();
  QString check_callnumber = find_callnumber->text();

  if (check_title == "" && check_author == "" && check_callnumber == "")
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("Please enter either an author, title, or call number\nfor accurate search results!\n");
    box->exec();
    return;
  }
  
  // Code that determines what the user is searching for
  if (check_author != "")
  {
    if (check_title != "")
      find_model->setQuery("SELECT * FROM book WHERE Author = '" + check_author + "' AND Title = '" + check_title + "'");

    else if (check_callnumber != "")
      find_model->setQuery("SELECT * FROM book WHERE Author = '" + check_author + "' AND Callnumber = '" + check_callnumber + "'");

    else
      find_model->setQuery("SELECT * FROM book WHERE Author = '" + check_author + "'"); 
  }
  else
  {
    if (check_callnumber != "")
      find_model->setQuery("SELECT * FROM book WHERE Callnumber = '" + check_callnumber + "'"); 
    
    else if (check_title != "")
    {
      find_model->setQuery("SELECT * FROM book WHERE Title = '" + check_title + "'"); 
    }
  }

  // If no books were found
  if (!find_model->query().first())
  {
    QMessageBox* box = new QMessageBox;
    box->setIcon(QMessageBox::Warning);
    box->setText("No books found, please try again.\n");
    box->exec();
    return;
  }

  // Display find results
  find_table->setGeometry(300, 300, 720, 400);
  find_model->insertColumns(99, 4);
  find_table->setModel(find_model);
  find_table->show();
}

void Find::show()
{
  find_view->show();
}
