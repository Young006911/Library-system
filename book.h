#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string isbn;          // 图书ISBN
    string title;         // 书名
    string author;        // 作者
    string publisher;     // 出版社
    bool isBorrowed;      // 在馆状态

public:
    // 构造函数
    Book(string isbn, string title, string author, string publisher);
    
    // 析构函数
    ~Book();

    // 基本操作：获取信息
    void showInfo() const;
    string getIsbn() const { return isbn; }
    bool getBorrowStatus() const { return isBorrowed; }

    // 业务操作：借书、还书
    void borrowBook();
    void returnBook();
};
