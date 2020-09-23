#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Manager :public Worker
{
public:
	//构造函数
	Manager(int m_Id, string m_Name, int m_DeptID);

	//显示个人信息
	virtual void showInfo();
	//获取部门名称
	virtual string getDeptName();
};