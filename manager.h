#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Manager :public Worker
{
public:
	//���캯��
	Manager(int m_Id, string m_Name, int m_DeptID);

	//��ʾ������Ϣ
	virtual void showInfo();
	//��ȡ��������
	virtual string getDeptName();
};