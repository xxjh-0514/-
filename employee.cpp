//普通员工类的实现文件
#define _CRT_SECURE_NO_WARNINGS
#include"employee.h";

//添加作用域限定符Employee::,表示以下函数是Employee类的成员函数

//构造函数
Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;//职工编号
	this->m_Name = name;//职工姓名
	this->m_DeptId = did;//部门编号


}
//显示个人信息
void Employee::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t职工的姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()//调用获取岗位名称的函数
		<< "\t岗位职责：完成经理交代的任务" << endl;
}

//获取岗位名称
string Employee::getDeptName()
{
	return "员工";
 }