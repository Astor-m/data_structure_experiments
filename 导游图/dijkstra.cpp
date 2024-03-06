#define _CRT_SECURE_NO_WARINGS
#include<bits/stdc++.h>
using namespace std;

const int inf=9999;
vector<vector<int> > G(21,vector<int>(21,inf));
vector<int> path;

vector<int> dijkstra(vector<vector<int> >G,int s){
	int n=G.size();
	vector<int> dis(n,inf);
	vector<int> vis(n,false);
	dis[s]=0;
	for(int i=0;i<n-1;i++){
		int node=-1;
		for(int j=0;j<n;j++)
			if(!vis[j]&&(dis[j]<dis[node]||j==-1))
				node=j;
		for(int j=0;j<n;j++){
			dis[j]=min(dis[j],dis[node]+G[node][j]);
			if(dis[j]+G[node][j]<dis[j]){
				dis[j]=dis[node]+G[node][j];
				path[j]=node;
			}
		}
		vis[node]=true;
	}
	return dis;
}

void get_path(int x,vector<int>&P){
	cout<<endl<<x;
	if(x==0){
		P.push_back(0);
		return;
	}
	if(path[x]!=-1)
		get_path(path[x],P);
	P.push_back(x);
}

int main(){
	int n;
	cin>>n;
	path=vector<int>(n,-1);
	vector<vector<int> > G(n,vector<int>(n));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>G[i][j];
	vector<int> dis=dijkstra(G,0);
	
	for(int i=0;i<dis.size();i++)
		cout<<dis[i]<<" ";
	cout<<endl;
	 
	vector<int> P;
	get_path(4,P);
	cout<<endl;
	for(int i=0;i<P.size();i++)
		cout<<P[i]<<" ";
		
	return 0;
}

/*
6
0  99 1  6  5  99
99 0  2  4  1  3
1  2  0  99 99 99
6  4  99 0  99 99
5  1  99 99 0  99
99 3  99 99 99 99


*/
