//职工管理系统的头文件，包含了职工管理系统的类定义和成员函数声明
#pragma once//防止头文件重复包含
#include<iostream>//包含输入输出流头文件
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"//定义文件名为empFile.txt
using namespace std;//使用标准的命名空间

class WorkerManager
{
public:
	//构造函数
	WorkerManager();

	//显示菜单函数
	void Show_Menu();

	//退出系统函数
	void ExitSystem();


	//记录职工人数
	int m_EmpNum;


	//职工数组指针
	Worker** m_EmpArray;

	//添加职工人数
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空 标志
	bool m_FileIsEmpty;

	//统计文件中的人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示员工信息
	void Show_Emp();

	//删除职工信息
	void Del_Emp();

	//判断职工是否存在 如果存在返回职工所在数组中的位置，不存在返回-1
	int IsExist(int id);

	//修改职工信息
	void Mod_Emp();

	//查找职工信息
	void Find_Emp();

	//按照编号排序
	void Sort_Emp();

	//清空文件操作
	void Clean_File();

	//析构函数
	~WorkerManager();
};