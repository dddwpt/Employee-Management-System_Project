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
//以下是登录系统的制作
//密码与账户的数据储存结构
typedef struct users{
	char name[20];
	char zh[20];
	char mm[20];
}A;
int i=0;
//判断是否为管理员进入系统
int Flag=0;
//注册界面(注册成功返回1，未成功返回0)
int registerusers(){
	A b,a;
	char c[20];
	FILE *fp;
	printf("=========================================================\n");
	printf("=                     注        册                      =\n");
	printf("=                                                       =\n");
	printf("=========================================================\n");
	//读取文件Users.txt储存在与代码同目录下
	fp = fopen("Users.txt","r");
	fread(&b, sizeof(A), 1, fp);
	printf("请输入账号\n");
	scanf("%s",&a.zh);
	//验证账号是否已经被注册
	while(1)
	{
		if (strcmp(a.zh, b.zh))
		{
			if (!feof(fp))
			{
				fread(&b, sizeof(A), 1, fp);
			}
			else
			{
				break;
			}
		}
		else 
		{
			printf("该账号已经被注册\n");
			fclose(fp);
			return 0;
		}
	}
	//time为最大错误密码输入次数（注册）最大可以输入错误两次
	int time = 2;
	//设置密码环节，需要用户输入两次密码，第一次输入密码第二次确定密码
	do
	{
		printf("请设置密码:\n");
		i = 0;
		for (i = 0; i < 20; i++)
		{
			//_getch不可查看密码
			a.mm[i] = _getch();
			if (a.mm[i] == '\r')
			{
				break;
			}
			else
			{
				printf("*");
			}
		}
		a.mm[i] = '\0';
		printf("\n");
		printf("请确认密码:\n");
		i = 0;
		for (i = 0; i < 20; i++)
		{
			c[i] = _getch();
			if (c[i] == '\r')
			{
				break;
			}
			else
			{
				printf("*");
			}
		}
		c[i] = '\0';
		printf("\n");
		if (!strcmp( a.mm,c) )
		{
			
			printf("请输入用户名：");
			scanf("%s",&a.name);
			fp = fopen("Users.txt", "a");
			fwrite(&a,sizeof(A),1,fp);
			printf("%s,注册成功！\n", a.name);
			fclose(fp);
			return 1;
		}else
		{
			if (time != 0)
			{
				printf("密码错误！\n请重新输入密码\n您还有%d次机会\n", time);
				time--;
				continue;
			}
			else
			{
				printf("多次输入错误，即将退出！\n");
				fclose(fp);
			
				return 0;
			}
		}
		//若机会耗尽退出程序
	}while(time >=0);
}
//登录系统(成功登录返回1密码错误返回0)
int userslogin(){
	A a,b;
	FILE *fp;
	printf("=========================================================\n");
	printf("=                     登        录                      =\n");
	printf("=                                                       =\n");
	printf("=========================================================\n");
	printf("=输入您的账号：\n");
	scanf("%s",&b.zh);
	printf("=输入您的密码：\n");
	i = 0;
	for (i = 0; i < 20; i++)
	{
		b.mm[i] = _getch();
		if (b.mm[i] == '\r')
		{
			break;
		}
		else
		{
			printf("*");
		}
	}
	b.mm[i] = '\0';
	printf("\n");
	fp = fopen("Users.txt", "r");
	while (1)
	{
		fread(&a, sizeof(A), 1, fp);
		if (strcmp(b.zh,a.zh)==0)
		{
			break;
			
		}
		else
		{
			if (!feof(fp))
			{
				fread(&a, sizeof(A), 1, fp);
			}
			else
			{
				printf("账号或密码错误\n");
				fclose(fp);
				return 0;
			}
		}
	}
	if (strcmp(b.mm, a.mm)==0)
	{
		//发出提示“用户名”欢迎回来
		if(strcmp(a.name,"administrator")==0){
			Flag = 9;
		}
		printf("%s，欢迎回来\n",a.name);
		fclose(fp);
		return 1;
	}
	else
	{
		printf("密码错误！\n");
		fclose(fp);
		return 0;
	}
	
}
//功能菜单函数
void menu(){
	if(Flag == 9){
		printf("================您以管理员身份进入本系统=================\n");
		printf("=1.添加新员工                                           =\n");
		printf("=2.删除员工                                             =\n");
		printf("=3.进入查询页面                                         =\n");
		printf("=4.对员工进行排序                                       =\n");
		printf("=5.修改员工信息                                         =\n");
		printf("=6.退出本系统                                           =\n");
		printf("=请输入相应的操作序号来操作系统                         =\n");
		printf("=========================================================\n");
	}else if(Flag!=9){
		printf("================您以员工的身份进入本系统=================\n");
		printf("=1.进入查询页面                                         =\n");
		printf("=2.修改你的信息                                         =\n");
		printf("=3.退出本系统                                           =\n");
		printf("=请输入相应的操作序号来操作系统                         =\n");
		printf("=========================================================\n");
	}
}
//判断员工信息是否重复
int  getemployeename(char *name){
	int i=0;
	int flag=-1;
	//重复返回flag=-1；
	//不重复返回flag>-1；
	//默认不重复
	for(i=0;i<employeegs;i++){
		if(strcmp(name,employeesz[i].name)==0){
			//重复使用姓名,同时返回是哪一个员工的名字与输入新名字重复	
			flag = i;
			break;
		}
	}
	return flag;
}
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
//查询员工
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
//员工信息文件读写与储存
//员工信息的储存
void savewenjian(){
	FILE *fp;
	fp = fopen("Employee.txt","w+");
	int i;
	for(i=0;i<employeegs;i++){
		fprintf(fp,"%s %s %s %lf %d %s\n",employeesz[i].name,employeesz[i].gender,employeesz[i].phone,employeesz[i].money,employeesz[i].age,employeesz[i].location);
	}
	fclose(fp);
	printf(":) 已经为您自动保存员工信息！\n");
}
//员工信息的读取
void readwenjian(){
	FILE *fp;
	fp = fopen("Employee.txt","r");
	if(NULL==(fp = fopen("Employee.txt","r"))){
		printf("打开文件失败请检查程序文件是否完整\n");
		fclose(fp);
		return;
	}
	int i;
	while(
		fscanf(fp,"%s%s%s%lf%d%s\n",employeesz[i].name,employeesz[i].gender,employeesz[i].phone,&employeesz[i].money,&employeesz[i].age,employeesz[i].location) !=EOF
		){
		i++;
	}
	employeegs = i;
	fclose(fp);
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
	savewenjian();
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
	savewenjian();
	printf("已经删除了该员工\n\n");
}

//排序员工
void sortemployee(){
	int choice=0;
	printf("================管理员身份进入了排序系统=================\n");
	printf("=1.按照姓名排序                                         =\n");
	printf("=2.按照性别排序                                         =\n");
	printf("=3.按照工资排序                                         =\n");
	printf("=4.按照年龄排序                                         =\n");
	printf("=5.按照电话排序                                         =\n");
	printf("=========================================================\n");
	printf("=请输入您的操作\n\n");
	scanf("%d",&choice);
	int j=0,i=0;
	for(i=employeegs-1;i>0;i--){
		for(j=0;j<i;j++){
			if(
				choice==1&&strcmp(employeesz[j].name,employeesz[j+1].name)>0
				||
				choice==2&&strcmp(employeesz[j].gender,employeesz[j+1].gender)>0
				||
				choice==3&&employeesz[i].money>employeesz[j+1].money
				||
				choice==4&&employeesz[j].age>employeesz[j+1].age
				||
				choice==5&&strcmp(employeesz[j].phone,employeesz[j+1].phone)>0
				){
				struct Employee EM = employeesz[j];
				employeesz[j]=employeesz[j+1];
				employeesz[j+1]=EM;
			}
		}
	}
	printf("=排序成功，若想查看排序结果可以进入查询系统\n\n");
	savewenjian();
    
}
int main(){
	//开始就读取文件
	readwenjian();
	int flag = 0;
	//主菜单界面
	printf("=========================================================\n");
	printf("=                欢迎来到职工管理系统                   =\n");
	printf("=                   请选择账户登录                      =\n");
	printf("=                  账号输入格式如下                     =\n");
	printf("=             管理员账号：administrator                 =\n");
	printf("=   普通用户请使用自己的名字的英文大写首字母进行登录    =\n");
	printf("=                  新员工请进行注册                     =\n");
	printf("=              登录请输入1，注册请输入2                 =\n");
	printf("=========================================================\n");
	printf("=请输入您的操作方式：");
	scanf("%d",&flag);
	printf("\n");
    int loflag=0;
	int reflag=0;
	if(flag == 1){
		//登录		
		loflag = userslogin();
	}else if(flag == 2){
		//注册
	    reflag = registerusers();
	}else{
		printf("=您输入的不是1或者2，操作非法自动退出程序\n");
		return 1;
	}
	//功能菜单界面
	//与用户的交互逻辑
	//管理员权限
	if(loflag==1||reflag==1){
	while(Flag==9){
		int choice=0;
	    menu();
		scanf("%d",&choice);
		switch (choice) {
		case 1:
			addyg();
		    savewenjian();
			break;
		case 2:
			Deletempolyee();
			break;
	    case 3:
			Findemployee();

			break;
		case 4:
			sortemployee();
			break;
		case 5:
			changeemployee();
			
		
			break;
		case 6:
			printf("==已经为您最后一次保存员工数据==  :)\n");
			savewenjian();
			printf("==退出本程序！\n");
			return 1;
		
			break;
		default:
			printf("非法操作应当禁止   :(\n");
			
			break;
		}
		
	}
	//普通用户权限
	while(Flag!=9){
		int choice=0;
	    menu();
		scanf("%d",&choice);
		switch (choice) {
		case 1:
			Findemployee();
			break;
		case 2:
			changeemployee();
			break;
		case 3:
			printf("==已经为您最后一次保存员工数据:)\n");
			savewenjian();
			printf("==退出本程序！\n");
				getchar();
			return 1;
			break;
		default:
			printf("==非法操作应当禁止:(\n");
			
			break;
		}
		
	}
	}
	return 0;
	getchar();
}
