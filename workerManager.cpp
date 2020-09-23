#include"workerManager.h"

WorkManager::WorkManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "数据为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在且不为空
	int num = this->get_EmpNum();
	/*cout << "职工人数为：" << num << endl;*/
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中
	this->init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id
			<< "  姓名：" << this->m_EmpArray[i]->m_Name
			<< "  部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
		this->m_EmpArray[i]->showInfo();
	}*/
}

void WorkManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "**************欢迎使用职工管理系统**************" << endl;
	cout << "**************  0、退出管理程序  ***************" << endl;
	cout << "**************  1、增加职工信息  ***************" << endl;
	cout << "**************  2、显示职工信息  ***************" << endl;
	cout << "**************  3、删除离职员工  ***************" << endl;
	cout << "**************  4、修改职工信息  ***************" << endl;
	cout << "**************  5、查找职工信息  ***************" << endl;
	cout << "**************  6、按照编号排序  ***************" << endl;
	cout << "**************  7、清空所有文档  ***************" << endl;
	cout << "************************************************" << endl;
}

//退出系统
void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

//添加职工
void WorkManager::Add_Emp()
{
	cout << "请输入添加的职工数量：" << endl;
	
	int addNum = 0; //保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间的大小
		int newSize = this->m_EmpNum + addNum;
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来数据存入新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;   //职工编号
			string name;	//职工姓名
			int dSelect;	//选择部门

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id,name,dSelect);
				break;
			case 2:
				worker = new Manager(id, name, dSelect);
				break;
			case 3:
				worker = new Boss(id, name, dSelect);
				break;
			default:
				break;
			}
			//将创建的职工职责保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原来空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更改新职工人数
		this->m_EmpNum = newSize;

		//更新文件不为空标志
		this->m_FileIsEmpty = false;
		
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		
		//保存信息
		this->save();
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
	system("pause");
	system("cls");	

}

//保存信息
void WorkManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//统计文件中的人数
int WorkManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) num++;
	
	return num;
}

//初始化员工
void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1) //普通员工
			worker = new Employee(id, name, dId);
		else if (dId == 2) //经理
			worker = new Manager(id, name, dId);
		else //总裁
			worker = new Boss(id, name, dId);

		this->m_EmpArray[index++] = worker;
	}
	//关闭文件
	ifs.close();
}

//显示职工
void WorkManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除职工
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空";
	else
	{
		cout << "请输入要删除的职工编号：";
		int id;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) //职工存在，删除
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();

			cout << "删除成功" << endl;
		}
		else
			cout << "删除职工不存在" << endl;
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//修改职工
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空" << endl;
	else
	{
		cout << "请输入修改的职工编号：";
		int id;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)  //职工存在，修改
		{
			//释放数组
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "查到" << id << "号员工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;

			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更新数据
			this->m_EmpArray[index] = worker;
			cout << "修改成功" << endl;
			this->save();
		}
		else
			cout << "修改职工不存在" << endl;
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请选择查找方式" << endl;
		cout << "1、按编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "请输入职工编号：";
			int id;
			cin >> id;

			int res = this->IsExist(id);
			if (res != -1)
			{
				this->m_EmpArray[res]->showInfo();
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "请输入职工姓名：";
			string name;
			cin >> name;

			bool flag = false;

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					this->m_EmpArray[i]->showInfo();

					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败" << endl;
			}
		}
		else
		{
			cout << "查找失败" << endl;
		}
	}
	system("pause");
	system("cls");
}

//按照编号排序
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按照升序排序" << endl;
		cout << "2、按照降序排序" << endl;

		int select = 0;
		cin >> select;
		
		//排序
		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  //升序
				{
					if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						Worker* temp = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[j];
						this->m_EmpArray[j] = temp;
					}
				}

				else         //降序
				{
					if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						Worker* temp = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[j];
						this->m_EmpArray[j] = temp;
					}
				}
			}
		}
	}
	cout << "排序成功" << endl;
	this->save();
	this->Show_Emp();
}

//清空
void WorkManager::Clear_Emp()
{
	cout << "确认清空请按1" << endl;
	int select;
	cin >> select;

	if (select == 1)
	{
		//打开模式  ios::trunc  如果存在删除并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl; 
	}
	system("pause");
	system("cls");
}

WorkManager::~WorkManager()
{

}
