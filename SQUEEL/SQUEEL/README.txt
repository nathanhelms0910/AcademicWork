Project Name: SQUEEL
Project Collaborators: Morgan Magner, Nathan Helms, Andrew Jones, Trenton Taylor
Project Goals: The goal for this project is to submit a library database written in Qt and SQL that will:
-show books stored in a library
-allow a user to search for a book
-allow the user to submit a new book to be stored in the database
-allow a book currently in the database to be updated with new information
-contains a query menu with Loans, Book Search, Patron Search, About, and Home. 

Note: You need the ISBN to submit books, update them, to withdraw a book, to submit a book

-Loans will open up a new menu that will allow the user to see which books are currently checked out, and will allow the user to withdraw or return a loan
-Book search will allow the user to search for a book
-Patron search will allow the user to search for a specific patron
-About pulls up a quick text blurb about the program
-Home takes you back to the main window


Note: The submit button and the update button only appear when the user goes past the end of the record table
   
To Compile: Type: qmake
            Then type: make

To Run: Type ./SQUEEL

To navagate the database: click the back button to move backwards through the database, and click forward to move forward through the database.

To add a new book: Move forward until the submit button appears, add in the necessary information, and click submit. 

To update an existing book: Move forward until the update button appears, add in the necessary information, and click update.

To Withdraw a book: Navigate in the query menu and click on loans, add in the necessary information, and click Withdraw Book.

To Return a book: Navigate in the query menu and click on loans, add in the necessary information, and click Return Book.

To search for a book: Navigate in the query menu and click on Book Search, add in the necessary information, and click Submit. 

To search for a patron: Navigate in the query menu and click on Patron Search, add in the necessary information, and click Submit.
