#include <iostream>
#include <string>
#include "book.h"
#define MAX_BOOK 100

Book bookList[MAX_BOOK];
int bookCount = 0;


void addBook(){
    if(bookCount >= MAX_BOOK){
        cout<<"图书库存已满！"<<endl;
        return;
    }
    string id,name,author;
    cout<<"请输入书号：";
    cin>>id;
    cout<<"请输入书名：";
    cin.ignore();
    getline(cin,name);
    cout<<"请输入作者：";
    getline(cin,author);
    bookList[bookCount++] = Book(id,name,author);
    cout<<"✅ 新增图书成功！"<<endl;
}


void showAllBook(){
    if(bookCount == 0){
        cout<<"暂无图书记录"<<endl;
        return;
    }
    cout<<"\n===== 图书列表 ====="<<endl;
    for(int i=0;i<bookCount;i++){
        bookList[i].showInfo();
    }
    cout<<"====================\n"<<endl;
}

