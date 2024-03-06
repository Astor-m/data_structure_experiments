#include<iostream>
#include<string.h>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
#define N 9999
#define INF 0x3f3f3f3f
int mp[N][N];	//用邻接矩阵来存图；
int dis[N];		//用了记录源点到各顶点的距离；
int vis[N];		//标记顶点是否访问过;
vector<int> path;
int p, q;//求p到q之间的最短路径； 
int num=0;
int n=28, m=30;

void inin(int n){//初始化；
	int i,j;
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (i == j)
				mp[i][j] = 0;
			else
				mp[i][j] = INF;
		}
	}
}

void Dijkstra(int st,int n){//这里的st是源点，和prime算法中的st不同，这个不是任意的，而是根据题目要求的源点；
	int i, j, k, x;
	for (i = 0; i < n; i++)//将第i行取出来，用dis数组记录源点到与它相连接的顶点的距离；
		dis[i] = mp[st][i];
	vis[st] = 1;//标记刚才源点,表示已经访问；
	while (1){
		x = -1;
		int min = INF;
		for (i = 0; i < n; i++){//在当前的dis距离数组中找到一个最小的路径，并将这条路到达的顶点记录；
			if (vis[i] != 1 && dis[i] < min){//找到st点到下一个最短距离的点并用p记录该点 
				min = dis[i];
				x = i;
			}
		}
		vis[x] = 1;//表示p点已被访问 
		if (x == -1)//直到所有的顶点都已访问过，结束循环，当然，这是最坏的情况，如果在不考虑时间的情况下，可以这么写；
			break;
		for (i = 0 ; i < n; i++){//更新dis数组，
			if (vis[i] != 1 && dis[i] > min + mp[x][i]){//记录p点到下一个最短距离的点，并判断新的距离是否比已有距离短 
				dis[i] = min + mp[x][i];
				path[i]=x;
			}
		}
	}
}


void get_path(int x,vector<int>&P){
	if(x==p){
		P.push_back(0);
		return;
	}
	if(path[x]!=-1)
		get_path(path[x],P);
	P.push_back(x);
	num++;
}

int main(){
	int i, j;
//	cin >> n >> m;//n个顶点，m条边
	inin(n);
	path=vector<int>(n,-1);
/* 
	for (i = 0; i < m; i++){
		int a, b, x;
		cin >> a >> b >> x;//a和b之间的距离是x
		mp[a][b] = x;//无向图；
		mp[b][a] = x;
	}
*/
	mp[0][2]=1741;mp[2][0]=1741;
	mp[1][2]=1960;mp[2][1]=1960;
	mp[2][3]=194;mp[3][2]=194;
	mp[3][4]=599;mp[4][3]=599;
	mp[4][5]=250;mp[5][4]=250;
	mp[4][6]=638;mp[6][4]=638;
	mp[5][6]=500;mp[6][5]=500;
	mp[5][7]=384;mp[7][5]=384;
	mp[5][15]=844;mp[15][4]=844;
	mp[7][8]=512;mp[8][7]=512;
	mp[8][9]=500;mp[9][8]=500;
	mp[8][10]=800;mp[10][8]=800;
	mp[9][10]=584;mp[10][9]=584;
	mp[9][12]=680;mp[12][9]=680;
	mp[12][11]=250;mp[11][12]=250;
	mp[12][13]=582;mp[13][12]=582;
	mp[12][22]=660;mp[22][12]=660;
	mp[13][15]=975;mp[15][13]=975;
	mp[14][15]=434;mp[15][14]=434;
	mp[15][17]=392;mp[17][15]=392;
	mp[16][17]=244;mp[17][16]=244;
	mp[16][18]=531;mp[18][16]=531;
	mp[17][19]=331;mp[19][17]=331;
	mp[17][21]=303;mp[21][17]=303;
	mp[19][20]=120;mp[20][19]=120;
	mp[19][26]=976;mp[26][19]=976;
	mp[21][23]=667;mp[23][21]=667;
	mp[23][24]=265;mp[24][23]=265;
	mp[25][26]=302;mp[26][25]=302;
	mp[26][27]=242;mp[27][26]=242;

	cin >> p >> q;//输入起点和终点
	Dijkstra(p,n);
	cout << dis[q] << endl;//打印最短路距离 
	vector<int> P;
	for(int i=0;i<n;i++)
		cout<<path[i]<<" ";
	cout<<endl;
	get_path(q,P);
	for(int i=0;i<num;i++)//打印最短路径 
		cout<<P[i]<<" ";
	return 0;
}
