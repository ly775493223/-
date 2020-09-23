#include"employee.h"

Employee::Employee(int m_Id, string m_Name, int m_DeptID)
{
	this->m_Id = m_Id;
	this->m_Name = m_Name;
	this->m_DeptId = m_DeptID;
}

void Employee::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" <<this->getDeptName()
		<< "\t职责：完成经理分配的任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}