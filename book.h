#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
using namespace std;

class Item{
protected:
    string id;     
    string name;    
    string author;
    bool isBorrowed;
public:
    Item(string i="",string n="",string a=""):id(i),name(n),author(a),isBorrowed(false){}
    virtual void showInfo() const{
        cout<<"编号："<<id<<" 书名："<<name<<" 作者："<<author;
        if(isBorrowed) cout<<" 【已借出】";
        else cout<<" 【可借阅】";
        cout<<endl;
    }
    string getId() const{return id;}
    bool getStatus() const{return isBorrowed;}
    void borrowBook(){isBorrowed = true;}
    void returnBook(){isBorrowed = false;}
};

class Book : public Item{
public:
    Book(string i="",string n="",string a=""):Item(i,n,a){}
    void showInfo() const override{
        cout<<"图书 ";
        Item::showInfo();
    }
};

#endif
