#pragma once
#include "common.h"
void secretInput(istream& in, string& temp);
// 加密输入函数，加密输入到temp中,用*号掩盖

void loginCompare(account& user);
// 登录比较函数，用于比较用户提供的账户信息与系统中保存的账户信息是否匹配

bool login(account& user);
// 登录函数，用于用户登录操作，提示用户输入信息并调用登录比较函数比较

void viewReaders();
// 查看读者函数，用于显示系统中所有读者账户的信息

void viewBookAdmins();
// 查看图书管理员函数，用于显示系统中所有图书管理员账户的信息

bool addAccount();
// 添加账户函数，用于向账户文本中追加新的账户

bool modifyAccount();
// 修改账户函数，用于查询和修改系统中已存在的账户信息，如不存在则退出
