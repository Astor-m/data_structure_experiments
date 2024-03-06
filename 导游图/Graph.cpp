// Graph.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define M  55555
#define MAXV 40
#define FALSE  0
#define TRUE   1

typedef struct  //图的存储类型
{
	char vexs[MAXV][9];
	char xiaobin[MAXV][40];
	int  arcs[MAXV][MAXV];
	int  vexnum;
}MGraph;

int p[MAXV][MAXV][MAXV];
int d[MAXV][MAXV];


void chushi(MGraph &G)    //初始化图， 相当于输入一个图
{
	int i, j;
	
	strcpy(G.vexs[0], "乌鲁木齐");
	strcpy(G.vexs[1], "西宁");
	strcpy(G.vexs[2], "兰州");
	strcpy(G.vexs[3], "呼和浩特");
	strcpy(G.vexs[4], "北京");
	strcpy(G.vexs[5], "天津");
	strcpy(G.vexs[6], "沈阳");
	strcpy(G.vexs[7], "长春");
	strcpy(G.vexs[8], "哈尔滨");
	strcpy(G.vexs[9], "大连");
	strcpy(G.vexs[10], "西安");
	strcpy(G.vexs[11], "郑州");
	strcpy(G.vexs[12], "徐州");
	strcpy(G.vexs[13], "成都");
	strcpy(G.vexs[14], "武汉");
	strcpy(G.vexs[15], "上海");
	strcpy(G.vexs[16], "昆明");
	strcpy(G.vexs[17], "贵阳");
	strcpy(G.vexs[18], "株洲");
	strcpy(G.vexs[19], "南昌");
	strcpy(G.vexs[20], "福州");
	strcpy(G.vexs[21], "柳州");
	strcpy(G.vexs[22], "南宁");
	strcpy(G.vexs[23], "广州");
	strcpy(G.vexs[24], "深圳");

	
	G.vexnum=25;
	
	for(i=0; i<G.vexnum; i++)
		for(j=0; j<i; j++)
			G.arcs[i][j]=M;
			
	for(i=0; i<G.vexnum; i++)
		G.arcs[i][i]=0;

    for(i=0; i<G.vexnum; i++)
		for(j=i; j<G.vexnum; j++)
			G.arcs[i][j]=M;

    G.arcs[0][2]=1892,  G.arcs[1][2]=216,   G.arcs[2][3]=1145,    G.arcs[3][4]=668,   G.arcs[4][5]=137;
    G.arcs[11][12]=349, G.arcs[5][6]=704,   G.arcs[6][7]=305,     G.arcs[6][9]=397,   G.arcs[7][8]=242;
    G.arcs[10][13]=842, G.arcs[2][10]=676,  G.arcs[10][11]=511,   G.arcs[4][11]=695,  G.arcs[5][12]=674;
    G.arcs[11][14]=534, G.arcs[12][15]=651, G.arcs[13][16]=1100,  G.arcs[13][17]=967, G.arcs[16][17]=639;
    G.arcs[17][18]=902, G.arcs[17][21]=607, G.arcs[21][22]=255,   G.arcs[18][21]=672, G.arcs[18][14]=409;
    G.arcs[18][19]=367, G.arcs[18][23]=675, G.arcs[23][24]=140,   G.arcs[19][20]=622, G.arcs[15][19]=825;
    
    for(i=0; i<G.vexnum; i++)
       for(j=i; j<G.vexnum; j++)
       	   if(G.arcs[i][j]!=M && G.arcs[j][i]==M)
       	       G.arcs[j][i]=G.arcs[i][j];
       	       
    strcpy(G.xiaobin[0], "中国最西北边的大城市！");
	strcpy(G.xiaobin[1], "西宁, 好，有空去玩!");
	strcpy(G.xiaobin[2], "拉面赫赫有名的地方！");
	strcpy(G.xiaobin[3], "有空去见识见识这个城市!");
	strcpy(G.xiaobin[4], "中国首都");
	strcpy(G.xiaobin[5], "麻花很有名，不过我还没有吃过！");
	strcpy(G.xiaobin[6], "是不是工业基地，我还不清楚!");
	strcpy(G.xiaobin[7], "要是真是永远是春天就好了!");
	strcpy(G.xiaobin[8], "冰雕很漂亮");
	strcpy(G.xiaobin[9], "好像有个大港口!");
	strcpy(G.xiaobin[10], "兵马俑让人失望！");
	strcpy(G.xiaobin[11], "在中国的中部");
	strcpy(G.xiaobin[12], "也跟我一样姓徐啊! 呵呵!");
	strcpy(G.xiaobin[13], "没听说过！");
	strcpy(G.xiaobin[14], " 好地方！");
	strcpy(G.xiaobin[15], "很想去闯一闯的地方！");
	strcpy(G.xiaobin[16], "听说是四季如春的地方");
	strcpy(G.xiaobin[17], "太阳很稀有的地方，否则怎么叫贵阳!?");
	strcpy(G.xiaobin[18], "听说是火车拉来的城市！");
	strcpy(G.xiaobin[19], "八一起义！");
	strcpy(G.xiaobin[20], "不了解");
	strcpy(G.xiaobin[21], "和我一样，不怎么样!");
	strcpy(G.xiaobin[22], "看清楚了，不是海南啊！");
	strcpy(G.xiaobin[23], "妹妹在广州打工！");
	strcpy(G.xiaobin[24], "经济特区！");
}


void ShortestPath_FLOYD(MGraph g)//找最短路径
{
	int i, j, k, l;
	
	for(i=0; i<g.vexnum; i++)
		for(j=0; j<g.vexnum; j++)
		{
		    d[i][j]=g.arcs[i][j];
		    for(k=0; k<g.vexnum; k++)
		        p[i][j][k]=FALSE;
		    if(d[i][j]<M)
		    {
		    	p[i][j][i]=TRUE;
		    	p[i][j][j]=TRUE;
		    }
		}
		
	for(k=0; k<g.vexnum; k++)
	    for(i=0; i<g.vexnum; i++)
	        for(j=0; j<g.vexnum; j++)
	            if(d[i][k]+d[k][j]<d[i][j])
	            {
	            	d[i][j]=d[i][k]+d[k][j];
	            	for(l=0; l<g.vexnum; l++)
	            	    p[i][j][l]=p[i][k][l] || p[k][j][l];
	            }    
}


void windows(char &a)
{
	do
	{
	    system("cls");	
	    printf("\n\t╔━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╗\n\t┃");
	    printf("\t\t\t\t\t\t\t    ┃\n\t┃\t\t\t * 操作说明 *\t\t\t    ┃\n\t┃");
	    printf("\t\t\t\t\t\t\t    ┃\n\t┃    城市解说--------j\t\t\t行程指南---------z  ┃\n\t┃");
	    printf("\t\t\t\t\t\t\t    ┃\n\t┃\t\t\t\t\t退出程序---------t  ┃");
	    printf("\n\t╚━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╝\n");
		printf("\n\n\t请选择操作:");
		a=getch();
	}while(a!='j' && a!='z' && a!='t');
}

void print(MGraph g)
{
	int i;
	printf("\n\n\t    %d.%s\n\t   ", 0, g.vexs[0]);
	for(i=1; i<g.vexnum; i++)
	{
		printf("%2d.%-8s", i, g.vexs[i]);
		if(!(i%6))
		printf("\n\t   ");
	}
}


void reprint()
{
   	system("cls");
    printf("\n\t输入错误! 请重新输入!%c\n", 7);
}


void choose1(MGraph g, int &num)
{  
    do
    { 
    	print(g);
        printf("\n\n\t请选择你要了解的城市:");
        scanf("%d", &num);
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum);
}


void choose2(MGraph g, int &num)
{  
    do
    { 
    	print(g);
        printf("\n\n\t请选择你要的起点城市:");
        scanf("%d", &num);
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum);
}


void choose3(MGraph g, int &num, int m)
{  
    do
    { 
        print(g);
        printf("\n\t您刚才选择的起点城市为: %s !\n", g.vexs[m]);
        printf("\n\t好了,请选择你要的目的城市:");
        scanf("%d", &num);
        if(num==m)
        {
             printf("\n\n\t\t抱歉,您选的起点城市和终点城市为同一城市!%c", 7);
             printf("\n\n\t\t 请重新输入!");
             getch();
             system("cls");
        }
        if (num<0 || num>=g.vexnum)
        reprint();
    }while(num<0 || num>=g.vexnum || num==m);
}


void find(MGraph g)
{
	int a, b, i, j, l, m, fz[MAXV];
	choose2(g, a);
	choose3(g, b, a);
	printf("\n\t\t从%s到%s最近的路程有%d千米!", g.vexs[a], g.vexs[b], d[a][b]);
	printf("\n\n\t\t路线为:\n");
	for(i=0, j=0; i<g.vexnum; i++)
	    if(p[a][b][i])
	        fz[j++]=i;         //用数组记录路线上的城市
	for(m=0, l=1; m<j; m++)       //路线上总共有j个城市要输出
	    for(i=0; i<j; i++)     //找与d[a]直接相连的城市
	       if(g.arcs[a][fz[i]]!=M)//主要是给沿途城市排序
	       {
	          printf("\n\t\t\t%d.%s--%dKm", l++, g.vexs[fz[i]], g.arcs[a][fz[i]]);
	          g.arcs[fz[i]][a]=M;
		      a=fz[i];
	       }
	getch();
}


void jieshao(MGraph g, int n) //城市相关信息介绍
{
	printf("\n\t\t%s", g.xiaobin[n]);
	getch();
}


void choose(MGraph g, char c)
{
	int h;
	switch(c)
	{
	    case 'z':
                find(g);
		        break;
	    case 'j':
	            choose1(g, h);
		        jieshao(g, h);
	}
}


int main()
{
	char a;
	MGraph g;    //定义一个图
	
	chushi(g);   //输入一个图
	ShortestPath_FLOYD(g);   //求个点之间的最短路径
	
	do
    {
        windows(a);         // 显示窗口
        choose(g, a);
    }while(a!='t');
	return 0;
}
