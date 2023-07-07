#include "common.h"
#include "accounts.h"
//账户与账户管理
void secretInput(istream& in,string &temp)
{
    temp="";
    //密码的加密输入
    char ch, inputPassword[105];
    int intdx = 0;
    while ((ch = _getch()) != '\r')//当输入的不是回车的时候就继续读入
    {
        if (ch != '\b')
        {
            cout << "*";
            inputPassword[intdx++] = ch;
        }//如果没有输入退格就在屏幕上输出一个*
        else
        {
            if (intdx > 0)//若全部删除完则不再退格
            {
                cout << '\b';
                cout << " ";
                cout << '\b';
                intdx--;
            }
        }//如果输入退格就先输出一个退格然后在将上次输出的*换为空格然后继续退格
    }
    cout << endl;
    for (int di = 0; di < intdx; di++)
    {
        temp += inputPassword[di];//将字符数组读入临时账户的密码
    }
    return;
}
void loginCompare(account& user)
{
    user.job = -1;
    ifstream fin;
    fin.open(AccountPath);
    account temp;
    while (fin >> temp.name >> temp.password >> temp.job)
    {
        if (temp.name == user.name && temp.password == user.password)
        {
            user.job = temp.job;
            return;
        }
    }
    fin.close();
    return;
}
bool login(account& user)
{
    cout << "//请登录：" << endl;
    cout << "//请输入您的账号:";
    cin >> user.name;
    cout << "//请输入您的密码:";
    secretInput(cin,user.password);
    loginCompare(user);//登录比较检测
    if (user.job >= 0)//如果存在该用户及用户身份,则登入
    {
        cout << "欢迎登陆，" << jobs[user.job] << " " << user.name << endl;
        system("pause");//暂停展示登陆欢迎信息
        return true;
    }
    else
    {
        cout << "用户名或密码错误!" << endl;
        return false;
    }
}
bool addAccount()
{
   
    account temp;
    cout << "注册开始:" << endl;
    cout << "请输入账号:";
    cin >> temp.name;

    //用户是否存在的检测
    ifstream fin;
    fin.open(AccountPath);
    account test;
    while (fin >> test.name >> test.password >> test.job)
    {
        if (temp.name == test.name)
        {
            cout << "该用户名已被注册,请重试!" << endl;
            return false;//若用户已存在则直接返回注册失败
        }
    }
    fin.close();

    //若用户不存在则继续注册
    cout << "请输入密码:";
    secretInput(cin,temp.password);
    string temppassword;
    cout << "请确认密码:";//密码的二次验证
    secretInput(cin, temppassword);
    if (temppassword != temp.password)
    {
        cout << "两次密码不一致,请检查后重新注册!!" << endl;
        return false;
    }
    cout << "请输入用户身份: 读者(0), 管理员(1), 超级管理员(2): ";
    cin >> temp.job;
    //添加新建用户信息
    ofstream fout;
    fout.open(AccountPath, ios::app);
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        return false;
    }
    fout << temp.name << " " << temp.password << " " << temp.job << endl;
    fout.close();
    return true;
}
bool modifyAccount()
{
    cout << "请输入要修改密码的账户用户名:" << endl;
    string tempName;
    cin >> tempName;
    ifstream fin;
    fin.open(AccountPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return false;
    }
    account temp;
    bool exist = false;
    string tempFileData = ""; //临时储存文件内容
    while (fin >> temp.name >> temp.password >> temp.job)
    {
        if (temp.name == tempName)
        {
            cout << "已找到该用户，当前信息为:" << endl;
            cout << temp.name << ' ' << temp.password << ' ' << temp.job << endl;
            cout << "请输入新信息:" << endl;
            cout << "用户名:";
            cin >> temp.name;
            //输入密码及密码的二次验证
            cout << "请输入密码:";
            secretInput(cin, temp.password);
            string temppassword;
            cout << "请确认密码:";//密码的二次验证
            secretInput(cin, temppassword);
            if (temppassword != temp.password)
            {
                cout << "两次密码不一致,请检查后重新修改!!" << endl;
                return false;
            }
            cout << "用户身份: 读者(0), 管理员(1), 超级管理员(2): ";
            cin >> temp.job;
            exist = true;
        }
        tempFileData += temp.name + ' ' + temp.password + ' ' + to_string(temp.job) + '\n';
    }
    if (!exist)
        cout << "该用户不存在!" << endl;
    fin.close();

    ofstream fout;
    fout.open(AccountPath);
    fout << tempFileData;
    fout.close();
    return exist;
}
void viewReaders()
{
    ifstream fin(AccountPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    cout << "读者用户如下:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, password;
        int job;
        ss >> name >> password >> job;
        if (jobs[job] == "读者")
        {
            cout << "用户名: " << name << endl;
            cout << "用户身份: " << jobs[job] << endl;
            cout << endl;
        }
    }

    fin.close();
}
void viewBookAdmins()
{
    ifstream fin(AccountPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    cout << "图书管理员如下:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, password;
        int job;
        ss >> name >> password >> job;
        if (jobs[job] == "图书管理员")
        {
            cout << "用户名: " << name << endl;
            cout << "用户身份: " << jobs[job] << endl;
            cout << endl;
        }
    }

    fin.close();
}
