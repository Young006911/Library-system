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
       
