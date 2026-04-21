//老板类的声明文件
#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

//老板类
class Boss :public Worker
{
public:
	//构造函数声明，参数列表包括职工编号、职工姓名、部门编号
	Boss(int id, string name, int did);


	//子类重写父类的纯虚函数（virtual可删可不删）

	//以下是成员函数（行为）
	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();
};
