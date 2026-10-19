#pragma once
#include <string>
#include <vector>
#include "Book.h" 

using namespace std;

class User {
protected:
    string id;
    string name;
    string department;
    vector<Book*> borrowedBooks; 

public:
    User(string id, string name, string dept);
    virtual ~User();

    virtual void showInfo() const;
    string getId() const { return id; }
    
    bool borrowABook(Book* book);
    bool returnABook(const string& isbn);
    void showBorrowedBooks() const;
}; 
