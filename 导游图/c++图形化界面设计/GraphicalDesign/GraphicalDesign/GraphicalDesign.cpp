#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <string.h>
#include<vector>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<graphics.h>
using namespace std;

#define N 9999
#define INF 0x3f3f3f3f
int map[N][N];	//用邻接矩阵来存图；
int dis[N];		//用了记录源点到各顶点的距离；
int vis[N];		//标记顶点是否访问过;
vector<int> path;
int p, q;//求p到q之间的最短路径； 
int num=0;
char city[28][10]={"乌鲁木齐","拉萨","西宁","兰州","成都","重庆","昆明","贵阳","南宁","广州","海口","台北","福州","南昌","西安","郑州","太原","石家庄","呼和浩特","北京","天津","济南","合肥","南京","上海","沈阳","长春","哈尔滨"};
char city2[28][10]={"wlmq","ls","xn","lz","cd","cq","km","gy","nn","gz","hk","tb","fz","nc","xa","zz","ty","sjz","hhht","bj","tj","jn","hf","nj","sh","sy","cc","heb"};
char picture[28][10]={"wlmq.jpg","ls.jpg","xn.jpg","lz.jpg","cd.jpg","cq.jpg","km.jpg","gy.jpg","nn.jpg","gz.jpg","hk.jpg","tb.jpg","fz.jpg","nc.jpg","xa.jpg","zz.jpg","ty.jpg","sjz.jpg","hhht.jpg","bj.jpg","tj.jpg","jn.jpg","nj.jpg","sh.jpg","sy.jpg","cc.jpg","heb.jpg"};
int r[3][4]={{1010,10,1190,40},{1010,50,1190,80},{1010,640,1190,670}};//按钮坐标
int point[28][2]={{230,220},{225,520},{405,410},{445,420},{445,515},{505,545},{415,640},{485,620},{505,690},{615,690},//每个城市的坐标
				  {455,740},{735,630},{695,620},{645,570},{520,440},{595,445},{580,370},{605,370},{560,320},{625,335},
				  {645,345},{645,395},{650,495},{680,505},{720,505},{730,285},{740,235},{760,195}};

int button_judge(int x,int y){//实现鼠标点击选择
	if(x>r[0][0] && x<r[0][2] && y>r[0][1] && y<r[0][3])return 1;//点击为开始导游
	if(x>r[1][0] && x<r[1][2] && y>r[1][1] && y<r[1][3])return 2;//点击为城市介绍
	if(x>r[2][0] && x<r[2][2] && y>r[2][1] && y<r[2][3])return 3;//退出程序
	return 0;
}

void inin(int n){//初始化；
	int i,j;
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (i == j)
				map[i][j] = 0;
			else
				map[i][j] = INF;
		}
	}
	map[0][2]=1741;map[2][0]=1741;
	map[1][2]=1960;map[2][1]=1960;
	map[2][3]=194;map[3][2]=194;
	map[3][4]=599;map[4][3]=599;
	map[4][5]=250;map[5][4]=250;
	map[4][6]=638;map[6][4]=638;
	map[5][6]=500;map[6][5]=500;
	map[5][7]=384;map[7][5]=384;
	map[5][15]=844;map[15][4]=844;
	map[7][8]=512;map[8][7]=512;
	map[8][9]=500;map[9][8]=500;
	map[8][10]=800;map[10][8]=800;
	map[9][10]=584;map[10][9]=584;
	map[9][12]=680;map[12][9]=680;
	map[12][11]=250;map[11][12]=250;
	map[12][13]=582;map[13][12]=582;
	map[12][22]=660;map[22][12]=660;
	map[13][15]=975;map[15][13]=975;
	map[14][15]=434;map[15][14]=434;
	map[15][17]=392;map[17][15]=392;
	map[16][17]=244;map[17][16]=244;
	map[16][18]=531;map[18][16]=531;
	map[17][19]=331;map[19][17]=331;
	map[17][21]=303;map[21][17]=303;
	map[19][20]=120;map[20][19]=120;
	map[19][26]=976;map[26][19]=976;
	map[21][23]=667;map[23][21]=667;
	map[23][24]=265;map[24][23]=265;
	map[25][26]=302;map[26][25]=302;
	map[26][27]=242;map[27][26]=242;
}
void Dijkstra(int st,int n){
	int i, j, k, x;
	path=vector<int>(n,-1);
	for (i = 0; i < n; i++)//用dis数组记录源点到与它相连接的顶点的距离；
		dis[i] = map[st][i];
	vis[st] = 1;//标记刚才源点,表示已经访问；
	while (1){
		x = -1;
		int min = INF;
		for (i = 0; i < n; i++){//在当前的dis距离数组中找到一个最小的路径，并将这条路到达的顶点记录；
			if (vis[i] != 1 && dis[i] < min){
				min = dis[i];
				x = i;
			}
		}
		vis[x] = 1;
		if (x == -1)//直到所有的顶点都已访问过，结束循环
			break;
		for (i = 0 , k=0; i < n; i++){//更新dis数组，
			if (vis[i] != 1 && dis[i] > min + map[x][i]){
				dis[i] = min + map[x][i];
				path[i]=x;
			}
		}
	}
}

void get_path(int x,vector<int>&P){
	if(!x){
		P.push_back(0);
		return;
	}
	if(path[x]!=-1)
		get_path(path[x],P);
	P.push_back(x);
	num++;
}

int main(){

	int p=-1,q=-1;
	vector<int> P;
	int start[2],end[2];
	inin(30);//初始化图
	initgraph(1200,1000);
	IMAGE img;
	IMAGE im;
	loadimage(&img,"a.jpg",1000,800);//打开地图
	putimage(0,0,&img);
	setbkmode(TRANSPARENT);
	settextstyle(30,0,"宋体");//s为字体种类如“宋体”
	settextcolor(RED);
	outtextxy(450,10,"导游图");
	settextstyle(20,0,"宋体");
	
	RECT R1={r[0][0],r[0][1],r[0][2],r[0][3]};
	RECT R2={r[1][0],r[1][1],r[1][2],r[1][3]};
	RECT R3={r[2][0],r[2][1],r[2][2],r[2][3]};
	drawtext("开始导游",&R1,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("城市介绍",&R2,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("退出程序",&R3,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	while(true){
	
		MOUSEMSG m;//鼠标指针
		m = GetMouseMsg();//获取一条鼠标消息
		switch(m.uMsg){
			case WM_LBUTTONDOWN://左键点击
				switch(button_judge(m.x,m.y)){//判断鼠标点击哪个按钮

					case 1:
						setfillcolor(BLACK);
						solidrectangle(1010,10,1190,80);//将初始信息覆盖，生成新的信息
						outtextxy(1000,10,"起点：");
						rectangle(1100,10, 1190, 30);//绘制边框
						outtextxy(1000,40,"终点：");
						rectangle(1100,40, 1190, 60);//绘制边框
						char a[10],b[10];
						InputBox(a,30,"起点：");//输入起点城市
						InputBox(b,30,"终点：");//输入终点城市
						for(int i=0;i<28;i++){
							if(strcmp(a,city2[i])==0){
								p=i;
								outtextxy(1100,10,city[p]);
							}
							if(strcmp(b,city2[i])==0){
								q=i;
								outtextxy(1100,40,city[q]);
							}
						}
						if(p==-1||q==-1){
							outtextxy(1100,90,"输入错误");
							system("pause");
							return 0;
						}
						Dijkstra(p,28);
						get_path(q,P);
						setcolor(YELLOW);
						outtextxy(1000,70,"推荐路线:");
						outtextxy(1000,110,city[p]);//起点
						char t[5];
						sprintf(t, "%d",dis[p]);
						outtextxy(1080,110,t);
						fillcircle(point[p][0],point[p][1],5);
						start[0]=point[p][0];
						start[1]=point[p][1];
						
						for(int i=0;i<num;i++){//打印路径
							end[0]=point[P[i]][0];
							end[1]=point[P[i]][1];
							char s[10];
							sprintf(s, "%d",dis[P[i]]);
							setcolor(YELLOW);
							outtextxy(1000,130+i*20,city[P[i]]);
							outtextxy(1080,130+i*20,s);
							fillcircle(point[P[i]][0],point[P[i]][1],5);
							setcolor(RED);
							line(start[0],start[1],end[0],end[1]);
							start[0]=end[0];
							start[1]=end[1];
						}
						system("pause");
						break;
					case 2://城市介绍
							setfillcolor(BLACK);
							solidrectangle(1000,360,1200,400);
							setfillcolor(RED);
							char c[10];
							InputBox(c,30,"输入想看的城市：");
							for(int i=0;i<28;i++){//查找城市
								if(strcmp(c,city2[i])==0){
									setcolor(YELLOW);
									settextstyle(14,0,"宋体");
									outtextxy(1000,380,city[i]);
									loadimage(&im,picture[i],200,200);
									putimage(1000,400,&im);
									break;
								}
							}
						getchar();
						break;
					case 3://直接退出程序
						return 0;
					default:
						FlushMouseMsgBuffer();//单击事件后清空鼠标消息
						//printf("\r\n(%d,%d)",m.x,m.y);//打印鼠标坐标，方便调试时确定区域
						break;
				}
				break;
		}
	}
	getchar();
	closegraph();
	getchar();
	return 0;
}


						//fillrectangle(220,210,240,230);//乌  230,220
						//fillrectangle(215,510,235,530);//拉萨	225,520
						//fillrectangle(395,400,415,420);//西宁	405,410
						//fillrectangle(435,410,455,430);//兰州	445,420
						//fillrectangle(435,520,455,540);//成都	445,510
						//fillrectangle(485,535,515,555);//重庆	505,545
						//fillrectangle(405,630,425,650);//昆明	415,640
						//fillrectangle(475,610,495,630);//贵阳	485,620
						//fillrectangle(495,680,515,700);//南宁	505,690
						//fillrectangle(595,670,615,690);//广州	605,680
						////海口	455,740
						//fillrectangle(725,620,755,640);//台北	735,630
						//fillrectangle(685,610,705,630);//福州	695,620
						//fillrectangle(635,560,655,580);//南昌	645,570
						//fillrectangle(510,440,530,460);//西安	515,430
						//fillrectangle(585,435,605,455);//郑州	595,445
						//fillrectangle(570,360,590,380);//太原	580,370
						//fillrectangle(595,360,615,380);//石家庄	605,370
						//fillrectangle(550,310,570,330);//呼和浩特	560,320
						//fillrectangle(615,325,635,345);//北京	625,335
						//fillrectangle(635,335,655,355);//天津	645,345
						//fillrectangle(635,385,655,405);//济南	645,395
						//fillrectangle(640,485,660,505);//合肥	650,495
						//fillrectangle(670,485,690,505);//南京	680,505
						//fillrectangle(710,495,730,515);//上海	720,505
						//fillrectangle(720,275,740,295);//沈阳	730,285
						//fillrectangle(730,225,750,245);//长春	740,235
						//fillrectangle(750,185,770,205);//哈尔滨	760,195


