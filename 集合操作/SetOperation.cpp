// 数据结构1.cpp : 定义控制台应用程序的入口点。
//


#define  TRUE 1
#define  FALSE   0
#define  OK  1
#define  ERROR   0
#define INFEASIBLE   -1
#define OVERFLOW   -2
typedef  int  Status;
typedef  char  ElemType;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef  struct NodeType
{
	ElemType   data;
	struct NodeType  *next;
} NodeType,*LinkType;

typedef struct
{
	LinkType head,tail;//指向链表的头和尾
	int size;
}OrderedList;

ElemType a[100]="magazine";//set1初始值
ElemType b[100]="paper";
OrderedList L1,L2,L3;

Status MakeNode(LinkType &p,ElemType e)//加长链表 
{
	p=(LinkType)malloc(sizeof(NodeType));
	if(!p)
		return FALSE;
	p->data=e;
	p->next=NULL;
	return TRUE;
}

Status InitList(OrderedList &L)//初始化链表 ，头结点定义为空 
{
	if(MakeNode(L.head,' '))
	{
		L.tail=L.head;
		L.size=0;
		return TRUE;
	}
	else
	{
		L.head=NULL;
		return FALSE;
	}
}
Status LocateElem(OrderedList L,  ElemType e,  LinkType &p)//查找元素e在表L1中的位置
{
	NodeType *pre;
	if(L.head)
	{
		pre=L.head;
		p=pre->next;
		while(p && p->data<e)
		{
			pre=p;
			p=p->next;
		}
		if(p && p->data==e)//查找成功
		{
			return TRUE;
		}
		else
		{
			p=pre;
			return FALSE;
		}
	}
	else
		return FALSE;
}

void InsertAfter(OrderedList L,  LinkType q,  LinkType s)//在链表尾添加新结点
{
	if(L.head && q && s)
	{
		s->next=q->next;
		q->next=s;
		if(L.tail==q)
			L.tail=s;
		L.size++;
	}
}

void CreateSet(OrderedList &T, char *s)//输入字符串，并去除重复字符和非a~z字符 
{
	unsigned i;
	LinkType p ,q;
	if(InitList(T))
	{
		for(i=0;i<=strlen(s);i++)
		{
			if(s[i]>='a' &&s[i]<='z' &&  !LocateElem(T,s[i],p))
			{
				if(MakeNode(q,s[i]))
				{
					InsertAfter(T,p,q);
				}
			}
		}
	}
}
Status Print(LinkType p)
{
	if(p)
	{
		printf("%c",p->data);
		return TRUE;
	}
	else
		return FALSE;
}

void ListTraverse(LinkType p, Status (*visit)( LinkType ))
{
	printf("%c",'\t');
	while(p)
	{
		visit(p);
		p=p->next;
	}
	printf("%c",'\n');
	
}

void Append(OrderedList &L,LinkType s)//L=L3，制作L3
{
	if(L.head && s)//在L3的表尾添加元素
	{
		if(L.tail!=L.head)
			L.tail->next=s;
		else
			L.head->next=s;
		L.tail=s;
		L.size++;
	}
}


void Union(OrderedList &T,OrderedList S1,OrderedList S2)//T=L3,S1=L1,S2=L2，求L1与L2的合集并存入L3链表
{
	LinkType p1,p2,p;
	if(InitList(T))		
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)//当指针未越界时循环
		{
			if(p1->data<=p2->data)//
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);				
				if(p1->data==p2->data)
					p2=p2->next;
				p1=p1->next;
			}
			else
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p2->data;
				p->next=NULL;
				Append(T,p);
				p2=p2->next;
			}
		}
		while(p1)//p2结束，p1还有元素
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p1->data;
			p->next=NULL;
			Append(T,p);
			p1=p1->next;
		}
		while(p2)//p1结束，p2还有元素
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p2->data;
			p->next=NULL;
			Append(T,p);
			p2=p2->next;
		}
	}
}

void Intersection(OrderedList &T,OrderedList S1,OrderedList S2)//T=L3,S1=L1,S2=L2，求L1与L2的交集，存入L3
{
	LinkType p1,p2,p;
	if(!InitList(T))
		T.head=NULL;
	else
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)
		{
			if(p1->data<p2->data)
				p1=p1->next;
			else if(p1->data>p2->data)
				p2=p2->next;
			else
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);				
				p2=p2->next;
				p1=p1->next;
			}
		}
	}
}

void Difference(OrderedList &T,OrderedList S1,OrderedList S2)//求差集
{
	LinkType p1,p2,p;
	if(!InitList(T))
		T.head=NULL;
	else
	{
		p1=S1.head->next;
		p2=S2.head->next;
		while( p1 && p2)
		{
			if(p1->data<p2->data)
			{
				p=(LinkType)malloc(sizeof(NodeType));
				p->data=p1->data;
				p->next=NULL;
				Append(T,p);
				p1=p1->next;
			}
			else if(p1->data>p2->data)
				p2=p2->next;
			else
			{
				p1=p1->next;				
				p2=p2->next;
			}
		}
		while(p1)
		{
			p=(LinkType)malloc(sizeof(NodeType));
			p->data=p1->data;
			p->next=NULL;
			Append(T,p);
			p1=p1->next;
		}
		
	}
}

void ReadCommand(char &cmd)//打印操作界面
{
	printf("\n--------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t操  作  提  示");
	printf("\n--------------------------------------------------------------------------\n");
	printf("\tMakeSet1------1\t\t\t\tMakeSet2--------2\n\tUnion---------u\t\t\t\tIntersection----i\n\tDifference----d\t\t\t\tQuit------------q\n\tDisplay-------y");
	do{
		printf("\n\n\t请选择操作：");
		cmd=getch();//接受输入操作
		printf("\n--------------------------------------------------------------------------\n");
	}while(cmd!='1' && cmd!='2' && cmd!='u' && cmd!='i' && cmd!='d' && cmd!='q' && cmd!='y');
}
void Interpret(char &cmd)
{
	system("cls");   //清屏
	switch(cmd)
	{
	case '1'://输入set1
		printf("\n\t请输入字符串：");
		gets(a);//先将得到输入存入a串
		printf("\t原始字符串:");
		printf("\t%s\n",a);
		CreateSet(L1, a);//将set1中a-z存入Li链表，并去除重复元素
		printf("\t构建的集合:");
		ListTraverse(L1.head->next,Print);//打印制作好的L1链表
		break;
	case '2'://与case1操作相同
		printf("\n\t请输入字符串：");
		gets(b);
		printf("\t原始字符串:");
		printf("\t%s\n",b);
		CreateSet(L2, b);
		printf("\t构建的集合:");
		ListTraverse(L2.head->next,Print);
		break;
	case 'u'://求合集
		CreateSet(L1, a);
		CreateSet(L2, b);
		Union(L3,L1,L2);
		printf("\n\t集合1:");
		ListTraverse(L1.head->next,Print);
		printf("\t集合2:");
		ListTraverse(L2.head->next,Print);
		printf("\t并集:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'i'://求交集
		CreateSet(L1, a);
		CreateSet(L2, b);
		Intersection(L3,L1,L2);
		printf("\n\t集合1:");
		ListTraverse(L1.head->next,Print);
		printf("\t集合2:");
		ListTraverse(L2.head->next,Print);
		printf("\t交集:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'd'://求差集
		CreateSet(L1, a);
		CreateSet(L2, b);
		Difference(L3,L1,L2);
		printf("\n\t集合1:");
		ListTraverse(L1.head->next,Print);
		printf("\t集合2:");
		ListTraverse(L2.head->next,Print);
		printf("\t差集:");
		ListTraverse(L3.head->next,Print);
		break;
	case 'y'://打印并、交、差集
		printf("\n\t原始字符串:\n");
		printf("\t\t%s\n\t\t%s\n",a,b);		
		CreateSet(L1, a);
		CreateSet(L2, b);
		printf("\t由字符串构建的集合:\n");
		printf("\t");
		ListTraverse(L1.head->next,Print);
		printf("\t");
		ListTraverse(L2.head->next,Print);
		Union(L3,L1,L2);
		printf("\t并集:");
		ListTraverse(L3.head->next,Print);
		
		Intersection(L3,L1,L2);
		printf("\t交集:");
		ListTraverse(L3.head->next,Print);
		
		Difference(L3,L1,L2);
		printf("\t差集:");
		ListTraverse(L3.head->next,Print);
		break;
	}	
}
int main()
{
	char cmd;//输入操作	
	do
	{
		ReadCommand(cmd);
		Interpret(cmd);
	}while(cmd!='q');
	return 0;
}



