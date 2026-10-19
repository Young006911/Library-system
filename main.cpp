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

void borrow(){
    string bid;
    cout<<"输入要借阅的书号：";
    cin>>bid;
    for(int i=0;i<bookCount;i++){
        if(bookList[i].getId() == bid){
            if(bookList[i].getStatus()){
                cout<<"❌ 这本书已经被借走了"<<endl;
                return;
            }
            bookList[i].borrowBook();
            cout<<"✅ 借书成功！"<<endl;
            return;
        }
    }
    cout<<"❌ 未找到该书"<<endl;
}

// 还书
void giveBack(){
    string bid;
    cout<<"输入要归还的书号：";
    cin>>bid;
    for(int i=0;i<bookCount;i++){
        if(bookList[i].getId() == bid){
            if(!bookList[i].getStatus()){
                cout<<"❌ 本书未被借出，无需归还"<<endl;
                return;
            }
            bookList[i].returnBook();
            cout<<"✅ 还书成功！"<<endl;
            return;
        }
    }
    cout<<"❌ 未找到该书"<<endl;
}

void menu(){
    cout<<"\n=====图书馆借阅管理系统====="<<endl;
    cout<<"1.新增图书"<<endl;
    cout<<"2.查看所有图书"<<endl;
    cout<<"3.借阅图书"<<endl;
    cout<<"4.归还图书"<<endl;
    cout<<"0.退出系统"<<endl;
    cout<<"============================"<<endl;
    cout<<"请输入功能选择：";
}

int main()
{
    int op;
    while(true){
        menu();
        cin>>op;
        switch(op){
            case 1: addBook();break;
            case 2: showAllBook();break;
            case 3: borrow();break;
            case 4: giveBack();break;
            case 0:
                cout<<"系统退出，再见！"<<endl;
                return 0;
            default:
                cout<<"输入错误，请重新选择！"<<endl;
        }
    }
    return 0;
}
