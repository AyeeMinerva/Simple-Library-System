#include "common.h"
#include "books.h"
#include "accounts.h"
#include "helps.h"
#include "notices.h"
//������
int main()
{
Begin:
    system("cls");
    Hello();
    account currentUser;
    //���õ�¼����,��δ��¼���ظ�����
    while (true)
    {
        if (login(currentUser))//�ظ�ֱ������Ϊֹ
            break;
    }
    int choice;
    while (true)
    {
        //�����û���¼�����, ���о�����û��������
        system("cls"); // ����
        help(currentUser.job);

        //�ȴ��û�ѡ��,ͨ���û��ľ���ѡ���ȡ����Ĺ��ܺ���ʵ��
        cout << "//��������Ҫ���еĲ���:";
        cin >> choice;
        switch (currentUser.job)//�����û���ݽ��в�ͬѡ���ѡ��
        {
        case 0://����Ƕ���
            switch (choice)
            {
            case 1:
                borrowBook(currentUser);
                break;
            case 2:
                returnBook(currentUser);
                break;
            case 3:
                showBorrowRecords(currentUser);
                break;
            case 4:
                showBookInfo();
                break;
            case 5:
                showAllBooks();
                break;
            case 6:
                showNotice();
                break;
            case 7:
                goto Begin;
                //return 0;
                break;
            default:
                cout << "������������������!" << endl;
                break;
            }
            break;
        case 1://ͼ�����Ա
            switch (choice)
            {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                showAllBooks();
                break;
            case 4:
                showBorrowRecords();
                break;
            case 5:
                newNotice();
                break;
            case 6:
                goto Begin;
                //return 0;
                break;
            default:
                cout << "������������������!" << endl;
                break;
            }
            break;
        case 2://��������Ա
            switch (choice)
            {
            case 1:
                addAccount();
                break;
            case 2:
                modifyAccount();
                break;
            case 3:
                viewReaders();
                break;
            case 4:
                viewBookAdmins();
                break;
            case 5:
                goto Begin;
                //return 0;
            default:
                cout << "������������������!" << endl;
                break;
            }
            break;
        default:
            break;
        }
        system("pause");
    }
    return 0;
}