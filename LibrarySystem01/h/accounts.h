#pragma once
#include "common.h"
void secretInput(istream& in, string& temp);
// �������뺯�����������뵽temp��,��*���ڸ�

void loginCompare(account& user);
// ��¼�ȽϺ��������ڱȽ��û��ṩ���˻���Ϣ��ϵͳ�б�����˻���Ϣ�Ƿ�ƥ��

bool login(account& user);
// ��¼�����������û���¼��������ʾ�û�������Ϣ�����õ�¼�ȽϺ����Ƚ�

void viewReaders();
// �鿴���ߺ�����������ʾϵͳ�����ж����˻�����Ϣ

void viewBookAdmins();
// �鿴ͼ�����Ա������������ʾϵͳ������ͼ�����Ա�˻�����Ϣ

bool addAccount();
// ����˻��������������˻��ı���׷���µ��˻�

bool modifyAccount();
// �޸��˻����������ڲ�ѯ���޸�ϵͳ���Ѵ��ڵ��˻���Ϣ���粻�������˳�
