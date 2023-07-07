#pragma once
#define _CRT_SECURE_NO_WARNINGS
//头文件及依赖文件
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include<conio.h>
#include <Windows.h>
//名称空间
using namespace std;
//结构体、常量与随机变量定义
//账户
const string AccountPath = "accounts.txt";
struct account
{
    string name;
    string password;
    int job;
};
const string jobs[3] = { "读者","图书管理员","超级管理员" };//用户身份字符串
//公告
const string NoticePath = "notices.txt";
//图书
struct Time
{
    int y;
    int m;
    int d;
};
struct book
{
    string name;
    string num;
    int quantity;
    int borrowed;
};
const string BookPath = "books.txt";
const string BorrowRecordPath = "borrow_records.txt";
