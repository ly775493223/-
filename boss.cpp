#include"boss.h"

Boss::Boss(int m_Id, string m_Name, int m_DeptID)
{
	this->m_Id = m_Id;
	this->m_Name = m_Name;
	this->m_DeptId = m_DeptID;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\tְ�𣺹���˾��С����" << endl;
}

string Boss::getDeptName()
{
	return string("�ܲ�");
}