#include<iostream>
using namespace std;
#include"workerManager.h"

#include"boss.h"
#include"manager.h"
#include"employee.h"
#include"worker.h"

int main()
{
	//测试代码
	/*Worker* worker = NULL;
	worker = new Employee(1,"张三",1);
	worker->showInfo();

	Worker* manager = NULL;
	manager = new Manager(2, "李四", 2);
	manager->showInfo();

	Worker* boss = NULL;
	boss = new Boss(3, "王五", 3);
	boss->showInfo();*/


	WorkManager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();
		cout << "请输入您的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clear_Emp();
			break;

		default:
			system("cls");
			break;
		}

	}

}