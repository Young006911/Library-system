#pragma once
#include <string>
#include <vector>
#include "Book.h" // 依赖关系

using namespace std;

class User {
protected:
    string id;
    string name;
    string department;
    // 组合关系：用户拥有借出的书（这里先用vector简单表示，后续会优化）
    vector<Book*> borrowedBooks; 

public:
    User(string id, string name, string dept);
    virtual ~User(); // 虚析构函数，为多态做准备

    virtual void showInfo() const;
    string getId() const { return id; }
    
    // 借书与还书逻辑（依赖关系体现）
    bool borrowABook(Book* book);
    bool returnABook(const string& isbn);
    void showBorrowedBooks() const;
}; 
