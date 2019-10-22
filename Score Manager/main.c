//Main.h                         //成绩管理系统 

#include<stdio.h>
#include<stdlib.h>

#define N 100 

typedef struct grade              //定义元组信息 
{
	char StuNo[20];               //学号，由字符串组成 
	char Name[15];                //姓名，由字符串组成 
	int Score;                   //成绩，char类型 
	int Flag;
}Grade;

typedef struct sqlist               //定义顺序表 
{
	Grade * elem;
}Sqlist;

void InitialFile()         //文件初始化方法
{
	FILE *pf; 
    	
	if((pf = fopen("scores.txt", "a")) == NULL)  //打开操作不成功
    {
        printf("错误：数据文件打开失败！\n");
        return;  //结束程序的执行
    }
    
    fclose(pf);
	
	return;
}

void GetSqlist(int *mm, int *nn, Grade *b, Sqlist *a)     //通过现有文件创建一个顺序表方便排序计算等操作 
{
	FILE *pf;
    int tempc;
    int tempcc;
    char temps[20];
    char tempss[15];
    int i;
    int count=0;
	
	a->elem = b; //初始化
    
    if((pf = fopen("scores.txt", "r")) == NULL)  //打开操作不成功
    {
        printf("错误：文件打开失败！");
        return;  //结束程序的执行
    }
    
    for(i=0;i<*nn;i++)
    {
    	(a->elem+i)->Flag = 0;
    }
    
    for(i=0;i<*nn;i++)
    {
    	tempc = fgetc(pf);
    	if(tempc == EOF)
		{
			printf("顺序表创建完成！\n");
			break;
		} 
    	if(tempc == '#')
    	{
    		tempc = fgetc(pf);
    		if(tempc != '#')
    		{
    			count++;
    			fseek(pf, -1, SEEK_CUR);
    		    fgets(temps, 20, pf);
    		    if(1)
    		    {
    		    	strcpy( (a->elem+i)->StuNo, temps); 
    		    	fseek(pf, 3, SEEK_CUR);
    		    	fgets(tempss, 15, pf);
    		    	strcpy( (a->elem+i)->Name, tempss); 
    		    	fseek(pf, 4, SEEK_CUR);
    		    	fscanf(pf, "%d   ", &tempcc); //
	    		    (a->elem+i)->Score = tempcc;
	    		    (a->elem+i)->Flag = 1;
    		    }
		    }
	    }
    }
    *mm = count;
    return;
}

void SortSqlist(Sqlist *a, int *mm) //BUG
{
	int i,j;
	int tempc;
	char temps[20];
	char tempss[15];
	for(i=0;i<20;i++)
	{
		temps[i]=' ';
	}
	for(i=0;i<15;i++)
	{
		tempss[i]=' ';
	}
	for(i=0;i<*mm;i++)
	{
		for(j=0;j<*mm-1;j++)
		{
			if(strcmp((a->elem+j)->StuNo,(a->elem+j+1)->StuNo)>0)
			{
				strcpy(temps, (a->elem+j)->StuNo);
				strcpy((a->elem+j)->StuNo, (a->elem+j+1)->StuNo);
				strcpy((a->elem+j+1)->StuNo, temps);
				
				strcpy(tempss, (a->elem+j)->Name);
				strcpy((a->elem+j)->Name, (a->elem+j+1)->Name);
				strcpy((a->elem+j+1)->Name, tempss);
				
				tempc = (a->elem+j)->Score;
				(a->elem+j)->Score = (a->elem+j+1)->Score;
				(a->elem+j+1)->Score = tempc;
			}
		}
	}
}

void GetInfo(char * inputStuNo, char * inputName, int * inputScore)   //获取信息操作，用于在主函数中提示用户输入信息传递该信息到主函数中 
{
	printf("\n");
	printf("请输入学生学号：\n");
	scanf("%s", inputStuNo);
	getchar();
	printf("请输入学生姓名：\n");
	scanf("%s", inputName);
	printf("请输入学生成绩：\n");
    getchar();
	scanf("%d", inputScore);
	return;
}

void GetStuNo(char * inputStuNo)
{
	printf("\n");
	printf("请输入学生学号：\n");
	scanf("%s", inputStuNo);
	return;
}

void GetName(char * inputName)
{
	printf("\n");
	printf("请输入学生姓名：\n");
	scanf("%s", inputName);
	return;
}

int GetMM()
{
	FILE *pf;
	int tempc;
	int count=0; 
	
	if((pf = fopen("scores.txt", "r")) == NULL)  //打开操作不成功
    {
	    printf("错误：文件打开失败！");
        return;  //结束程序的执行
    }
    
    for(;;)
    {
    	scanf("%c", &tempc);
    	
    	if(tempc == EOF)
		{
			fclose(pf);
			return count;
		} 
    	if(tempc == '\n')
    	{
    		count++;
	    }
    }
}

void AddStu(Sqlist *a, int *mm, int *nn) 
{
	char newStuNo[20];
	char newName[15];
	int *newScore; 
	int i;
	
	if(*mm == *nn)  //超出容量，返回值为0，表示出错
	{
		printf("出错：超出数据表容量！\n");     //提示：超出容量，出错 
		return;   
	}
	
	GetInfo(newStuNo, newName, newScore);
	for(i=0;i<*nn;i++)
	{
		if((a->elem+i)->Flag==0)
		{
			strcpy((a->elem+i)->StuNo, newStuNo);
	        strcpy((a->elem+i)->Name, newName);
	        (a->elem+i)->Score = *newScore;
            (a->elem+i)->Flag = 1;
            *mm = *mm + 1;
            break;
		}
	}
	printf("\n信息添加成功！\n");
	return;
}

void QuertById(Sqlist *a, int *mm)    //按ID查找操作  
{
    char inputStuNo[20];
    int i;
    for(i=0;i<20;i++)
	{
		inputStuNo[i]=' ';
	} 

    
    GetStuNo(inputStuNo);
    for(i=0;i<20;i++)
	{
		if(inputStuNo[i]=='\0')
		{
			inputStuNo[i]=' ';
		}
	} 
   	inputStuNo[i-1]='\0';
   	
   	printf("\n");
   	printf("学号                "); 
	printf("姓名           "); 
	printf("成绩\n");
    
    for(i=0;i<*mm;i++)
    {
        if((strcmp(inputStuNo, (a->elem+i)->StuNo)==0)&&((a->elem+i)->Flag==1))
        {
        	printf("%-20s", (a->elem+i)->StuNo);
		    printf("%-15s", (a->elem+i)->Name);
		    printf("%-5d", (a->elem+i)->Score);
		    printf("\n");
        }
    }
    printf("\n\n查询完成！\n\n");
}

void DelById(Sqlist *a, int *mm)
{
	char inputStuNo[20];
	int i;
	for(i=0;i<20;i++)
	{
		inputStuNo[i]='\0';
	}
	GetStuNo(inputStuNo);  //BUG
	for(i=0;i<20;i++)
	{
		if(inputStuNo[i]=='\0')
		{
			inputStuNo[i]=' ';
		}
	} 
   	inputStuNo[i-1]='\0';
	for(i=0;i<*mm;i++)
	{
		if(strcmp(inputStuNo, (a->elem+i)->StuNo)==0) 
		{
			(a->elem+i)->Flag = 0;
		}
	}
	*mm = *mm - 1;
	printf("\n删除成功！\n"); 
	return;
} 

void ListAll(int *mm, int *nn, Sqlist *a)
{
	SortSqlist(a, mm);
	int i;
	
	printf("\n");
	printf("学号                "); 
	printf("姓名           "); 
	printf("成绩\n");
	
	for(i=0;i<*nn;i++)
	{
		if((a->elem+i)->Flag == 1) 
		{
			printf("%-20s", (a->elem+i)->StuNo);
		    printf("%-15s", (a->elem+i)->Name);
		    printf("%-5d", (a->elem+i)->Score);
		    printf("\n");
		}
	}
    printf("\n");
	return; 
}

void AvgScore(int *mm, int*nn, Sqlist *a)
{
	int i;
	int s=0;
	float avg;
	
	for(i=0;i<*mm;i++)
	{
		s += (a->elem+i)->Score;
	}
	
	avg = (float)s/(*mm);
	printf("平均成绩为：%.2f", avg);
	printf("\n");
	
	return; 
}

void MaxScore(int *mm, int*nn, Sqlist *a)
{
	Grade temp;
	int i;
	int Max=-100;
	
	for(i=0;i<*mm;i++)
	{
		if(Max < (a->elem+i)->Score)
		{
			Max = (a->elem+i)->Score;
		} 
	}
	printf("\n");
	printf("最高分为：%d", Max);
	printf("\n");
	printf("学号                "); 
	printf("姓名           "); 
	printf("成绩\n");
	
	for(i=0;i<*mm;i++)
	{
		if((a->elem+i)->Score == Max)
		{
			printf("%s", (a->elem+i)->StuNo);
		    printf("%s", (a->elem+i)->Name);
		    printf("%d", (a->elem+i)->Score);
		    printf("\n");
		}
	}

	return; 	
}

void WriteFile(Sqlist *a, int *mm)  
{        
    int i;
    FILE *pf;
    
    if((pf = fopen("scores.txt", "w")) == NULL)  //打开操作不成功
    {
        printf("错误：文件打开失败！");
        return;  //结束程序的执行
    }
    
    for(i=0;i<*mm;i++)
    {
    	if((a->elem+i)->Flag == 1)
    	{
    		fprintf(pf, "#%-20s##%-15s###%-5d\n", (a->elem+i)->StuNo, (a->elem+i)->Name, (a->elem+i)->Score);
	    }
    }
	
	fclose(pf);
	
	return;
}

int main()
{
	
	void InitialFile();
    void GetSqlist(int *mm, int *nn, Grade *b, Sqlist *a);
    void SortSqlist(Sqlist *a, int *mm);
    void GetInfo(char * inputStuNo, char * inputName, char inputScore);
    void GetStuNo(char * inputStuNo);
    void GetName(char * inputName);
    void AddStu(Sqlist *a, int *mm, int *nn);
    void QuertById(Sqlist *a, int *mm);
    void ListAll(int *mm, int *nn, Sqlist *a);
    void AvgScore(int *mm, int*nn, Sqlist *a);
    void MaxScore(int *mm, int*nn, Sqlist *a);
    int GetMM();
    void DelById(Sqlist *a, int *mm);
    
    int a;   //指令变量
	int size = 100; //定义容量 
	int x = 0;
	int y = 100; 
	int *mm = &x;
	int *nn = &y;
	//*mm = 0; 
	//*nn = 100;
	InitialFile(size, mm, nn); //初始化操作 
	//*mm = GetMM();
	Grade b[100];
	Sqlist yyy;
	Sqlist *aa = &yyy;
	GetSqlist(mm, nn, b, aa);
	
	for(;;)
	{
		printf("欢迎使用成绩管理系统,请选择功能：\n");
        printf("按1:创建成绩信息\n");
        printf("按2:按学号查找成绩信息\n");
        printf("按3:按学号排序查看所有成绩信息\n");
        printf("按4:查看成绩平均分\n");
        printf("按5:查看最高分学生信息\n");
        printf("按6:按学号删除成绩信息\n");
        printf("按7:查看当前数据表状态\n");
        printf("按8:保存当前数据到文件\n");
        printf("按0:退出程序\n");
        printf("\n");
        scanf("%d",&a);
	switch(a)
    {
    	case 0:
    	{
    		WriteFile(aa, mm);
    		printf("感谢您的使用！\n");
   	    	return 0;
	    }
	    case 1:
    	{
    		AddStu(aa, mm, nn);  
    		getchar();
    		WriteFile(aa, mm);
    		break;
	    }
	    case 2:
    	{
    		QuertById(aa, mm);
    		break;
	    }
	    case 3:
    	{
    		ListAll(mm, nn, aa);
    		WriteFile(aa, mm);
    		break;
	    }
	    case 4:
    	{
    		AvgScore(mm, nn, aa);
    		break;
	    }
	    case 5:
    	{
    		MaxScore(mm, nn, aa);
    		break;
	    }
	    case 6:
    	{
    		DelById(aa, mm);
    		WriteFile(aa, mm);
    		break;
	    }
	    case 7:
    	{
    		printf("当前数据容量：%d\n", *mm);
    		printf("最大数据容量：%d\n", *nn);
    		break;
	    }
	    case 8:
    	{
    		WriteFile(aa, mm);
    		printf("保存成功！\n");
    		break;
	    }
	    default:
	    {
    		printf("非法命令！\n");
    		printf("\n");
    		break;
    	}
    }
	}
}
