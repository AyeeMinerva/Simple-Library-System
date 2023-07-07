#include "common.h"
#include "notices.h"
//公告与公告管理
bool newNotice()
{
    cout << "//正在准备发布新公告....." << endl;
    ofstream fout;
    fout.open(NoticePath, ios::app);
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        return false;
    }
    string temp;
    cout << "//请输入要发布的公告，单独一行输入Ctrl+Z组合键结束.." << endl;
    while (getline(cin, temp))
    {
        fout << temp << endl;
    }
    fout << endl;
    cin.clear();
    cin.ignore();
    fout.close();
    cout << "//您所新建的公告已被保存" << endl;
    return true;
}
void showNotice()
{
    cout << "正在查询公告.." << endl;
    ifstream fin;
    fin.open(NoticePath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }
    cout << "当前查询到的公告如下:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        cout << temp << endl;
    }
    fin.close();
}

