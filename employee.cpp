#include"employee.h"

Employee::Employee(int m_Id, string m_Name, int m_DeptID)
{
	this->m_Id = m_Id;
	this->m_Name = m_Name;
	this->m_DeptId = m_DeptID;
}

void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" <<this->getDeptName()
		<< "\tְ����ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}