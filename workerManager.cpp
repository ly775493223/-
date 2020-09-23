#include"workerManager.h"

WorkManager::WorkManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ�����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "����Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ������Ҳ�Ϊ��
	int num = this->get_EmpNum();
	/*cout << "ְ������Ϊ��" << num << endl;*/
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
	this->init_Emp();

	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
			<< "  ������" << this->m_EmpArray[i]->m_Name
			<< "  ���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
		this->m_EmpArray[i]->showInfo();
	}*/
}

void WorkManager::Show_Menu()
{
	cout << "************************************************" << endl;
	cout << "**************��ӭʹ��ְ������ϵͳ**************" << endl;
	cout << "**************  0���˳��������  ***************" << endl;
	cout << "**************  1������ְ����Ϣ  ***************" << endl;
	cout << "**************  2����ʾְ����Ϣ  ***************" << endl;
	cout << "**************  3��ɾ����ְԱ��  ***************" << endl;
	cout << "**************  4���޸�ְ����Ϣ  ***************" << endl;
	cout << "**************  5������ְ����Ϣ  ***************" << endl;
	cout << "**************  6�����ձ������  ***************" << endl;
	cout << "**************  7����������ĵ�  ***************" << endl;
	cout << "************************************************" << endl;
}

//�˳�ϵͳ
void WorkManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

//���ְ��
void WorkManager::Add_Emp()
{
	cout << "��������ӵ�ְ��������" << endl;
	
	int addNum = 0; //�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ�Ĵ�С
		int newSize = this->m_EmpNum + addNum;
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�����ݴ����¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;   //ְ�����
			string name;	//ְ������
			int dSelect;	//ѡ����

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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
			//��������ְ��ְ�𱣴浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ���ռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//�����ļ���Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		
		//������Ϣ
		this->save();
	}
	else
	{
		cout << "������������" << endl;
	}
	system("pause");
	system("cls");	

}

//������Ϣ
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

//ͳ���ļ��е�����
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

//��ʼ��Ա��
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

		if (dId == 1) //��ͨԱ��
			worker = new Employee(id, name, dId);
		else if (dId == 2) //����
			worker = new Manager(id, name, dId);
		else //�ܲ�
			worker = new Boss(id, name, dId);

		this->m_EmpArray[index++] = worker;
	}
	//�ر��ļ�
	ifs.close();
}

//��ʾְ��
void WorkManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��";
	else
	{
		cout << "������Ҫɾ����ְ����ţ�";
		int id;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) //ְ�����ڣ�ɾ��
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
			cout << "ɾ��ְ��������" << endl;
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//�޸�ְ��
void WorkManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	else
	{
		cout << "�������޸ĵ�ְ����ţ�";
		int id;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)  //ְ�����ڣ��޸�
		{
			//�ͷ�����
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "�鵽" << id << "��Ա������������ְ���ţ�" << endl;
			cin >> newId;
			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;

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

			//��������
			this->m_EmpArray[index] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else
			cout << "�޸�ְ��������" << endl;
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "��ѡ����ҷ�ʽ" << endl;
		cout << "1������Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)
		{
			cout << "������ְ����ţ�";
			int id;
			cin >> id;

			int res = this->IsExist(id);
			if (res != -1)
			{
				this->m_EmpArray[res]->showInfo();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else if (select == 2)
		{
			cout << "������ְ��������";
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
				cout << "����ʧ��" << endl;
			}
		}
		else
		{
			cout << "����ʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

//���ձ������
void WorkManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1��������������" << endl;
		cout << "2�����ս�������" << endl;

		int select = 0;
		cin >> select;
		
		//����
		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  //����
				{
					if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						Worker* temp = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[j];
						this->m_EmpArray[j] = temp;
					}
				}

				else         //����
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
	cout << "����ɹ�" << endl;
	this->save();
	this->Show_Emp();
}

//���
void WorkManager::Clear_Emp()
{
	cout << "ȷ������밴1" << endl;
	int select;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ  ios::trunc  �������ɾ�������´���
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
		cout << "��ճɹ�" << endl; 
	}
	system("pause");
	system("cls");
}

WorkManager::~WorkManager()
{

}
