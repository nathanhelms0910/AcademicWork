CREATE TABLE book
(
  Isbn INTEGER,
  Title TEXT,
  Author TEXT,
  Callnumber TEXT,
  Pages INTEGER,
  Copies INTEGER,
  Binding TEXT,
  Publisher TEXT
  );

CREATE TABLE loans
(
    Isbn INTEGER,
    Patron TEXT
    );
