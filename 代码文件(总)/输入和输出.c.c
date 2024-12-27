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
void Findemployee(){
	printf("================管理员身份进入了查询系统=================\n");
	printf("=1.按照姓名查询                                         =\n");
	printf("=2.按照性别查询                                         =\n");
	printf("=3.按照工资查询                                         =\n");
	printf("=4.按照年龄查询                                         =\n");
	printf("=5.展现全部信息                                         =\n");
	printf("=========================================================\n");
	printf("=请输入您的查询方式:");
	int choice=0;
	//查询条件变量声明
	char cxtj[20];
	double minmoneytj = 0,maxmoneytj = 1;
	int  minage = 0,maxage = 1;
	//以下是计算总人数，平均工资，平均年龄的变量声明
	int count=0;
	double allmoney=0;
	int allage=0;
	//选择查询方式
	scanf("%d",&choice);
	switch (choice) {
	case 1:
		printf("=请输入需要查询员工的姓名:");
		scanf("%s",cxtj);
		break;
	case 2:
		printf("=请输入需要查询员工的性别:");
		scanf("%s",cxtj);
		break;
	case 3:
		printf("=请输入需要查询员工的工资(输入一个范围)\n");
		printf("=MAX:");
		scanf("%lf",&maxmoneytj);
		printf("=MIN:");
		scanf("%lf",&minmoneytj);
		break;
	case 4:
		printf("=请输入需要查询员工的年龄(输入一个范围)\n");
		printf("=MAX:");
		scanf("%d",&maxage);
		printf("=MIN:");
		scanf("%d",&minage);
		break;	
	case 5:
		printf("=为您展现了所有员工信息:)\n");
		break;
	default:
		printf("=您所选择的查询方式尚未开发:(\n");
		
		break;
	}
	//输出信息
	int i = 0;
	for(i=0;i<employeegs;i++){
		if(choice==5
			||
			(choice ==1&&strstr(employeesz[i].name,cxtj))
			||
			(choice==2&&strstr(employeesz[i].gender,cxtj))
			||
			(choice==3&&employeesz[i].money>=minmoneytj&&employeesz[i].money<=maxmoneytj)
			||
			(choice==4&&employeesz[i].age>=minage&&employeesz[i].age<=maxage)){
			printf("========================================\n");
			printf("=\t姓名：%s\n",employeesz[i].name);
			printf("=\t性别：%s\n",employeesz[i].gender);
			printf("=\t年龄：%d\n",employeesz[i].age);
			printf("=\t工资：%lf\n",employeesz[i].money);
			printf("=\t电话：%s\n",employeesz[i].phone);
			printf("=\t地址：%s\n",employeesz[i].location);
			//计算总人数和总工资与总年龄方便后续计算平均数
			count++;
			allmoney+=employeesz[i].money;
			allage+=employeesz[i].age;
		}
	}
	//计算平均数和输出总人数
	printf("======总人数为：%d\n",count);
	if(count == 0){
		printf("由于总人数为0，不可计算平均数据\n");
	}else{
		double argmoney = allmoney/count;
		printf("======平均工资为：%.1lf\n",argmoney);
		double argage = (double)allage/count;
		printf("======平均工资为：%.1lf\n",argage);
	}
	
}
