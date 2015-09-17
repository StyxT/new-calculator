#include "stdio.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "string.h"
#define bool int
#define false 0
#define true 1

using namespace std;

ofstream fout("ans.txt");                                            //c++文件输出 保存计算结果


void choose();                                                           //总选择菜单
void matrix_choose();                                               //矩阵运算选择菜单


struct num                                                               //用于除法计算
{
   int val;
   struct num *next;
};

struct num* createlist(string str)
{
	int length=str.size();
	struct num *head=new num();
	struct num *prev=head,*e=new num();

	for(int i=0;i<length;i++)
	{
		struct num *p=new num();
		p->val=str[i]-48;                          //char to int
		prev->next=p;
		prev=p;
	}
	prev->next=e;
	e->val=-1;                                        //e节点作为哨兵 帮助结束运算
	e->next=NULL;
	return head;
}


int max(int a,int b)                                                  //返回二者最大的一个
{
    if(a>b)
        return a;
    else
        return b;
}

void add()                                                                //整数加法
{
    system("title plus");
    system("cls");
    int numA[1000],sizeA,iA=1;
    int numB[1000],sizeB,iB=1;
    int ans[1000],sizeofAns;
    char numa[1000];
    char numb[1000];
    int i;

    memset(numA,0,sizeof(numA));
    memset(numB,0,sizeof(numB));
     memset(ans,0,sizeof(ans));
    printf("Please enter the first number:\n");
    gets(numa);
    sizeA=(int)(strlen(numa));
    printf("Please enter the second number:\n");
    gets(numb);
    sizeB=(int)(strlen(numb));
    //数据输入部分完成
    while(iA<=sizeA)
    {
        numA[iA]=(numa[sizeA-iA]-'0');
        iA++;
    }

    while(iB<=sizeB)
    {
        numB[iB]=(numb[sizeB-iB]-'0');
        iB++;
    }
    //数据由char类型数组转换为int型数组

    sizeofAns=max(sizeA,sizeB)+1;

    //2数相加，结果的长度是2者最长的长度或再加1
    for(i=1;i<=sizeofAns;i++)
    {
        int temp=0;
        ans[i]+=numA[i]+numB[i];        //数位相加
        temp=ans[i]/10;
        ans[i+1]+=temp;                       //进位
        ans[i]%=10;
    }
    if(ans[sizeofAns]==0)
        sizeofAns--;                                  //去除前导0
    printf("The result is:\n");
    for(i=sizeofAns;i>=1;i--)                 //输出结果
        printf("%d",ans[i]);
    printf("\n");

     fout<<numa<<"+"<<numb<<"=";
     for(i=sizeofAns;i>=1;i--)
        fout<<ans[i];                                  //结果保存到文件
     fout<<endl;
     fout<<endl;

l1:  printf("\n");
     printf("Do you want to continue?(Y/N)");
     char c;
     scanf("%c",&c);getchar();
     switch(c)
     {
            case 'n':
            case 'N':choose();break;
            case  'y':
            case  'Y':add();break;
            default: goto l1;
     }
}

void minus_num()                                                   //整数减法
{
    system("title minus");
    system("cls");
    int numA[1000],sizeA,iA=1;
    int numB[1000],sizeB,iB=1;
    int ans[1000],sizeofAns;
    char numa[1000];
    char numb[1000];
    int i,negative=0;//negative为符号标记

    memset(numA,0,sizeof(numA));
    memset(numB,0,sizeof(numB));
    memset(ans,0,sizeof(ans));
    printf("Please enter the minuend:\n");
    gets(numa);
    sizeA=(int)(strlen(numa));
    printf("Please enter the subtrahend:\n");
    gets(numb);
    sizeB=(int)(strlen(numb));
    //数据输入完成
    if(sizeA<sizeB || (numa[1]<numb[1] && sizeA<=sizeB))   //被减数永远为长度最长的数
    {
        while(iA<=sizeB)
        {
            numA[iA]=(numb[sizeB-iA]-'0');     //numA存放被减数  numB存放减数
            iA++;
        }

        while(iB<=sizeA)
        {
            numB[iB]=(numa[sizeA-iB]-'0');
            iB++;
        }
        negative=1;
    }
    else
    {
        while(iA<=sizeA)
        {
            numA[iA]=(numa[sizeA-iA]-'0');
            iA++;
        }

        while(iB<=sizeB)
        {
            numB[iB]=(numb[sizeB-iB]-'0');
            iB++;
        }
    }
    //数据处理完成，已经转变为int型
    sizeofAns=max(sizeA,sizeB);
    for(i=0;i<=sizeofAns;i++)
    {
        if(numA[i]<numB[i])             //减法操作 不够的借位
        {
            numA[i]+=10;
            numA[i+1]--;
        }
        ans[i]=numA[i]-numB[i];
    }

    fout<<numa<<"-"<<numb<<"=";

    while(ans[sizeofAns]==0)
        sizeofAns--;                                      //去除前导0
    printf("The result is:\n");
    if(negative==1)                                    //是否为负数
    {
        printf("-");
        fout<<'-';
    }
    for(i=sizeofAns;i>=1;i--)
    {
        printf("%d",ans[i]);
        fout<<ans[i];
    }
    printf("\n");
    fout<<endl;
l1:  printf("\n");
     printf("Do you want to continue?(Y/N)");
     char c;
     scanf("%c",&c);getchar();
     switch(c)
     {
            case 'n':
            case 'N':choose();break;
            case  'y':
            case  'Y':minus_num();break;
            default: goto l1;
     }
}

void mutilplication()                                                //整数乘法
{
    system("title multiplication");
    system("cls");
    int numA[1000],sizeA,iA=0;
    int numB[1000],sizeB,iB=0;
    int ans[1000],sizeofAns;
    char numa[1000];
    char numb[1000];
    int i,j;

    memset(numA,0,sizeof(numA));
    memset(numB,0,sizeof(numB));
    memset(ans,0,sizeof(ans));
    printf("Please enter the first number:\n");
    gets(numa);
    fout<<numa<<"*";
    sizeA=(int)(strlen(numa));
    printf("Please enter the second number:\n");
    gets(numb);
    fout<<numb<<"=";
    sizeB=(int)(strlen(numb));
    //数据输入完成
    while(iA<sizeA)
    {
        numA[iA]=(numa[iA]-'0');
        iA++;
    }

    while(iB<sizeB)
    {
        numB[iB]=(numb[iB]-'0');
        iB++;
    }
    //数据转化为int型
    sizeofAns=sizeA+sizeB-1;    //结果的位数
    for(i=0;i<sizeA;i++)
        for(j=0;j<sizeB;j++)
            ans[i+j]+=numA[i]*numB[j];   //模拟手算
    for(i=sizeofAns;i>=1;i--)
      if(ans[i]>=10)
      {
          ans[i-1]+=ans[i]/10;                     //进位
          ans[i]%=10;
      }
    if(ans[0]!=0)
        i=0;
    else
        i=1;                                                //判断结果的长度
    printf("The result is:\n");
    for(i;i<sizeofAns;i++)
    {
        printf("%d",ans[i]);
        fout<<ans[i];
    }
    printf("\n");
    fout<<endl;
 l1:    printf("Do you want to continue?(Y/N)");
     char c;
     scanf("%c",&c);getchar();
     switch(c)
     {
            case 'n':
            case 'N':choose();break;
            case  'y':
            case  'Y':mutilplication();break;
            default: goto l1;
     }
}

void divide()                                                             //整数除法
{
    system("title Divide");
    system("cls");
	struct num *h,*he,*p,*r,*e;
	int n,i=0,d;
	string str;

	cout<<"Please enter the  dividend:\n";
	cin>>str;
	fout<<str<<"/";
	cout<<"Please enter the divisor:\n";
	cin>>d;
	fout<<d<<"=";
	//输入数据完成
	h=createlist(str);
    he=new num();
    r=he;
    e=new num();
    //将被除数加入链表
    for(;h->val!=-1;h=h->next,i*=10)
    {
        p=new num();
    	p->val=(h->val+i)/d;                        //模拟手算
    	i=(h->val+i)%d;
    	r->next=p;
    	r=p;
    //	cout<<p->val;
    }
    r->next=e;
    e->val=-1;                                         //设置结束哨兵
    while(he->val==0)
     he=he->next;
     cout<<"The result is:\n";
    while(he->val!=-1)
    {
      cout<<he->val;
      fout<<he->val;
      he=he->next;
    }
    printf("\n");
    fout<<endl;
 l1:   printf("Do you want to continue?(Y/N)");
     char c;
     cin>>c;getchar();
     switch(c)
     {
            case 'n':
            case 'N':choose();break;
            case  'y':
            case  'Y':divide();break;
            default :goto l1;
     }
}

void matrix_transfer()                                              //矩阵转置
{
    system("title matrix transfer");
    system("cls");
    int m,n,a[100][100],b[100][100];
    cout<<"Please enter the dimension of the matrix:\n";
    cin>>m>>n;
    cout<<"Please enter the matrix:\n";
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
            fout<<a[i][j]<<" ";
            b[j][i]=a[i][j];                        //输入时进行转置
        }
        fout<<endl;
    }

    cout<<"The result is:\n";

    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=m;j++)
      {
         printf("%2d ",b[i][j]);
         fout<<b[i][j]<<" ";
      }
       cout<<endl;
       fout<<endl;
    }
    fout<<endl<<endl<<endl;
    l1:  printf("\n");
    printf("Do you want to continue?(Y/N)");
     char c;
     cin>>c;getchar();
     switch(c)
     {
            case 'n':
            case 'N':matrix_choose();break;
            case  'y':
            case  'Y':matrix_transfer();break;
            default:goto l1;
     }
}


void matrix_muti()        //矩阵乘法
{
        system("title matrix multiplication");
        system("cls");
        int a[100][100],b[100][100];
        int ans[100][100];
        int m,n1,n2,p,i,j,k;

        printf("Please enter the dimension of the first matrix:\n");
        scanf("%d %d",&m,&n1);
        printf("Please enter the first matrix:\n");

        for(i=1;i<=m;i++)
        {
            for(j=1;j<=n1;j++)
            {
                scanf("%d",&a[i][j]);
                fout<<a[i][j]<<" ";
            }
            fout<<endl;
        }

        printf("Please enter the dimension of the second matrix:\n");
        scanf("%d %d",&n2,&p);
        printf("Please enter the second matrix:\n");

        for(i=1;i<=n2;i++)
        {
            for(j=1;j<=p;j++)
            {
                scanf("%d",&b[i][j]);
                fout<<b[i][j]<<" ";
            }
            fout<<endl;
        }

        if(n1!=n2)     //输入数据错误
            printf("WRONG DIMENSION! Quit....\n");
        else
        {
            for(i=1;i<=m;i++)
                for(j=1;j<=p;j++)
                    for(k=1;k<=n1;k++)
                        ans[i][j]+=a[i][k]*b[k][j];     //矩阵乘法的定义
            printf("The result is:\n");
            for(i=1;i<=m;i++)
            {
                for(j=1;j<=p;j++)
                {
                    printf("%4d ",ans[i][j]);
                    fout<<ans[i][j]<<" ";
                }
                printf("\n");
                fout<<endl;
            }
        }
    fout<<endl<<endl<<endl;
      printf("\n");
 l1:    printf("Do you want to continue?(Y/N)");
     char c;
     cin>>c;getchar();
     switch(c)
     {
            case 'n':
            case 'N':matrix_choose();break;
            case  'y':
            case  'Y':matrix_muti();break;
            default: goto l1;
     }

}

void matrix_add()          //矩阵加法
{
    system("title matrix plus");
    system("cls");
    int n,m,i,j;
    int a[100][100],b[100][100];
    printf("Please enter the dimension of the  matrix:\n");
    scanf("%d %d",&n,&m);
    printf("Please enter the first matrix:\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            fout<<a[i][j]<<" ";
        }
        fout<<endl;
    }

    printf("Please enter the second matrix:\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            scanf("%d",&b[i][j]);
            fout<<b[i][j]<<" ";
        }
        fout<<endl;
    }
    printf("The result is:\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
           printf("%3d ",a[i][j]+b[i][j]);
           fout<<a[i][j]+b[i][j]<<" ";
        }
        printf("\n");
        fout<<endl;
    }

    fout<<endl<<endl<<endl;

    printf("\n");
    printf("Do you want to continue?(Y/N)");
     char c;
     cin>>c;getchar();
     switch(c)
     {
            case 'n':
            case 'N':matrix_choose();break;
            case  'y':
            case  'Y':matrix_add();break;
            default : goto l1;
     }
}

void matrix_minus()         //矩阵减法
{
    system("title matrix minus");
    system("cls");
    int n,m,i,j;
    int a[100][100],b[100][100];
    printf("Please enter the dimension of the matrix:");
    scanf("%d %d",&n,&m);
    printf("Please enter the first matrix:\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            fout<<a[i][j]<<" ";
        }
        fout<<endl;
    }
    printf("Please enter the second matrix:\n");
     for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            scanf("%d",&b[i][j]);
            fout<<b[i][j]<<" ";
        }
        fout<<endl;
    }
    printf("The result is:\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            fout<<a[i][j]-b[i][j]<<" ";
            printf("%3d ",a[i][j]-b[i][j]);
        }
        printf("\n");
        fout<<endl;
    }
    fout<<endl<<endl<<endl;
    printf("\n");
     printf("Do you want to continue?(Y/N)");
     char c;
    cin>>c;getchar();
     switch(c)
     {
            case 'n':
            case 'N':matrix_choose();break;
            case  'y':
            case  'Y':matrix_minus();break;
     }
}


void opera()                       //四则混合运算
{
    system("title operation");
    system("cls");
    char a[100];
    int s1[100],*sp1,i;        //s1是数字栈，sp1是栈顶指针
    char s2[100],*sp2;        //s2是符号栈，sp2是栈顶指针
    int boo[100]={0};
    boo['*']=1;                    //*,/的运算优先级高于+，-
    boo['/']=1;
    sp1=s1;
    sp2=s2;

    printf("Please enter the operation:\n");
    gets(a);
    fout<<a<<"=";
    for(i=0;i<strlen(a);i++)
    {
        if(a[i]>='0' && a[i]<='9')
        {
            int ans=0,k=1;
            while(a[i]>='0' && a[i]<='9')
            {
                ans=ans*k+(a[i]-'0');
                i++;
                k*=10;
            }
            *sp1=ans;
            sp1++;
            i--;

        }
        else
        {

            if(i==1)
            {
                *sp2=a[i];
                sp2++;
            }
            else
            {
                if(boo[*(sp2-1)]>=boo[a[i]])
                {
                    int aa=*(--sp1);
                    int bb=(*(--sp1));
                    switch(*(--sp2))
                    {
                        case '+':aa=aa+bb;break;
                        case '-':aa=-aa+bb;break;
                        case '*':aa=aa*bb;break;
                        case '/':aa=bb/aa;break;
                    }
                    *sp1=aa;
                    sp1++;
                    *sp2=a[i];
                    sp2++;
                }
                else
                {
                    *sp2=a[i];
                    sp2++;
                }
            }


        }
    }

    while(sp2>=s2+1)
    {
        int aa=*(--sp1);
        int bb=(*(--sp1));
        switch(*(--sp2))
        {
            case '+':aa=aa+bb;break;
            case '-':aa=-aa+bb;break;
            case '*':aa=aa*bb;break;
            case '/':aa=bb/aa;break;
        }
        *sp1=aa;
        sp1++;
    }
    int ans=*(--sp1);
    printf("The result is:");
    printf("%d\n",ans);
    fout<<ans<<endl;
     printf("\n");
     printf("Do you want to continue?(Y/N)");
     char c;
     scanf("%c",&c);getchar();
     switch(c)
     {
            case 'n':
            case 'N':choose();break;
            case  'y':
            case  'Y':opera();break;
     }
}

void UI()                               //主界面
{
    system("mode 82,14");
    int i,j;
    for(i=1;i<=79;i++)
        printf("*");
    printf("\n");
    for(i=1;i<=3;i++)
    {
        printf("*");
        for(j=1;j<78;j++)
            printf(" ");
        printf("*");
        printf("\n");
    }
    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("welcome to our calculator!");
    for(i=1;i<28;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("1.plus             2.minus");
    for(i=1;i<28;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("3.multiplication   4.divide");
    for(i=1;i<27;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("5.algorithm about matrix.  ");
    for(i=1;i<27;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("6.Simple four operations.  ");
    for(i=1;i<27;i++)
        printf(" ");
    printf("*");
    printf("\n");

     printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("7.Quit                     ");
    for(i=1;i<27;i++)
        printf(" ");
    printf("*");
    printf("\n");

    for(i=1;i<27;i++)
        printf(" ");
    printf("Please make a choice:");
}

void matrix_UI()                    //矩阵计算界面
{
    system("cls");
    system("title matrix");
    int i,j;
    for(i=1;i<=81;i++)
        printf("*");
    printf("\n");
    for(i=1;i<=3;i++)
    {
        printf("*");
        for(j=1;j<80;j++)
            printf(" ");
        printf("*");
        printf("\n");
    }
    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("welcome to our matrix calculator!");
    for(i=1;i<23;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("1.   plus              2.minus");
    for(i=1;i<26;i++)
        printf(" ");
    printf("*");
    printf("\n");

    printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("3.multiplication       4.transfer");
    for(i=1;i<23;i++)
        printf(" ");
    printf("*");
    printf("\n");

     printf("*");
    for(i=1;i<25;i++)
        printf(" ");
    printf("5.cancel                     ");
     for(i=1;i<27;i++)
        printf(" ");
    printf("*");
    printf("\n");

    for(i=1;i<30;i++)
        printf(" ");
    printf("Please make a choice:");

}

void matrix_choose()               //矩阵功能的选择
{
    matrix_UI();
      int n;
    scanf("%d",&n);
    getchar();
    system("cls");
    switch(n)
    {
        case 1:matrix_add(); break;
        case 2:matrix_minus();break;
        case 3:matrix_muti();break;
        case 4:matrix_transfer();break;
        case 5:choose();break;
    }
}

void choose()                             //总选择界面
{
    UI();
    system("title calculator");
    int n;
    scanf("%d",&n);
    getchar();
    system("cls");
    switch(n)
    {
        case 1:add(); break;
        case 2:minus_num();break;
        case 3:mutilplication();break;
        case 4:divide();break;
        case 5:system("title matrix calculator"); matrix_choose(); break;
        case 6:opera();
        case 7:exit(1);
    }
}



int main()
{
    system("title calculator");
    choose();                                  //程序接口
    fout.close();                             //关闭文件
    return 0;
}
