#include "Book.h"

Book::Book(string isbn, string title, string author, string publisher)
    : isbn(isbn), title(title), author(author), publisher(publisher), isBorrowed(false) {}

Book::~Book() {}

void Book::showInfo() const {
    cout << "ISBN: " << isbn << " | 书名: " << title 
         << " | 作者: " << author << " | 状态: " << (isBorrowed ? "已借出" : "在馆") << endl;
}

void Book::borrowBook() { isBorrowed = true; }
void Book::returnBook() { isBorrowed = false; }
