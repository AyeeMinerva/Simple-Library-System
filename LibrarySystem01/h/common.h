#pragma once
#define _CRT_SECURE_NO_WARNINGS
//ͷ�ļ��������ļ�
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include<conio.h>
#include <Windows.h>
//���ƿռ�
using namespace std;
//�ṹ�塢�����������������
//�˻�
const string AccountPath = "accounts.txt";
struct account
{
    string name;
    string password;
    int job;
};
const string jobs[3] = { "����","ͼ�����Ա","��������Ա" };//�û�����ַ���
//����
const string NoticePath = "notices.txt";
//ͼ��
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
