
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************宏定义***************************/

#define OK 1
#define MVNum 10             //最大顶点个数
#define V 10
#define MaxInt 32767         //无限大
#define MaxRoad 100
#define Extra 10             //用于增加景点

/*******************定义结构体**************************/


typedef struct {
	char name[30];          //景点名称
	char number[10];        //景点代号
	char introduce[200];    //景点介绍
}Info;

typedef struct {
	int num;			//对应景点的编号
	Info data;			//存储景点的信息
}View;

typedef struct {								//图的结构
	View	   view[MVNum+Extra];						//顶点向量数组
	int		   length[MVNum+Extra][MVNum+Extra];           //用二维数组存放每条边的权值，就是路的长度
}MGraph;


/***********************定义一些全局变量*****************/

MGraph G;							//存储信息的图

int shortest[MVNum][MVNum];			//存储两点间的最短路径

int path[MVNum][MVNum];				//存储两点间的路径

int visited[V]={0};               //初始化数组,0为未经过,1为已经经过

int stacks[120];                    //存放路径的数组

int top=1;                          //指向数组的顶端

int ends;                           //全局变量 路径终点

int ex=0;                           //用来存新的景点

/********************调用函数***************************/

void drawMap();         //画地图函数
void choose();          //跳转函数
void init_info();       //初始化信息函数
void Exit();            //结束函数
int shortdistance();    //最短路径
void floyd();           //floyd算法求最短路径
void display(int i,int j);//输出最短路径
void AllPath(MGraph G,int start);//求全部路径
void visitor();         //游客初始界面
void PathInfo();        //关于路径操作的选择
void AddView();         //增加景点
void DeleteView();      //删除景点
void UpdateView();      //更新景点
void UpdateRoad();      //更新道路
void manager();         //管理员操作界面
void FirstPage();       //初始界面
void Check();           //打印增加景点后的矩阵图

/*******************打印地图****************************/

void drawMap()
{
    int i;
        printf("                            ---------------------------*勤仁坡*---------\n");
        printf("                            --------------------------------------------\n");
        printf("                            -----------*桃李廊*-------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            --*游泳馆*------------------------*主楼*----\n");
        printf("                            --------------------------------------------\n");
        printf("                            ---------*行政楼*-------------*图书馆*------\n");
        printf("                            --------------------------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ----------------------------*操场*----------\n");
        printf("                            ---------*逸夫楼*---------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ---------*金陵广场*-------------------------\n");
        printf("                            --------------------------------------------\n");
        printf("                            ----------------------------------*体育馆*--\n");

    printf("\n\n请完成接下来的操作:  1、进入游客登陆系统      2、进入管理员登陆系统     3、退出程序\n\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1: visitor();break;
        case 2: manager();break;
        case 3: Exit();break;
    }
}

/******************跳转函数******************************/
void choose()
{
    int i;
    printf("请完成接下来的操作:  1、返回首页      2、退出程序\n");
    scanf("%d",&i);
	switch(i)
	{
	    case 1:FirstPage();break;
	    case 2:Exit();break;
	}
}

/*******************初始化信息**************************/
void init_info()
{
	int i, j;

	G.view[1].num = 1;
	strcpy(G.view[1].data.name, "情人坡");
	strcpy(G.view[1].data.number, "001");
	strcpy(G.view[1].data.introduce, "位于学校北门附近，有一块大草坪，是休息娱乐的好去处");

	G.view[2].num = 2;
	strcpy(G.view[2].data.name, "桃李廊");
	strcpy(G.view[2].data.number, "002");
	strcpy(G.view[2].data.introduce, "一条长长的被藤蔓包裹的走廊");

	G.view[3].num = 3;
	strcpy(G.view[3].data.name, "游泳馆");
	strcpy(G.view[3].data.number, "003");
	strcpy(G.view[3].data.introduce, "校园内开放的专业游泳馆");

	G.view[4].num = 4;
	strcpy(G.view[4].data.name, "行政楼");
	strcpy(G.view[4].data.number, "004");
	strcpy(G.view[4].data.introduce, "校园内老师办公的场所");

	G.view[5].num = 5;
	strcpy(G.view[5].data.name, "逸夫楼");
	strcpy(G.view[5].data.number, "005");
	strcpy(G.view[5].data.introduce, "由邵逸夫捐赠的新教学楼");

	G.view[6].num = 6;
	strcpy(G.view[6].data.name, "金陵广场");
	strcpy(G.view[6].data.number, "006");
	strcpy(G.view[6].data.introduce, "位于学校南门的一大片广场，适合游玩");

	G.view[7].num = 7;
	strcpy(G.view[7].data.name, "体育馆");
	strcpy(G.view[7].data.number, "007");
	strcpy(G.view[7].data.introduce, "校园内设施齐全的体育馆，用于进行各种体育活动");

	G.view[8].num = 8;
	strcpy(G.view[8].data.name, "操场");
	strcpy(G.view[8].data.number, "008");
	strcpy(G.view[8].data.introduce, "校园内部唯一一块正规大小的运动场，适宜进行体育运动");

	G.view[9].num = 9;
	strcpy(G.view[9].data.name, "图书馆");
	strcpy(G.view[9].data.number, "009");
	strcpy(G.view[9].data.introduce, "图书库存丰富，是学生自习的好去处");

	G.view[10].num = 10;
	strcpy(G.view[10].data.name, "主楼");
	strcpy(G.view[10].data.number, "010");
	strcpy(G.view[10].data.introduce, "校园内历史最悠久的建筑，是学校最美的风景");

	for (i = 1; i <= V; i++)
		for (j = 1; j <= V; j++)
			G.length[i][j] = 0;       //将路径长度初始化

	G.length[1][2] = G.length[2][1]=3;             //输入路径长度
	G.length[1][9] = G.length[9][1]=9;
	G.length[1][10] = G.length[10][1]=3;
	G.length[2][3] = G.length[3][2]=5;
	G.length[2][10] = G.length[10][2]=5;
	G.length[3][4] = G.length[4][3]=5;
	G.length[3][5] = G.length[5][3]=8;
	G.length[4][5] = G.length[5][4]=6;
	G.length[4][9] = G.length[9][4]=4;
	G.length[4][10] = G.length[10][4]=6;
	G.length[5][6] = G.length[6][5]=3;
	G.length[6][8] = G.length[8][6]=5;
	G.length[7][8] = G.length[8][7]=4;
	G.length[7][9] = G.length[9][7]=11;
	G.length[8][9] = G.length[9][8]=4;
	G.length[9][10] = G.length[10][9]=7;

    G.length[10][10]=G.length[1][1]=0;
    G.length[2][2]=G.length[3][3]=0;
    G.length[4][4]=0;
    G.length[5][5]=G.length[6][6]=0;
    G.length[7][7]=G.length[8][8]=0;
    G.length[9][9]=0;


}

void Exit()
{
    printf("\n              已退出程序!");
    system("pause>null");
}
/*******************************新的矩阵图************************/
void Check()
{
    int i,j;
    printf("\n");
    for(i=1;i<=MVNum+ex;i++)
        for(j=1;j<=MVNum+ex;j++)
        {
            printf("%d\t",G.length[i][j]);
            if(j==MVNum+ex)
                printf("\n");
        }
    choose();
}
/********************************最短路径*************************/

int shortdistance()
{                   //要查找的两景点的最短路径
    int i,j;
    printf("请输入要查询的两个景点的数字编号中间用空格间隔开:\n");
    scanf("%d %d",&i,&j);
    floyd();
    display(i,j);
    return 0;
    fflush(stdin);
}

void floyd()                        //floyd算法
{
    int i,j,k;
    for(i=1;i<=V;i++)
    {
		for(j=1;j<=V;j++)           //将二维数组初始化，先将两点间存在的路径设为最短路径
		{
		    if(G.length[i][j]!=0)   //若两点间存在路径，则将shorest()设置为路径
			shortest[i][j]=G.length[i][j];
			else
            shortest[i][j]=MaxInt;  //如果两点间没有路径，则将shorest()设为Maxlnt
			path[i][j]=0;           //利用path数组存放不断更新的最短路径，先初始化为0
		}
    }                               //初始化数组
    for(k=1;k<=V;k++)               //i为初始点，j为终点,k为中间过度点
		for(i=1;i<=V;i++)
			for(j=1;j<=V;j++)       //若加入的新顶点使得更短
			{
				if(shortest[i][j]>(shortest[i][k]+shortest[k][j]))
				{
					shortest[i][j]=shortest[i][k]+shortest[k][j];
					path[i][j]=k;
					path[j][i]=k;       //k为终点前最后一个点，将目前的最短路径记录下来
				}
			}
}


void display(int i,int j)           //打印两个景点的最短路径
{
    int k,temp=j;
    printf("您要查询的两景点间最短路径是： \n\n");
    fflush(stdin);
    printf("%d",j);             //打印终点
    while(path[i][j]!=0)        //如果两点间的path存在
    {                               //i…………k-j,k为终点前最后一个点
        printf("<--%d",path[i][j]); //找到k后，继续找i和k之间的最短路径
        j=path[i][j];
    }
    printf("<--%d\n\n",i);
    printf("%d-->%d的最短路径是:%d米\n",i,temp,100*shortest[i][temp]);
	printf("请选择接下来的操作:      1、返回上一界面     2、返回首页      3、退出程序\n\n");
	scanf("%d",&k);
	switch(k)
	{
	    case 1:PathInfo();break;
	    case 2:FirstPage();break;
	    case 3:Exit();break;
	}
}


/********************************所有路径******************************/


void AllPath(MGraph G,int start)   //查询所有路径
{
    int j;
    visited[start]=1;              //标记已经走过的点
    stacks[top]=start;             //入数组
    top++;
    if(start==ends)                //倘若找到终点
    {
        for(j=1;j<top-1;j++)       //将存在数组stacks中的路径点一一输出
           {
                printf("%d-->",stacks[j]);
           }
        printf("%d\n",ends);
    }
    for(j=1;j<=V;j++)              //若未找到终点，继续遍历
    {
        if(!visited[j]&&G.length[start][j]!=0)  //j点没有被访问，且两点间存在路径
            AllPath(G,j);                       //j设置为新的start，进行递归
    }
    visited[start]=0;              //j为终点，取消访问标记，数组往回退一个
    top--;                         //栈顶元素个数减一

}



/***********************************游客操作程序部分**********************/
void visitor()
{
	int i=0,j;
	printf("\n请选择需要了解的景点:\n");
	for(i=1;i<=MVNum+ex;i++)
    {
        printf("%d、%s\t\t",i,G.view[i].data.name);
        if(i==(MVNum+ex)/2)
            printf("\n");
    }
	printf("\n\n请输入编号:");
	scanf("%d",&i);
	fflush(stdin);
	printf("\n");
	for(j=1;j<=MVNum+ex;j++)
    {
        if(j==i)
        {
            printf("景点编号:%d\n", G.view[j].num);
	        printf("景点名称:%s\n",G.view[j].data.name);
	        printf("景点信息:%s\n",G.view[j].data.introduce);
        }
    }
	printf("\n\n请继续完成操作！    1、路径查找操作        2、返回首页      3、退出程序\n");
	scanf("%d",&i);
	switch(i)
	{
	    case 1: PathInfo();break;
	    case 2: FirstPage();break;
	    case 3: Exit();break;
	}
}

void PathInfo()
{
    int i,v;
	printf("\n路径查找操作:1、查找两景点间最短路径    2、遍历两景点间所有路径\n\n请输入编号:");
	scanf("%d",&i);
	fflush(stdin);
	switch(i)
	{
        case(1):
            shortdistance();
            break;
        case(2):
            printf("请输入起点:");
            scanf("%d",&v);
            printf("请输入终点:");
            scanf("%d",&ends);
            AllPath(G,v);
            break;
	}
    choose();
}

/**************************管理员操作部分************************/

void AddView()//增加景点操作
{
    int i,k,j,way;
    char name[20];
    char number[20];
    char introduce[20];
    printf("请输入要增加的景点个数:"); //增加k个景点
    scanf("%d",&k);
    ex+=k;
    for(i=1;i<=k;i++)                   //通过k次循环输入新增的景点
    {
        printf("请输入你所添加的景点的信息:\n");
        G.view[MVNum+i].num=MVNum+i;

        printf("请输入景点编号:");
        scanf("%s",number);
        strcpy(G.view[MVNum+i].data.number, number);
        printf("\n");

        printf("请输入景点名称:");
        scanf("%s",name);
        strcpy(G.view[MVNum+i].data.name, name);
        printf("\n");

        printf("请输入景点介绍:");
        scanf("%s",introduce);
        strcpy(G.view[MVNum+i].data.introduce,introduce);
        printf("\n");

        while(1)
        {
            printf("请输入新增的路径连接顶点(若连接景点为0，则输入结束):");
            scanf("%d",&j);
            if(j!=0)
            {
                printf("\n新增的路径:(%d,%d)=",MVNum+i,j);
                scanf("%d",&way);
                G.length[MVNum+i][j]=way;
                G.length[j][MVNum+i]=way;
                printf("\n");
            }
            else
                break;
        }
        printf("第%d个景点信息已补充完整！\n\n",i);
    }
    printf("请选择操作:  1、查看新的景点矩阵图     2、返回\n");
    scanf("%d",&i);
    switch (i)
    {
        case 1:Check();break;
        case 2:choose();break;
    }
}

void UpdateView()
{
    int i,n;
    char name[20];
    char k[10];
    char introduce[20];
    printf("请输入你要更新的景点编号:");
    scanf("%d",&i);
    printf("请选择你要更新的内容:1、代号     2、名称       3、介绍\n");
    scanf("%d",&n);
    switch(n)
    {
        case(1):
            {
                printf("请输入新的代号:");
                scanf("%s",k);
                strcpy(G.view[i].data.number, k);
                printf("景点信息已更新！\n");
            }
            break;
        case(2):
            {
                printf("请更新景点名称:");
                scanf("%s",name);
                strcpy(G.view[i].data.name, name);
                printf("景点信息已更新！\n");
            }
            break;
        case(3):
            {
                printf("请更新景点介绍:");
                scanf("%s",introduce);
                strcpy(G.view[i].data.introduce,introduce);
                printf("\n景点信息已更新！\n");
            }
            break;
        default:
            printf("输入编号有误!\n");
    }
	choose();
}

void UpdateRoad()
{
    int i,j,l;
    printf("请输入你要更新的路（输入两景点编号）:");
    scanf("%d %d",&i,&j);
    fflush(stdin);
    printf("请输入新的信息:");
    scanf("%d",&l);
    G.length[i][j]=l;
    printf("道路信息已更新完成!");
    choose();
}

void DeleteView()
{
    //删除景点i
    int n;
    printf("请输入要删除的景点编号:");
    scanf("%d",&n);
    strcpy(G.view[n].data.name,"已删除");
    strcpy(G.view[n].data.number,"已删除");
    strcpy(G.view[n].data.introduce,"已删除");
    printf("\n该景点信息已删除!\n");
    choose();
}

void manager()//增加、删除、更新景点及道路信息
{
    int i;
    printf("\n欢迎进入管理员操作系统，请选择您要完成的内容:\n\n1、增加景点     2、删除景点      3、更新景点信息        4、更新道路信息\n\n");
    printf("\n请输入编号:");
    scanf("%d",&i);
    switch(i)
    {
        case 1:AddView();break;
        case 2:DeleteView();break;
        case 3:UpdateView();break;
        case 4:UpdateRoad();break;
    }
}



/*******************进入程序第一界面********************/



void FirstPage()
{
	int i;
	printf("                            |********************************************|\n");
	printf("                            |*         欢迎来到南农校园导游系统         *|\n");
	printf("                            |*            1、进入游客登陆系统           *|\n");
	printf("                            |*            2、进入管理人员系统           *|\n");
	printf("                            |*            3、打印地图                   *|\n");
	printf("                            |*            4、退出系统                   *|\n");
	printf("                            |********************************************|\n");
	printf("\n                                   请输入您要选择的操作:");
	scanf("%d", &i);
	switch (i)
	{
	case 1: visitor(); break;
	case 2: manager(); break;
	case 3: drawMap();break;
	case 4: Exit();
	}
	system("pause>null");
}

/******************************主函数**************************/
int main()
{
    init_info();
    FirstPage();
	return 0;
}

