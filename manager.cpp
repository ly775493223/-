#include"manager.h"

Manager::Manager(int m_Id, string m_Name, int m_DeptID)
{
	this->m_Id = m_Id;
	this->m_Name = m_Name;
	this->m_DeptId = m_DeptID;
}

void Manager::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t职责：完成总裁分配的任务" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}