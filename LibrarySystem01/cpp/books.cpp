#include "common.h"
#include "books.h"
//图书与图书管理
bool isValidTime(const Time& temp)
{
    // 检查年份是否合法
    if (temp.y < 0)
        return false;

    // 检查月份是否合法
    if (temp.m < 1 || temp.m > 12)
        return false;

    // 检查日期是否合法
    if (temp.d < 1 || temp.d > 31)
        return false;

    // 检查特定月份的日期是否合法
    if ((temp.m == 4 || temp.m == 6 || temp.m == 9 || temp.m == 11) && temp.d > 30)
        return false;
    if (temp.m == 2)
    {
        // 检查闰年的2月份日期是否合法
        if ((temp.y % 4 == 0 && temp.y % 100 != 0) || temp.y % 400 == 0)
        {
            if (temp.d > 29)
                return false;
        }
        else // 非闰年的2月份日期是否合法
        {
            if (temp.d > 28)
                return false;
        }
    }

    // 所有检查通过，时间合法
    return true;
}
void InputTime(istream& in, Time &t)
{
    Time temp;
    char tempCh;
    do {
        cout << "请输入合法的借书日期:格式YYYY/MM/DD" << endl;
        in >> temp.y >> tempCh >> temp.m >> tempCh >> temp.d;
        if (!isValidTime(temp))
            cout << "输入日期不合法,请重试输入合法的日期" << endl;
    } while (!isValidTime(temp));
    t.y = temp.y;
    t.m = temp.m;
    t.d = temp.d;
    return;
}
void addBook()
{
    cout << "请输入要添加的图书信息:" << endl;
    ofstream fout;
    fout.open(BookPath, ios::app);
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    book newBook;
    cin.ignore();//清除缓冲区的空格
    cout << "图书编号: ";
    getline(cin, newBook.num);
    cout << "图书名称: ";
    getline(cin, newBook.name);
    cout << "输入添加数量: ";
    cin >> newBook.quantity; // 设置默认数量为1
    newBook.borrowed = 0; // 设置默认借出数量为0

    // 查找是否已存在该编号的图书
    ifstream fin(BookPath);
    string line;
    bool bookExists = false;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string existingNum;
        ss >> existingNum;
        if (existingNum == newBook.num)
        {
            bookExists = true;
            break;
        }
    }
    fin.close();

    if (bookExists)
    {
        cout << "图书已存在，数量增加一本。" << endl;
        // 在原有记录上增加一本图书的数量
        ifstream fin(BookPath);
        ofstream temp;
        temp.open("temp.txt");
        while (getline(fin, line))
        {
            stringstream ss(line);
            string existingNum;
            string existingName;
            int existingQuantity;
            int existingBorrowed;
            ss >> existingName >> existingNum >> existingQuantity >> existingBorrowed;
            if (existingNum == newBook.num)
            {
                newBook.quantity++; // 增加数量
                temp << newBook.name << " " << newBook.num << " " << newBook.quantity + existingQuantity << " " << newBook.borrowed + existingBorrowed << endl;
            }
            else
            {
                temp << line << endl;
            }
        }
        fin.close();
        temp.close();
        remove(BookPath.c_str());
        rename("temp.txt", BookPath.c_str());
    }
    else
    {
        fout << newBook.name << " " << newBook.num << " " << newBook.quantity << " " << newBook.borrowed << endl;
        fout.close();
    }
    cout << "图书添加成功!" << endl;
}
void deleteBook()
{
    string bookNum;
    cout << "请输入要删除的图书编号: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        fin.close();
        return;
    }

    string temp;
    bool found = false;
    while (getline(fin, temp))
    {
        string num;
        string name;
        stringstream ss(temp);
        ss >> name >> num;
        if (num != bookNum)
        {
            fout << temp << endl;
        }
        else
        {
            found = true;
        }
    }

    fin.close();
    fout.close();

    remove(BookPath.data());
    rename("temp.txt", BookPath.data());

    if (found)
    {
        cout << "图书删除成功!" << endl;
    }
    else
    {
        cout << "找不到该图书编号!" << endl;
    }
}
void borrowBook(account& user)
{
    string bookNum;
    cout << "请输入要借阅的图书编号: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        fin.close();
        return;
    }

    string temp;
    bool found = false;
    Time borrowTime;
    while (getline(fin, temp))//读入文件,查找图书
    {
        stringstream ss(temp);
        string name, num;
        int quantity;
        int borrowed;
        ss >> name >> num >> quantity >> borrowed;
        if (num == bookNum && quantity - borrowed > 0)//若找到,则修改书籍信息
        {
            found = true;
            fout << name << " " << num << " " << quantity << " " << borrowed + 1;
            //合法借书日期输入
            InputTime(cin, borrowTime);
        }
        else
        {
            fout << temp << endl;
        }
    }

    fin.close();
    fout.close();

    remove(BookPath.data());
    rename("temp.txt", BookPath.data());

    if (found)//借书成功,输出借书记录
    {
        cout << "图书借阅成功!" << endl;

        ofstream recordOut;
        recordOut.open(BorrowRecordPath, ios::app);//续写方式打开记录文档
        if (!recordOut)
        { 
            cout << "文件打开失败...请重试";
            return;
        }
        //输出借书记录
        recordOut << user.name << " " << bookNum << " " << borrowTime.y << " " << borrowTime.m << " " << borrowTime.d << endl;
        recordOut.close();
    }
    else
    {
        cout << "该图书已被借出或不存在!" << endl;
    }
}
void returnBook(account& user)
{
    string bookNum;
    cout << "请输入要归还的图书编号: ";
    cin >> bookNum;
    Time returnTime;
    cout << "请输入归还时间,格式YYYY/MM/DD" << endl;
    char tempch;
    cin >> returnTime.y >> tempch >> returnTime.m >> tempch >> returnTime.d;
    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "文件打开失败...请重试";
        fin.close();
        return;
    }

    string temp;
    bool found = false;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, num;
        int quantity, borrowed;
        ss >> name >> num >> quantity >> borrowed;
        if (num == bookNum && borrowed >= 1)
        {
            found = true;
            fout << name << " " << num << " " << quantity << " " << borrowed - 1 << endl;
        }
        else
        {
            fout << temp << endl;
        }
    }

    fin.close();
    fout.close();

    remove(BookPath.data());
    rename("temp.txt", BookPath.data());

    if (found)
    {
        cout << "图书归还成功!" << endl;
        //修改记录文件:
        fin.open(BorrowRecordPath);
        if (!fin)
        {
            cout << "文件打开失败...请重试";
            return;
        }
        fout.open("temp.txt");
        if (!fout)
        {
            cout << "文件打开失败...请重试";
            fin.close();
            return;
        }
        string temp;
        bool found = false;
        while (getline(fin, temp))
        {
            stringstream ss(temp);
            string name, num;
            ss >> name >> num;
            if (!(num == bookNum && name == user.name))
            {
                fout << temp << endl;
            }
        }
        fin.close();
        fout.close();
        remove(BorrowRecordPath.data());
        rename("temp.txt", BorrowRecordPath.data());
    }
    else
    {
        cout << "该图书未被借出或不存在!" << endl;
    }
}
void showAllBooks()
{
    cout << "当前所有馆藏图书如下:" << endl;
    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }
    string temp;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, num;
        int quantity, borrowed;
        ss >> name >> num >> quantity >> borrowed;
        cout << endl;
        cout << "图书名称:" << name << endl;
        cout << "图书编号: " << num << endl;
        cout << "图书状态: " << "共有" << quantity << "本 已借出" << borrowed << "本" << endl;
    }

    fin.close();

}
void showBookInfo()
{
    string bookNum;
    cout << "请输入要查询的图书编号: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    string temp;
    bool found = false;
    while (getline(fin, temp))//从文件读入书籍信息
    {
        stringstream ss(temp);
        string name, num;
        int quantity, borrowed;
        ss >> name >> num >> quantity >> borrowed;
        if (num == bookNum)
        {
            found = true;
            cout << endl;
            cout << "图书名称:" << name << endl;
            cout << "图书编号: " << num << endl;
            cout << "图书状态: " << "共有" << quantity << "本 已借出" << borrowed << "本" << endl;
            break;
        }
    }

    fin.close();

    if (!found)
    {
        cout << "该图书不存在!" << endl;
    }
}
void showBorrowRecords()
{
    ifstream fin;
    fin.open(BorrowRecordPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    cout << "借阅记录如下:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        cout << temp << endl;//展示借阅记录
    }

    fin.close();
}
void showBorrowRecords(account& user)
{
    ifstream fin;
    fin.open(BorrowRecordPath);
    if (!fin)
    {
        cout << "文件打开失败...请重试";
        return;
    }

    cout << "您个人的借阅记录如下:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        string name, num;
        Time t;
        stringstream ss(temp);
        ss >> name >> num >> t.y >> t.m >> t.d;
        if (name == user.name)
            cout << num << " " << t.y << "/" << t.m << "/" << t.d << endl;//输出格式:姓名 借书编号 年/月/日
    }

    fin.close();
}
