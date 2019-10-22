//Main.h                         //�ɼ�����ϵͳ 

#include<stdio.h>
#include<stdlib.h>

#define N 100 

typedef struct grade              //����Ԫ����Ϣ 
{
	char StuNo[20];               //ѧ�ţ����ַ������ 
	char Name[15];                //���������ַ������ 
	int Score;                   //�ɼ���char���� 
	int Flag;
}Grade;

typedef struct sqlist               //����˳��� 
{
	Grade * elem;
}Sqlist;

void InitialFile()         //�ļ���ʼ������
{
	FILE *pf; 
    	
	if((pf = fopen("scores.txt", "a")) == NULL)  //�򿪲������ɹ�
    {
        printf("���������ļ���ʧ�ܣ�\n");
        return;  //���������ִ��
    }
    
    fclose(pf);
	
	return;
}

void GetSqlist(int *mm, int *nn, Grade *b, Sqlist *a)     //ͨ�������ļ�����һ��˳������������Ȳ��� 
{
	FILE *pf;
    int tempc;
    int tempcc;
    char temps[20];
    char tempss[15];
    int i;
    int count=0;
	
	a->elem = b; //��ʼ��
    
    if((pf = fopen("scores.txt", "r")) == NULL)  //�򿪲������ɹ�
    {
        printf("�����ļ���ʧ�ܣ�");
        return;  //���������ִ��
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
			printf("˳�������ɣ�\n");
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

void GetInfo(char * inputStuNo, char * inputName, int * inputScore)   //��ȡ��Ϣ����������������������ʾ�û�������Ϣ���ݸ���Ϣ���������� 
{
	printf("\n");
	printf("������ѧ��ѧ�ţ�\n");
	scanf("%s", inputStuNo);
	getchar();
	printf("������ѧ��������\n");
	scanf("%s", inputName);
	printf("������ѧ���ɼ���\n");
    getchar();
	scanf("%d", inputScore);
	return;
}

void GetStuNo(char * inputStuNo)
{
	printf("\n");
	printf("������ѧ��ѧ�ţ�\n");
	scanf("%s", inputStuNo);
	return;
}

void GetName(char * inputName)
{
	printf("\n");
	printf("������ѧ��������\n");
	scanf("%s", inputName);
	return;
}

int GetMM()
{
	FILE *pf;
	int tempc;
	int count=0; 
	
	if((pf = fopen("scores.txt", "r")) == NULL)  //�򿪲������ɹ�
    {
	    printf("�����ļ���ʧ�ܣ�");
        return;  //���������ִ��
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
	
	if(*mm == *nn)  //��������������ֵΪ0����ʾ����
	{
		printf("�����������ݱ�������\n");     //��ʾ���������������� 
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
	printf("\n��Ϣ��ӳɹ���\n");
	return;
}

void QuertById(Sqlist *a, int *mm)    //��ID���Ҳ���  
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
   	printf("ѧ��                "); 
	printf("����           "); 
	printf("�ɼ�\n");
    
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
    printf("\n\n��ѯ��ɣ�\n\n");
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
	printf("\nɾ���ɹ���\n"); 
	return;
} 

void ListAll(int *mm, int *nn, Sqlist *a)
{
	SortSqlist(a, mm);
	int i;
	
	printf("\n");
	printf("ѧ��                "); 
	printf("����           "); 
	printf("�ɼ�\n");
	
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
	printf("ƽ���ɼ�Ϊ��%.2f", avg);
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
	printf("��߷�Ϊ��%d", Max);
	printf("\n");
	printf("ѧ��                "); 
	printf("����           "); 
	printf("�ɼ�\n");
	
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
    
    if((pf = fopen("scores.txt", "w")) == NULL)  //�򿪲������ɹ�
    {
        printf("�����ļ���ʧ�ܣ�");
        return;  //���������ִ��
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
    
    int a;   //ָ�����
	int size = 100; //�������� 
	int x = 0;
	int y = 100; 
	int *mm = &x;
	int *nn = &y;
	//*mm = 0; 
	//*nn = 100;
	InitialFile(size, mm, nn); //��ʼ������ 
	//*mm = GetMM();
	Grade b[100];
	Sqlist yyy;
	Sqlist *aa = &yyy;
	GetSqlist(mm, nn, b, aa);
	
	for(;;)
	{
		printf("��ӭʹ�óɼ�����ϵͳ,��ѡ���ܣ�\n");
        printf("��1:�����ɼ���Ϣ\n");
        printf("��2:��ѧ�Ų��ҳɼ���Ϣ\n");
        printf("��3:��ѧ������鿴���гɼ���Ϣ\n");
        printf("��4:�鿴�ɼ�ƽ����\n");
        printf("��5:�鿴��߷�ѧ����Ϣ\n");
        printf("��6:��ѧ��ɾ���ɼ���Ϣ\n");
        printf("��7:�鿴��ǰ���ݱ�״̬\n");
        printf("��8:���浱ǰ���ݵ��ļ�\n");
        printf("��0:�˳�����\n");
        printf("\n");
        scanf("%d",&a);
	switch(a)
    {
    	case 0:
    	{
    		WriteFile(aa, mm);
    		printf("��л����ʹ�ã�\n");
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
    		printf("��ǰ����������%d\n", *mm);
    		printf("�������������%d\n", *nn);
    		break;
	    }
	    case 8:
    	{
    		WriteFile(aa, mm);
    		printf("����ɹ���\n");
    		break;
	    }
	    default:
	    {
    		printf("�Ƿ����\n");
    		printf("\n");
    		break;
    	}
    }
	}
}
