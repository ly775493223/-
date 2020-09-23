#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Employee :public Worker
{
public:
	//构造函数
	Employee(int m_Id, string m_Name, int m_DeptID);

	//显示个人信息
	virtual void showInfo();
	//获取部门名称
	virtual string getDeptName();
};