#include "common.h"
#include "helps.h"
//֪ͨ�����չʾ
bool Hello()
{
    cout << "//////////////////////////////////////" << endl;
    cout << "//        ��ӭʹ��ͼ�����ϵͳ      //" << endl;
    cout << "//////////////////////////////////////" << endl;
    return true;
}
void help(int job)
{
    cout << "//////////////////////////////////////" << endl;
    cout << "//              �˵�                //" << endl;
    switch (job)
    {
    case 0:
        cout << "//1. ����" << endl;
        cout << "//2. ����" << endl;
        cout << "//3. ��ѯ������Ϣ" << endl;
        cout << "//4. ��ѯͼ����Ϣ" << endl;
        cout << "//5. ��ѯ����ͼ����Ϣ" << endl;
        cout << "//6. �鿴����" << endl;
        cout << "//7. ע��" << endl; 
        break;
    case 1:
        cout << "//1. ���ͼ��" << endl;
        cout << "//2. ɾ��ͼ��" << endl;
        cout << "//3. ��ѯ����ͼ����Ϣ" << endl;
        cout << "//4. ��ѯδ������Ϣ" << endl;
        cout << "//5. ��������" << endl;
        cout << "//6. ע��" << endl;
        break;
    case 2:
        cout << "//1. ע�����˻�" << endl;
        cout << "//2. �޸��˻���Ϣ" << endl;
        cout << "//3. �鿴���ж����û���Ϣ" << endl;
        cout << "//4. �鿴����ͼ�����Ա" << endl;
        cout << "//5. ע��" << endl;
        break;
    }
    cout << "//////////////////////////////////////" << endl;
}