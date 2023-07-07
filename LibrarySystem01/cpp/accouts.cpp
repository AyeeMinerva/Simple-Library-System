#include "common.h"
#include "accounts.h"
//�˻����˻�����
void secretInput(istream& in,string &temp)
{
    temp="";
    //����ļ�������
    char ch, inputPassword[105];
    int intdx = 0;
    while ((ch = _getch()) != '\r')//������Ĳ��ǻس���ʱ��ͼ�������
    {
        if (ch != '\b')
        {
            cout << "*";
            inputPassword[intdx++] = ch;
        }//���û�������˸������Ļ�����һ��*
        else
        {
            if (intdx > 0)//��ȫ��ɾ���������˸�
            {
                cout << '\b';
                cout << " ";
                cout << '\b';
                intdx--;
            }
        }//��������˸�������һ���˸�Ȼ���ڽ��ϴ������*��Ϊ�ո�Ȼ������˸�
    }
    cout << endl;
    for (int di = 0; di < intdx; di++)
    {
        temp += inputPassword[di];//���ַ����������ʱ�˻�������
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
    cout << "//���¼��" << endl;
    cout << "//�����������˺�:";
    cin >> user.name;
    cout << "//��������������:";
    secretInput(cin,user.password);
    loginCompare(user);//��¼�Ƚϼ��
    if (user.job >= 0)//������ڸ��û����û����,�����
    {
        cout << "��ӭ��½��" << jobs[user.job] << " " << user.name << endl;
        system("pause");//��ͣչʾ��½��ӭ��Ϣ
        return true;
    }
    else
    {
        cout << "�û������������!" << endl;
        return false;
    }
}
bool addAccount()
{
   
    account temp;
    cout << "ע�Ὺʼ:" << endl;
    cout << "�������˺�:";
    cin >> temp.name;

    //�û��Ƿ���ڵļ��
    ifstream fin;
    fin.open(AccountPath);
    account test;
    while (fin >> test.name >> test.password >> test.job)
    {
        if (temp.name == test.name)
        {
            cout << "���û����ѱ�ע��,������!" << endl;
            return false;//���û��Ѵ�����ֱ�ӷ���ע��ʧ��
        }
    }
    fin.close();

    //���û������������ע��
    cout << "����������:";
    secretInput(cin,temp.password);
    string temppassword;
    cout << "��ȷ������:";//����Ķ�����֤
    secretInput(cin, temppassword);
    if (temppassword != temp.password)
    {
        cout << "�������벻һ��,���������ע��!!" << endl;
        return false;
    }
    cout << "�������û����: ����(0), ����Ա(1), ��������Ա(2): ";
    cin >> temp.job;
    //����½��û���Ϣ
    ofstream fout;
    fout.open(AccountPath, ios::app);
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
        return false;
    }
    fout << temp.name << " " << temp.password << " " << temp.job << endl;
    fout.close();
    return true;
}
bool modifyAccount()
{
    cout << "������Ҫ�޸�������˻��û���:" << endl;
    string tempName;
    cin >> tempName;
    ifstream fin;
    fin.open(AccountPath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return false;
    }
    account temp;
    bool exist = false;
    string tempFileData = ""; //��ʱ�����ļ�����
    while (fin >> temp.name >> temp.password >> temp.job)
    {
        if (temp.name == tempName)
        {
            cout << "���ҵ����û�����ǰ��ϢΪ:" << endl;
            cout << temp.name << ' ' << temp.password << ' ' << temp.job << endl;
            cout << "����������Ϣ:" << endl;
            cout << "�û���:";
            cin >> temp.name;
            //�������뼰����Ķ�����֤
            cout << "����������:";
            secretInput(cin, temp.password);
            string temppassword;
            cout << "��ȷ������:";//����Ķ�����֤
            secretInput(cin, temppassword);
            if (temppassword != temp.password)
            {
                cout << "�������벻һ��,����������޸�!!" << endl;
                return false;
            }
            cout << "�û����: ����(0), ����Ա(1), ��������Ա(2): ";
            cin >> temp.job;
            exist = true;
        }
        tempFileData += temp.name + ' ' + temp.password + ' ' + to_string(temp.job) + '\n';
    }
    if (!exist)
        cout << "���û�������!" << endl;
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
        cout << "�ļ���ʧ��...������";
        return;
    }

    cout << "�����û�����:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, password;
        int job;
        ss >> name >> password >> job;
        if (jobs[job] == "����")
        {
            cout << "�û���: " << name << endl;
            cout << "�û����: " << jobs[job] << endl;
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
        cout << "�ļ���ʧ��...������";
        return;
    }

    cout << "ͼ�����Ա����:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        stringstream ss(temp);
        string name, password;
        int job;
        ss >> name >> password >> job;
        if (jobs[job] == "ͼ�����Ա")
        {
            cout << "�û���: " << name << endl;
            cout << "�û����: " << jobs[job] << endl;
            cout << endl;
        }
    }

    fin.close();
}
