//职工管理系统的实现文件

#define _CRT_SECURE_NO_WARNINGS
#include "workerManager.h"

//类内声明的函数在类外实现
//构造函数的实现
WorkerManager::WorkerManager()
{
	ifstream ifs;//创建输入文件流对象
	ifs.open(FILENAME, ios::in);//以输入的方式打开文件--读文件
	//1、文件不存在的情况
	if (!ifs.is_open())//如果文件没有成功打开
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组的指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();//关闭文件
		return;//由于文件不存在，直接返回退出构造函数，不执行后续代码
	}

	//2、文件存在但数据为空的情况
	char ch;
	ifs >> ch;//从文件中读取一个字符，如果读取失败，说明文件为空
	if (ifs.eof())//
	{
		//文件为空
		//cout << "文件为空" << endl;//测试文件是否为空的代码
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组的指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();//关闭文件
		return;
	}

	//3、文件存在且数据不为空的情况
	int num = this->get_EmpNum();//统计文件中的人数
	//cout << "职工的人数为：" << num << endl;//测试统计人数的函数是否成功
	this->m_EmpNum = num;//记录职工人数

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];//开辟一个新的职工数组，大小为职工人数
	//将文件中的数据存到数组中
	this->init_Emp();//调用初始化员工函数将文件中的数据存到数组中
	
	////测试是否成功的代码
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "职工编号:" << this->m_EmpArray[i]->m_Id
	//		<< "姓名:" << this->m_EmpArray[i]->m_Name
	//		<< "部门编号:" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

//显示菜单函数的实现
void WorkerManager::Show_Menu()
{
	cout << "****************************" << endl;
	cout << "****欢迎使用职工管理系统****" << endl;
	cout << "*******0.退出管理系统*******" << endl;
	cout << "*******1.增加职工信息*******" << endl;
	cout << "*******2.显示职工信息*******" << endl;
	cout << "*******3.删除离职职工*******" << endl;
	cout << "*******4.修改职工信息*******" << endl;
	cout << "*******5.查找职工信息*******" << endl;
	cout << "*******6.按照编号排序*******" << endl;
	cout << "*******7.清空所有文档*******" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

//退出系统函数的实现
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次再使用" << endl;
	system("pause");
	exit(0);//退出程序
}


//添加职工的函数实现
void WorkerManager::Add_Emp()
{
	cout << "请输入添加的职工数量:" << endl;

	int addNum = 0;//定义一个变量用来接收用户输入的职工数量
	cin >> addNum;//接收用户输入的职工数量 
	if (addNum>0)
	{
		//添加
		//计算添加新的空间大小
		int newSize = this->m_EmpNum + addNum;//新的空间大小=原来职工的人数+新添加的职工人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];//开辟一个新的职工数组，大小为新空间大小
		//Worker** = 存放「职工指针」的数组，Worker** newSpace= 定义一个数组，用来存所有职工对象的地址=职工数组
		//new Worker* [newSize]
		//new：在堆区开辟空间
		//Worker* ：数组里每个元素都是 职工指针
		//[newSize]：数组能装 newSize 个职工指针

		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray!=NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];//将原来的数据拷贝到新空间下
			}
		}
		//添加新的数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个新职工的编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名：" << endl;
			cin >> name;
			cout << "请选择该职工的岗位:" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;//定义一个职工指针用来指向新创建的职工对象
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;//位置为原来职工人数+新添加的职工人数
		}

		//释放原来的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		//保存数据到文件中
		this->save();//调用保存文件函数将数据写入到文件中
	}
	else
	{
		cout << "输入数据有误，请重新输入" << endl;
	}
	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

//保存文件函数的实现
void WorkerManager::save()
{
	ofstream ofs;//创建输出文件流对象
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件--写文件

	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		//将职工的编号、姓名、部门编号写入到文件中，以空格分隔
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}

//统计文件中的人数的函数实现
int WorkerManager::get_EmpNum()
{
	ifstream ifs;//创建输入文件流对象
	ifs.open(FILENAME, ios::in);//打开文件--读文件

	int id;//存放职工编号
	string name;//存放职工姓名
	int dId;//存放部门编号

	int num = 0;//记录人数的变量
	//从文件中读取职工编号、姓名、部门编号，如果读取成功，说明还有职工信息
	//如果读取失败，说明已经到了文件末尾，没有更多职工信息了
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量，每读到一个职工的信息，就将人数变量加1
		num++;
	}

	return num;//返回统计到的人数
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;//创建输入文件流对象
	ifs.open(FILENAME, ios::in);//打开文件--读文件

	int id;//存放职工编号
	string name;//存放职工姓名
	int dId;//存放部门编号

	int index = 0;//定义一个变量用来记录职工数组的下标位置
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;//定义一个职工指针用来指向新创建的职工对象

		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else //老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;//将创建的职工指针保存到职工数组中，位置为index
		index++;//下标位置加1
	}

	//关闭文件
	ifs.close();
}


//显示员工信息函数实现
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();//调用职工数组中每个职工指针指向的职工对象的显示个人信息函数	
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}



//删除职工信息函数的实现
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		//按照职工编号删除员工
		cout << "请输入要删除的职工编号：" << endl;
		int id = 0;//定义一个变量用来接收用户输入的职工编号
		cin >> id;//接收用户输入的职工编号

		int index = this->IsExist(id);//
		if (index!=-1)//说明职工存在，并且要删除掉index位置上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//职工人数减一，更新数组中记录的人员个数
			//数据同步更新到文件中
			this->save();//调用保存文件函数将数据写入到文件中

			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}


//判断职工是否存在的函数实现
//如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;//定义一个变量用来记录职工所在数组中的位置，初始值为-1表示不存在

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//如果职工编号匹配，说明找到了该职工，返回职工所在数组中的位置
			index = i;
			break;//跳出循环
		}
	}
	return index;//返回职工所在数组中的位置，如果没有找到，返回-1
}

//修改职工信息函数实现
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)//如果文件不存在或者记录为空
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改的职工编号：" << endl;
		int id = 0;//定义一个变量用来接收用户输入的职工编号
		cin >> id;//接收用户输入的职工编号	

		int ret = this->IsExist(id);//调用判断职工是否存在的函数，返回职工所在数组中的位置
		if (ret!=-1)
		{
			//查找到编号的职工

			delete this->m_EmpArray[ret];//删除原来职工数组中位置为ret的职工对象，释放内存

			int newId = 0;//新的职工编号
			string newName=" ";//新的职工姓名
			int dSelect = 0;//新的部门选择

			cout << "查到编号为" << id << "的职工，请输入新的职工编号：" << endl;
			cin >> newId;

			cout << "请输入新的职工姓名：" << endl;
			cin >> newName;

			cout << "请选择新的职工岗位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;


			cin >> dSelect;

			Worker* worker = NULL;//定义一个职工指针用来指向新创建的职工对象
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
			}

			//更新数据到数组中
			this->m_EmpArray[ret] = worker;//将新创建的职工指针保存到职工数组中，位置为ret

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();//调用保存文件函数将数据写入到文件中
		}
		else
		{
			//没有找到编号的职工
			cout << "修改失败，未找到编号为" << id << "的职工！" << endl;
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}



//查找职工信息函数的实现
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)//如果是空文件就停止操作
	{
		cout << "文件不存在或者记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;

		int select = 0;//定义一个变量用来接收用户输入的查找方式
		cin >> select;//接收用户输入的查找方式

		if (select==1)
		{
			//按照编号查
			int id = 0;//定义一个变量用来接收用户输入的职工编号
			cout << "请输入要查找的职工编号：" << endl;
			cin >> id;//接收用户输入的职工编号

			int ret = IsExist(id);//调用判断职工是否存在的函数，返回职工所在数组中的位置
			if (ret!=-1)
			{
				//找到职工
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();//调用职工数组中位置为ret的职工指针指向的职工对象的显示个人信息函数
			}
			else
			{
				cout << "查找失败，未找到编号为" << id << "的职工！" << endl;
			}
		}
		else if (select==2)
		{
			//按姓名查找
			string name = " ";//定义一个变量用来接收用户输入的职工姓名
			cout << "请输入要查找的职工姓名：" << endl;
			cin >> name;//接收用户输入的职工姓名

			//加入判断是否查到的标志,按姓名查找：可重复 → 必须遍历完 → 必须用 flag 记录是否找到过
			//flag 的作用：记住 “整个遍历过程中，有没有成功匹配过哪怕一次”
			bool flag = false;//初始值为false表示没有查到

			for (int i = 0; i < m_EmpNum; i++)//遍历数组查找是否有这个人
			{
				if (this->m_EmpArray[i]->m_Name == name)//在当前这个职工管理对象里，拿出第i号员工，对比他的姓名和传进来的name，看是不是同一个人
				{
					cout << "查找成功！该职工信息如下：" << endl;
					flag = true;//如果查到职工了，就将标志改为true
					this->m_EmpArray[i]->showInfo();//调用职工数组中位置为i的职工指针指向的职工对象的显示个人信息函数
				}
			}
			if (flag==false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入的选项有误，请重新输入！" << endl;
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}


//按照编号排序函数的实现
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按照职工编号升序" << endl;
		cout << "2.按照职工编号降序" << endl;
		
		int select = 0;//定义一个变量用来接收用户输入的排序方式
		cin >> select;//接收用户输入的排序方式
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值或最大值的下标
			for (int j = i + 1; j < this->m_EmpNum; j++)//从i+1开始遍历，找到剩余元素中最小值或最大值的下标
			{
				if (select == 1)//升序
				{
					//如果当前最小值的职工编号大于第j个职工的编号，说明第j个职工的编号更小
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;//更新最小值的下标

					}
				}
				else//降序
				{
					//如果当前最大值的职工编号小于第j个职工的编号，说明第j个职工的编号更大 
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//判定一开始认定的最小值或最大值是不是计算的最小值或最大值，如果不是，就交换
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];//定义一个临时职工指针用来交换
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];//将最小值或最大值的职工指针赋值给第i个位置
				this->m_EmpArray[minOrMax] = temp;//将临时职工指针赋值给最小值或最大值的位置
				//交换完成后，第i个位置就是当前剩余元素中最小值或最大值了
				//继续下一轮循环，直到所有元素都排序完成
			}
			
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//调用保存文件函数将数据写入到文件中
		this->Show_Emp();//调用显示员工信息函数显示排序后的员工信息
	}
}


//清空文件操作函数的实现
void WorkerManager::Clean_File()
{
	cout << "确认清空吗？"<<endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;//定义一个变量用来接收用户输入的选项
	cin >> select;//接收用户输入的选项

	if (select==1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//以截断的方式打开文件，清空文件内容
		ofs.close();//关闭文件

		if (this->m_EmpArray!=NULL)//职工数组是否已经创建、是否有效、不为空
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)//遍历职工数组
			{
				delete this->m_EmpArray[i];//删除职工数组中每个职工指针指向的职工对象，释放内存
				this->m_EmpArray[i] = NULL;//将职工数组中每个职工指针置空
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;//删除职工数组指针，释放内存
			this->m_EmpArray = NULL;//将职工数组指针置空
			this->m_EmpNum = 0;//将职工人数置零
			this->m_FileIsEmpty = true;//将文件是否为空的标志置为true
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}


//析构函数的实现
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray!=NULL)//如果职工数组指针不为空
	{
		delete[] this->m_EmpArray;//释放职工数组指针指向的空间
		this->m_EmpArray = NULL;//将职工数组指针置空
	}
}