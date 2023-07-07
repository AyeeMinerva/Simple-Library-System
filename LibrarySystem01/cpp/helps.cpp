#include "common.h"
#include "helps.h"
//通知与输出展示
bool Hello()
{
    cout << "//////////////////////////////////////" << endl;
    cout << "//        欢迎使用图书管理系统      //" << endl;
    cout << "//////////////////////////////////////" << endl;
    return true;
}
void help(int job)
{
    cout << "//////////////////////////////////////" << endl;
    cout << "//              菜单                //" << endl;
    switch (job)
    {
    case 0:
        cout << "//1. 借书" << endl;
        cout << "//2. 还书" << endl;
        cout << "//3. 查询个人信息" << endl;
        cout << "//4. 查询图书信息" << endl;
        cout << "//5. 查询所有图书信息" << endl;
        cout << "//6. 查看公告" << endl;
        cout << "//7. 注销" << endl; 
        break;
    case 1:
        cout << "//1. 添加图书" << endl;
        cout << "//2. 删除图书" << endl;
        cout << "//3. 查询所有图书信息" << endl;
        cout << "//4. 查询未还书信息" << endl;
        cout << "//5. 发布公告" << endl;
        cout << "//6. 注销" << endl;
        break;
    case 2:
        cout << "//1. 注册新账户" << endl;
        cout << "//2. 修改账户信息" << endl;
        cout << "//3. 查看所有读者用户信息" << endl;
        cout << "//4. 查看所有图书管理员" << endl;
        cout << "//5. 注销" << endl;
        break;
    }
    cout << "//////////////////////////////////////" << endl;
}