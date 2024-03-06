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
typedef struct
{
	int weight;					//权值分量（可放大取整）
	int parent,lchild,rchild;		//双亲和孩子分量
}HTNode,*HuffmanTree;					//用动态数组存储Huffman树
typedef  char**HuffmanCode;				//动态数组存储Huffman编码表


void Select(HuffmanTree HT, int s, int &s1, int &s2)
{
	int i;
	int min1=RAND_MAX,min2=RAND_MAX;
	s1=-1;
	s2=-1;
	for(i=1;i<=s ;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<min2)
			{
				if(HT[i].weight<min1)
				{
					min2=min1;
					min1=HT[i].weight;
					s2=s1;
					s1=i;
				}
				else
				{
					min2=HT[i].weight;
					s2=i;
				}
			}
		}
	}
}


void  HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	HuffmanTree p;
	int i,m,s1,s2;
	int c,f,start;	//用无栈非递归遍历赫夫曼树求赫夫曼编码时注销此行
	//int cdlen,k;	//从叶子到跟逆向求每个字符的哈夫曼编码时注销此行
	char *cd;
	if(n<=1)
		return;
	m=2*n-1;    //n个叶子的HuffmanTree共有2n-1个结点;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0单元未用
	for(p=HT+1,i=1; i<=n; ++i,++p,++w)
	{
		p->lchild=0;
		p->parent=0;
		p->rchild=0;
		p->weight=*w;
	}//给前n0个单元初始化
	
	for(;i<=m; ++i,++p)
	{
		p->lchild=0;
		p->parent=0;
		p->rchild=0;
		p->weight=0;
		
	}//对叶子之后的存储单元清零
	for(i=n+1;i<=m; ++i)
	{    //建Huffman树(从叶子后开始存内结点) 
		Select(HT, i-1, s1, s2);   //在HT[1…i-1]选择parent为0且weight最小的两个结点，其序号分别为S1和s2（教材未给出此函数源码）
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+ HT[s2].weight;
	}
	//从叶子到跟逆向求每个字符的哈夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));						//分配n个字符编码的头指针向量（一维数组）
	cd=(char *) malloc(n*sizeof(char));								//分配求编码的工作空间(n) 
	cd[n-1]='\0';														//编码结束符（从cd[0]~cd[n-1]为合法空间）
	for(i=1;i<=n;++i)
	{																//逐个字符求Huffman编码
		start=n-1;														//编码结束符位置
		for(c=i,f=HT[i].parent;   f!=0;   c=f, f=HT[f].parent)			//从叶子到根逆向求编码
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
			HC[i]=(char*)malloc((n-start)*sizeof(char));				//为第i个字符编码分配空间
			strcpy(HC[i],&cd[start]);									//从cd复制编码串到HC
	}
///////////////////////////////////////////////////////////////////////
	/*
	//----------无栈非递归遍历赫夫曼树,求赫夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char*) malloc(n*sizeof(char)); //分配求编码的工作空间(n) 
	k=m;
	cdlen=0;
	for(i=1;i<=m;++i)
		HT[i].weight=0;  //遍历赫夫曼树时用作结点状态标志
	while(k)
	{
		if(HT[k].weight==0) 		//向左
		{		
			HT[k].weight=1;
			if(HT[k].lchild!=0)
			{
				k=HT[k].lchild;
				cd[cdlen++]='0';
			}
			else if(HT[k].rchild==0)      //登记叶子结点的字符的编码
			{
				HC[k]=(char *)malloc((cdlen+1) *sizeof(char));
				cd[cdlen]='\0';
				strcpy(HC[k],cd); //复制编码(串)
			}
		}
		else if (HT[k].weight==1) //向右
		{	
			HT[k].weight=2;
			if(HT[k].rchild!=0)
			{
				k=HT[k].rchild;
				cd[cdlen++]='1';
			}
		}
		else		 //HT[p].weight==2,退回
		{	
			HT[k].weight=0;
			k=HT[k].parent;	
			--cdlen;
			//退到父结点,编码长度减1
		}//else
	}//while
//////////////////////////////////////////////////////////////
*/
	free(cd);	//释放工作空间	
}//HuffmanCoding

int main()
{
	int w[]={5, 6, 2, 4, 14, 23, 3, 11};
	int i,n;
	HuffmanTree tree;
	HuffmanCode HC;
	n=sizeof(w)/sizeof(int);
	HuffmanCoding(tree, HC, w, n);
	for(i=1;i<=n;i++)
	{
		printf("%s\n",HC[i]);
	}
	return 0;
}
