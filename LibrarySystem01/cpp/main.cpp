#include "common.h"
#include "books.h"
#include "accounts.h"
#include "helps.h"
#include "notices.h"
//主函数
int main()
{
Begin:
    system("cls");
    Hello();
    account currentUser;
    //调用登录函数,若未登录则重复调用
    while (true)
    {
        if (login(currentUser))//重复直到登入为止
            break;
    }
    int choice;
    while (true)
    {
        //根据用户登录的身份, 进行具体的用户界面输出
        system("cls"); // 清屏
        help(currentUser.job);

        //等待用户选择,通过用户的具体选择调取具体的功能函数实现
        cout << "//请输入您要进行的操作:";
        cin >> choice;
        switch (currentUser.job)//根据用户身份进行不同选项的选择
        {
        case 0://如果是读者
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
                cout << "输入有误，请重新输入!" << endl;
                break;
            }
            break;
        case 1://图书管理员
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
                cout << "输入有误，请重新输入!" << endl;
                break;
            }
            break;
        case 2://超级管理员
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
                cout << "输入有误，请重新输入!" << endl;
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