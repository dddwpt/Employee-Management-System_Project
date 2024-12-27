#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//员工的数据
struct Employee{
	char name[50];//姓名
	char gender[10];//性别
	char phone[11];//电话11位
	double money;//工资
	int age;//年龄
	char location[20];//地址
};
//员工结构体数组
struct Employee employeesz[100];
//员工个数
int employeegs = 0;
int  getemployeename(char *name);
//添加员工
void addyg(){
	int yonflag = 1;
	while(yonflag == 1){
		//输入员工信息
		printf("请输入需要添加的员工姓名\n");
		scanf("%s",employeesz[employeegs].name);
		int nameflag = getemployeename(employeesz[employeegs].name);
		if(nameflag > -1){
			printf("名字已经存在\n");
			break;
		}
		printf("请输入新员工性别\n");
		scanf("%s",employeesz[employeegs].gender);
		printf("请输入新员工电话\n");
		scanf("%s",employeesz[employeegs].phone);
		printf("请输入新员工的工资\n");
		scanf("%lf",&employeesz[employeegs].money);
		printf("请输入新员工的地址\n");
		scanf("%s",employeesz[employeegs].location);
		printf("请输入新员工的年龄\n");
		scanf("%d",&employeesz[employeegs].age);
		employeegs++;
		getchar();
		printf("是否继续录入(继续输入1，终止输入2)：");
		scanf("%d",&yonflag);
		
	}
}
//修改员工信息
void changeemployee(){
	
	//检查输入姓名是否合法
	printf("请输入要修改员工的姓名\n");
	char c[20];
	
	scanf("%s",c);
	if(getemployeename(c)==-1){
		printf("未查询到此员工信息请选择添加员工操作\n");
		return ;
	}
	int i=0,count=0;
	for(i=0;i<employeegs;i++){
		if(strstr(employeesz[i].name,c)){
			count = i;
		}
	}
	printf("请输入性别：");
	scanf("%s",employeesz[count].gender);
	printf("请输入电话：");
	scanf("%s",employeesz[count].phone);
	printf("请输入工资：");
	scanf("%lf",&employeesz[count].money);
	printf("请输入年龄：");
	scanf("%d",&employeesz[count].age);
	printf("请输入地址：");
	scanf("%s",employeesz[count].location);
	printf("修改成功\n");

}
//删除员工
void Deletempolyee(){
	printf("=请输入要删除员工的姓名\n");
	char c[20];
	scanf("%s",c);
	if(getemployeename(c)==-1){
		printf("=未查询到此员工信息请选择添加员工操作\n");
		return ;
	}
	int i=0,count=0;
	for(i=0;i<employeegs;i++){
		if(strstr(employeesz[i].name,c)){
			count = i;
		}
	}
	int nums=0;
	for(nums = count;nums<employeegs-1;nums++){
		employeesz[nums]=employeesz[nums+1];
	}
	employeegs--;
	
	printf("已经删除了该员工\n\n");
}

