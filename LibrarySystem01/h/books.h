#pragma once
#include "common.h"
bool isValidTime(const Time& temp);
// 验证时间函数，用于判断给定的时间temp是否合法

void InputTime(istream& in, Time& t);
// 输入时间函数，用于从输入流中读取用户输入的时间，并将结果存储在Time对象t中

void addBook();
// 添加图书函数，用于向系统中添加新的图书

void deleteBook();
// 删除图书函数，用于从系统中删除指定的图书

void borrowBook(account& user);
// 借书函数，用于用户借书操作，将指定的图书借出给用户

void returnBook(account& user);
// 还书函数，用于用户归还借阅的图书

void showAllBooks();
// 显示所有图书函数，用于展示系统中所有图书的信息

void showBookInfo();
// 显示图书信息函数，用于展示指定图书的详细信息

void showBorrowRecords();
// 显示借阅记录函数，用于展示系统中所有借阅记录的信息

void showBorrowRecords(account& user);
// 显示用户借阅记录函数，用于展示指定用户的借阅记录信息