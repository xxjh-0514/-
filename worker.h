//这个头文件是抽象类worker的头文件，不做实例化对象，提供接口给子类重写实现，子类才能实例化对象
#pragma once
#include<iostream>
#include<string>
using namespace std;
 

//职工抽象类
class Worker
{
public:

	//以下是成员函数（行为）
	//显示个人信息
	virtual void showInfo() = 0;//纯虚函数没有实现，子类必须重写才能实例化对象

	//获取岗位名称
	virtual string getDeptName() = 0;//纯虚函数没有实现，子类必须重写才能实例化对象



	//以下是成员属性
	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//部门编号
	int m_DeptId;
};
