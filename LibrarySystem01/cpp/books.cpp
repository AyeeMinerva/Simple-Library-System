#include "common.h"
#include "books.h"
//ͼ����ͼ�����
bool isValidTime(const Time& temp)
{
    // �������Ƿ�Ϸ�
    if (temp.y < 0)
        return false;

    // ����·��Ƿ�Ϸ�
    if (temp.m < 1 || temp.m > 12)
        return false;

    // ��������Ƿ�Ϸ�
    if (temp.d < 1 || temp.d > 31)
        return false;

    // ����ض��·ݵ������Ƿ�Ϸ�
    if ((temp.m == 4 || temp.m == 6 || temp.m == 9 || temp.m == 11) && temp.d > 30)
        return false;
    if (temp.m == 2)
    {
        // ��������2�·������Ƿ�Ϸ�
        if ((temp.y % 4 == 0 && temp.y % 100 != 0) || temp.y % 400 == 0)
        {
            if (temp.d > 29)
                return false;
        }
        else // �������2�·������Ƿ�Ϸ�
        {
            if (temp.d > 28)
                return false;
        }
    }

    // ���м��ͨ����ʱ��Ϸ�
    return true;
}
void InputTime(istream& in, Time &t)
{
    Time temp;
    char tempCh;
    do {
        cout << "������Ϸ��Ľ�������:��ʽYYYY/MM/DD" << endl;
        in >> temp.y >> tempCh >> temp.m >> tempCh >> temp.d;
        if (!isValidTime(temp))
            cout << "�������ڲ��Ϸ�,����������Ϸ�������" << endl;
    } while (!isValidTime(temp));
    t.y = temp.y;
    t.m = temp.m;
    t.d = temp.d;
    return;
}
void addBook()
{
    cout << "������Ҫ��ӵ�ͼ����Ϣ:" << endl;
    ofstream fout;
    fout.open(BookPath, ios::app);
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    book newBook;
    cin.ignore();//����������Ŀո�
    cout << "ͼ����: ";
    getline(cin, newBook.num);
    cout << "ͼ������: ";
    getline(cin, newBook.name);
    cout << "�����������: ";
    cin >> newBook.quantity; // ����Ĭ������Ϊ1
    newBook.borrowed = 0; // ����Ĭ�Ͻ������Ϊ0

    // �����Ƿ��Ѵ��ڸñ�ŵ�ͼ��
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
        cout << "ͼ���Ѵ��ڣ���������һ����" << endl;
        // ��ԭ�м�¼������һ��ͼ�������
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
                newBook.quantity++; // ��������
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
    cout << "ͼ����ӳɹ�!" << endl;
}
void deleteBook()
{
    string bookNum;
    cout << "������Ҫɾ����ͼ����: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
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
        cout << "ͼ��ɾ���ɹ�!" << endl;
    }
    else
    {
        cout << "�Ҳ�����ͼ����!" << endl;
    }
}
void borrowBook(account& user)
{
    string bookNum;
    cout << "������Ҫ���ĵ�ͼ����: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
        fin.close();
        return;
    }

    string temp;
    bool found = false;
    Time borrowTime;
    while (getline(fin, temp))//�����ļ�,����ͼ��
    {
        stringstream ss(temp);
        string name, num;
        int quantity;
        int borrowed;
        ss >> name >> num >> quantity >> borrowed;
        if (num == bookNum && quantity - borrowed > 0)//���ҵ�,���޸��鼮��Ϣ
        {
            found = true;
            fout << name << " " << num << " " << quantity << " " << borrowed + 1;
            //�Ϸ�������������
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

    if (found)//����ɹ�,��������¼
    {
        cout << "ͼ����ĳɹ�!" << endl;

        ofstream recordOut;
        recordOut.open(BorrowRecordPath, ios::app);//��д��ʽ�򿪼�¼�ĵ�
        if (!recordOut)
        { 
            cout << "�ļ���ʧ��...������";
            return;
        }
        //��������¼
        recordOut << user.name << " " << bookNum << " " << borrowTime.y << " " << borrowTime.m << " " << borrowTime.d << endl;
        recordOut.close();
    }
    else
    {
        cout << "��ͼ���ѱ�����򲻴���!" << endl;
    }
}
void returnBook(account& user)
{
    string bookNum;
    cout << "������Ҫ�黹��ͼ����: ";
    cin >> bookNum;
    Time returnTime;
    cout << "������黹ʱ��,��ʽYYYY/MM/DD" << endl;
    char tempch;
    cin >> returnTime.y >> tempch >> returnTime.m >> tempch >> returnTime.d;
    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    ofstream fout;
    fout.open("temp.txt");
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
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
        cout << "ͼ��黹�ɹ�!" << endl;
        //�޸ļ�¼�ļ�:
        fin.open(BorrowRecordPath);
        if (!fin)
        {
            cout << "�ļ���ʧ��...������";
            return;
        }
        fout.open("temp.txt");
        if (!fout)
        {
            cout << "�ļ���ʧ��...������";
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
        cout << "��ͼ��δ������򲻴���!" << endl;
    }
}
void showAllBooks()
{
    cout << "��ǰ���йݲ�ͼ������:" << endl;
    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
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
        cout << "ͼ������:" << name << endl;
        cout << "ͼ����: " << num << endl;
        cout << "ͼ��״̬: " << "����" << quantity << "�� �ѽ��" << borrowed << "��" << endl;
    }

    fin.close();

}
void showBookInfo()
{
    string bookNum;
    cout << "������Ҫ��ѯ��ͼ����: ";
    cin >> bookNum;

    ifstream fin;
    fin.open(BookPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    string temp;
    bool found = false;
    while (getline(fin, temp))//���ļ������鼮��Ϣ
    {
        stringstream ss(temp);
        string name, num;
        int quantity, borrowed;
        ss >> name >> num >> quantity >> borrowed;
        if (num == bookNum)
        {
            found = true;
            cout << endl;
            cout << "ͼ������:" << name << endl;
            cout << "ͼ����: " << num << endl;
            cout << "ͼ��״̬: " << "����" << quantity << "�� �ѽ��" << borrowed << "��" << endl;
            break;
        }
    }

    fin.close();

    if (!found)
    {
        cout << "��ͼ�鲻����!" << endl;
    }
}
void showBorrowRecords()
{
    ifstream fin;
    fin.open(BorrowRecordPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    cout << "���ļ�¼����:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        cout << temp << endl;//չʾ���ļ�¼
    }

    fin.close();
}
void showBorrowRecords(account& user)
{
    ifstream fin;
    fin.open(BorrowRecordPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }

    cout << "�����˵Ľ��ļ�¼����:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        string name, num;
        Time t;
        stringstream ss(temp);
        ss >> name >> num >> t.y >> t.m >> t.d;
        if (name == user.name)
            cout << num << " " << t.y << "/" << t.m << "/" << t.d << endl;//�����ʽ:���� ������ ��/��/��
    }

    fin.close();
}
