#include<iostream>
#include<cstring>
#include<queue>
#include<vector> 
using namespace std;
typedef pair<int,int> P;//fisrt:边权，second:目的顶点编号 
#define MAXV 1000 
#define Inf 0x3f3f//>16000
int V=28,E=30;//顶点数，边数 
int s,ed;//起点，终点 
int cost[MAXV][MAXV];//cost[u][v] 边(u,v)的边权
int d[MAXV];//d[i]表示顶点i到起点的最短路径
int per[MAXV];
int vis[MAXV];//vis[i]标记顶点i是否已求得到起点的最短路径 ,是：1.否：0

void djks(){
	d[s]=0;
	int v,u;
	priority_queue<P,vector<P>, greater<P> > pq;
	pq.push({0,s});
	while(!pq.empty()){
		P p=pq.top();
		pq.pop();
		v=p.second;
		if(d[v]<p.first) continue;//顶点v已更新最短路，取出 
		vis[v]=1;//扩展顶点v
		for(u=1;u<=V;++u)//以顶点v为中间节点去更新其他点到s的最短路 
			if(!vis[u]&&d[u]>d[v]+cost[v][u])
				d[u]=d[v]+cost[v][u],per[u]=v,pq.push({d[u],u});	
	}
}
//打印路径 
void printPath(int v,int ed){
	if(v==ed){
		cout<<v<<" ";
		return;
	}
	printPath(per[v],ed);
	cout<<v<<" ";
}
int main(){
	memset(vis,0,sizeof(vis)); 
	fill(d,d+MAXV,Inf); 
	fill(cost[0],cost[0]+MAXV*MAXV,Inf);
/*
	cin>>V>>E;
	int u,v,w;
	for(int i=0;i<E;++i){//输入E条边 
		cin>>u>>v>>w;
		cost[u][v]=cost[v][u]=w;
	}
*/	
	cost[0][2]=1741;cost[2][0]=1741;
	cost[1][2]=1960;cost[2][1]=1960;
	cost[2][3]=194;cost[3][2]=194;
	cost[3][4]=599;cost[4][3]=599;
	cost[4][5]=250;cost[5][4]=250;
	cost[4][6]=638;cost[6][4]=638;
	cost[5][6]=500;cost[6][5]=500;
	cost[5][7]=384;cost[7][5]=384;
	cost[5][15]=844;cost[15][4]=844;
	cost[7][8]=512;cost[8][7]=512;
	cost[8][9]=500;cost[9][8]=500;
	cost[8][10]=800;cost[10][8]=800;
	cost[9][10]=584;cost[10][9]=584;
	cost[9][12]=680;cost[12][9]=680;
	cost[12][11]=250;cost[11][12]=250;
	cost[12][13]=582;cost[13][12]=582;
	cost[12][22]=660;cost[22][12]=660;
	cost[13][15]=975;cost[15][13]=975;
	cost[14][15]=434;cost[15][14]=434;
	cost[15][17]=392;cost[17][15]=392;
	cost[16][17]=244;cost[17][16]=244;
	cost[16][18]=531;cost[18][16]=531;
	cost[17][19]=331;cost[19][17]=331;
	cost[17][21]=303;cost[21][17]=303;
	cost[19][20]=120;cost[20][19]=120;
	cost[19][26]=976;cost[26][19]=976;
	cost[21][23]=667;cost[23][21]=667;
	cost[23][24]=265;cost[24][23]=265;
	cost[25][26]=302;cost[26][25]=302;
	cost[26][27]=242;cost[27][26]=242;
	cin>>s>>ed;//起点、终点
	djks();
	cout<<d[ed]<<endl;
	printPath(ed,s); 
	return 0;
}

 
 /*
6 9 
1 2 1
1 3 12
2 3 9
2 4 3
3 5 5
4 3 4
4 5 13
4 6 15
5 6 4
*/

