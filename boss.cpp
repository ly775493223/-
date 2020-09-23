#include"boss.h"

Boss::Boss(int m_Id, string m_Name, int m_DeptID)
{
	this->m_Id = m_Id;
	this->m_Name = m_Name;
	this->m_DeptId = m_DeptID;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t职责：管理公司大小事务" << endl;
}

string Boss::getDeptName()
{
	return string("总裁");
}