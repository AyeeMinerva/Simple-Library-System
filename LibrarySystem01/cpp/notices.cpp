#include "common.h"
#include "notices.h"
//�����빫�����
bool newNotice()
{
    cout << "//����׼�������¹���....." << endl;
    ofstream fout;
    fout.open(NoticePath, ios::app);
    if (!fout)
    {
        cout << "�ļ���ʧ��...������";
        return false;
    }
    string temp;
    cout << "//������Ҫ�����Ĺ��棬����һ������Ctrl+Z��ϼ�����.." << endl;
    while (getline(cin, temp))
    {
        fout << temp << endl;
    }
    fout << endl;
    cin.clear();
    cin.ignore();
    fout.close();
    cout << "//�����½��Ĺ����ѱ�����" << endl;
    return true;
}
void showNotice()
{
    cout << "���ڲ�ѯ����.." << endl;
    ifstream fin;
    fin.open(NoticePath);
    if (!fin)
    {
        cout << "�ļ���ʧ��...������";
        return;
    }
    cout << "��ǰ��ѯ���Ĺ�������:" << endl;
    string temp;
    while (getline(fin, temp))
    {
        cout << temp << endl;
    }
    fin.close();
}

