
// MazePath.cpp : 定义控制台应用程序的入口点。
//

#define  TRUE 1
#define  FALSE   0
#define  OK  1
#define  ERROR   0
#define INFEASIBLE   -1
#define OVERFLOW   -2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
typedef  int  Status;
#define  RANGE   20		//RANGE为实际分配的空间行列数
#define M 8				//maze数组的行数 
#define N 11			// maze数组的列数 
typedef struct			//表达迷宫元素位置信息的坐标
{
	int r,c;
}PosType;

typedef struct//m，n为待处理的迷宫的行列数，RANGE为实际分配的空间行列数
{
	int m,n;
	char arr[RANGE][RANGE];
}MazeType;

typedef int directiveType;//东西南北方向用1，2，3，4整数对应

typedef struct//路径拟用栈来存储，此处定义栈元素中数据域的信息
{
	int step;//存储到达该点时经历的步数
	PosType seat;//该点位置
	directiveType di;//从该点位置走向下一位置的方向
}ElemType;

typedef struct NodeType//路径拟用链栈来存储
{
	ElemType data;
	struct NodeType *next;
}NodeType,*LinkType;

typedef struct//对链栈的头指针和元素个数进行封装
{
	LinkType top;
	int size;
}Stack;
//以上是对存储结构逐层进行定义
void   InitStack(Stack  &S)   
{   //构建空链栈，不带头结点
	S.top=NULL;   
	S.size=0;   
}   
Status   MakeNode(LinkType &p,ElemType   e)   
{   //创建一个新结点，以便插入，本函数可作为链式存储创建结点的通用函数，可用于链表、链栈、链队的插入操作
	p=(NodeType *)malloc(sizeof(NodeType));   
	if(!p)
		return   FALSE;   
	p->data=e;
	p->next=NULL;   
	return   TRUE;   
}

Status   Push(Stack   &S,ElemType   e)   
{   //入栈操作，在这里本质上是栈头（链表头）进行插入
	LinkType   p;   
	if(MakeNode(p,e))   
	{   
		p->next=S.top;   
		S.top=p;   
		S.size++;   
		return   TRUE;   
	}   
	return   FALSE;   
}

Status   StackEmpty(Stack   S)   
{   //判断是否为空栈，这里是通过top指针为NULL来判断的，本质上也可以通过size是否为0来判断
	if(S.top==NULL)
		return   TRUE; 
	return  FALSE;   
}  

Status   Pop(Stack   &S,ElemType   &e) 
{	//出栈操作，本质上是删除表头元素
	LinkType   p;
	if(StackEmpty(S)) 
		return   FALSE; 
	else
	{ 
		p=S.top;
		S.top=S.top->next; 
		e=p->data; 
		S.size--; 
		free(p);
		return   TRUE;
	} 		  
}   

Status   pass(MazeType  maze,PosType  curpos)//判断该位置是否可走 
{   //判断迷宫Maze中，当前位置curpos是否是一个可达位置
	int   m,n;   //注意这里的m，n只是表达下标的临时变量，与前面出现的m，n是不一样的
	m=curpos.r;   
	n=curpos.c;   
	if(maze.arr[m][n]==' ')
		return   TRUE;   
	return   FALSE;   
}

Status   Same(PosType  curpos,PosType  end)   
{   //判断当前位置curpos是否已达出口
	if(curpos.r==end.r && curpos.c==end.c)
		return   TRUE;   
	return   FALSE;   
}

void   FootPrint(MazeType &maze,PosType curpos)   
{   //在迷宫中标识走过的位置，避免在有路可走时还走回头路出现死循环
	int   m,n;   
	m=curpos.r;   
	n=curpos.c;   
	maze.arr[m][n]='-';   
}

PosType   NextPos(PosType curpos,int di)   
{   //通过di的值，确定下一步的位置，下一步位置实际是当前位置的四个邻居中的一个
	switch(di)
	{
	case 1:
		curpos.c++; //向东走
		break;		
	case 2:
		curpos.r++; //向南走
		break;
	case 3:
		curpos.c--; //向西走
		break;		
	case 4:
		curpos.r--;  //向北走 
		break;
	}	
	return   curpos;  	
} 

void  MarkPrint(MazeType &maze,PosType p)   
{   //对试探无路可走后回退的位置做特殊标识
	maze.arr[p.r][p.c]='@';   
}

void  PrintMaze(MazeType ma)   
{	//对迷宫输出，实际是对一个二维数组的输出
	int i,j;
	printf("\n"); 
	for(i=0;i<ma.m;i++)   
	{   
		printf("\t");
		for(j=0;j<ma.n;j++)   
		{   
			printf("%c ",ma.arr[i][j]);   
		}   
		printf("\n");   
	} 
	printf("\n"); 
} 


void   InitMaze(MazeType  &maze,int  a[][N],int row,int col)   
{   //根据二维数组来初始化迷宫，这个二维数组可以设计为由用户从键盘输入，解决不同迷宫的问题，但这里用户接口不是我们考虑的重点
	//数据结构学习时往往将输入的数据直接嵌入到程序中，以简化输入节约时间
	//二维数组名a做参数时，需要知道待读的二维数组的列数，因为C语言中二维数组是按行优先顺序存储的
	//控制每行长度的实际就是定义列的数值，所以要明确参数N
	int i,j;
	maze.m=row;
	maze.n=col;	
	for(i=0;i<row;i++)   
		for(j=0;j<col;j++)   
		{   
			if(a[i][j]==0)
				maze.arr[i][j]=' '; 
			else
				maze.arr[i][j]='#';   
		}   
} 
/*
int   MazePath(MazeType &maze,PosType start,PosType end)   
{   //求解迷宫的关键函数，maze作为引用型变量是因为要对相关路径做一些标识
//返回值为路径的长度,返回0表示无通路
Stack   s;   
int   curstep=1;   //统计路径长度实际可不用curstep，栈s中的size分量已有相关信息，修改一下程序curstep可以用于统计走过的总步数
int   found=0;   
ElemType   e;   //以栈元素的形式暂存当前位置的相关信息，以便入栈构成路径
PosType   curpos=start; //置开始位置为当前位置
InitStack(s);
do{   //栈不空且未到出口则继续循环
if(pass(maze,curpos))   //如果curpos位置可达则先入栈
{   
FootPrint(maze,curpos);   //如果可通则标记为-，当然后边如发现是死胡同，则会重新标记为另外的符号
e.step=curstep;   
e.seat=curpos;   
e.di=1;			   
Push(s,e);   
if(Same(curpos,end))
{
found=s.size;
printf("路径为（前两位为下标，后一位为方向）：\n");
while(!StackEmpty(s))//输出路径
{
Pop(s,e);
printf("%d,%d,%d\n",e.seat.r,e.seat.c,e.di);
}
}
else
{   
curpos=NextPos(curpos,1);  //到新位置时默认先向东走 
curstep++;   
}   
}   
else if(!StackEmpty(s))   
{   
Pop(s,e);   //如果curpos位置不可达，且栈不空，则把刚入栈的元素弹出做相关判断
while((e.di==4) && !StackEmpty(s))
{   
MarkPrint(maze,e.seat); //标识此路不通  
Pop(s,e);   //回到上一个位置
curstep--;   //不减一的话可以用于统计走过的总步数
}   
if(e.di<4)//如果还有方向未走过，则沿新的方向继续试探
{   
e.di++;   
Push(s,e);  //默认新方向的下一位置可达，将当前位置入栈 
curpos=NextPos(e.seat,e.di);  //通过当前位置，以及去下一位置的方向得出新的位置，再循环查看新位置是否可达 
}
}		
}while(!StackEmpty(s) && !found);   
return   found-1;   
}  

*/
int  MazePath(MazeType &maze,PosType start,PosType end) 
{//此函数为递归方法求迷宫的算法
	static int steps=1;
	if(Same(start,end))
	{
		FootPrint(maze,start);
		printf("路径为（前两位为下标，后一位为方向）：\n");
		printf("%d,%d\n",start.r,start.c);
		return steps;
	}
	else if(pass(maze,start))//判断该方块是否可以走 
	{
		FootPrint(maze,start);
		if(MazePath(maze,NextPos(start,1),end))//向右走 
		{
			printf("%d,%d,%d\n",start.r,start.c,1);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,2),end))//向下走 
		{
			printf("%d,%d,%d\n",start.r,start.c,2);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,3),end))//向左走 
		{
			printf("%d,%d,%d\n",start.r,start.c,3);
			return steps++;
		}
		else if(MazePath(maze,NextPos(start,4),end))//向上走 
		{
			printf("%d,%d,%d\n",start.r,start.c,4);
			return steps++;
		}
		else
		{
			MarkPrint(maze,start);
			return FALSE;
		}
	}
	else//不能走 
	{
		return FALSE;
	}
}

void Print(int maze[][N])
{
	int i,j;
	printf("表示迷宫的数组\n");
	for(i=0;i<M;i++)//8行 
	{
		printf("\t");
		for(j=0;j<N;j++)//11列 
		{
			printf("%d ",maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int step=0;
	int maze[M][N]={
		1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,1,1,1,0,0,1,
		1,0,0,0,0,0,1,0,0,1,1,
		1,0,1,1,1,0,0,0,1,1,1,
		1,0,0,0,1,0,1,1,0,1,1,
		1,1,0,0,1,0,1,1,0,0,1,
		1,1,1,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1};
		MazeType L;
		PosType   start,end;
		Print(maze);
		InitMaze(L,maze,M,N);
		start.r=1;//起点 
		start.c=1;
		end.r=6;//终点 
		end.c=9;
		printf("由数组转化出的迷宫");
		PrintMaze(L);
		if(step=MazePath(L,start,end))
			printf("迷宫的路径，用-表示,路径长度为:%d",step);
		else
			printf("此迷宫没有通路！");
		PrintMaze(L);
		getch();
	return 0;
}

