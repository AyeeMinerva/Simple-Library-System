#pragma once
#include "common.h"
bool isValidTime(const Time& temp);
// ��֤ʱ�亯���������жϸ�����ʱ��temp�Ƿ�Ϸ�

void InputTime(istream& in, Time& t);
// ����ʱ�亯�������ڴ��������ж�ȡ�û������ʱ�䣬��������洢��Time����t��

void addBook();
// ���ͼ�麯����������ϵͳ������µ�ͼ��

void deleteBook();
// ɾ��ͼ�麯�������ڴ�ϵͳ��ɾ��ָ����ͼ��

void borrowBook(account& user);
// ���麯���������û������������ָ����ͼ�������û�

void returnBook(account& user);
// ���麯���������û��黹���ĵ�ͼ��

void showAllBooks();
// ��ʾ����ͼ�麯��������չʾϵͳ������ͼ�����Ϣ

void showBookInfo();
// ��ʾͼ����Ϣ����������չʾָ��ͼ�����ϸ��Ϣ

void showBorrowRecords();
// ��ʾ���ļ�¼����������չʾϵͳ�����н��ļ�¼����Ϣ

void showBorrowRecords(account& user);
// ��ʾ�û����ļ�¼����������չʾָ���û��Ľ��ļ�¼��Ϣ