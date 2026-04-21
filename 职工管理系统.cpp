//职工管理系统的入口函数
#define _CRT_SECURE_NO_WARNINGS
#include "workerManager.h"
//#include"worker.h"
//#include"employee.h"
//#include"manager.h"
//#include"boss.h"
using namespace std;

int main()
{
	////测试代码，创建一个员工对象，调用成员函数显示个人信息
	//Worker* worker = new Employee(1, "张三", 1);//使用父类指针指向子类对象，利用多态调用成员函数
	//worker->showInfo();//调用成员函数显示个人信息
	//delete worker;//释放内存

	//worker = new Manager(2, "李四", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "王五", 3);
	//worker->showInfo();
	//delete worker;


	//实例化一个管理者的对象
	WorkerManager wm;

	int choice = 0;//定义一个变量用来接收用户输入的选项

	while (true)
	{
		//调用显示菜单成员函数
		wm.Show_Menu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;//接收用户的选项
		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://增加职工信息
			wm.Add_Emp();
			break;
		case 2://显示所有职工信息
			wm.Show_Emp();
			break;
		case 3://删除职工信息
			wm.Del_Emp();
			break;
		case 4://修改职工信息
			wm.Mod_Emp();
			break;
		case 5://查找职工信息
			wm.Find_Emp();
			break;
		case 6://排序职工信息
			wm.Sort_Emp();
			break;
		case 7://清空文档
			wm.Clean_File();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}




	system("pause");

	return 0;
}