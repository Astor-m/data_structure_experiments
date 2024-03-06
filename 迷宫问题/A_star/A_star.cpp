#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
#define MAXN 99
#define MAXWEIGHT 99
struct Point{
    int x;
    int y;
};
int dir_x[4]={0,1,0,-1};
int dir_y[4]={1,0,-1,0};
int hight,weight;
int numvex;
int map[MAXN][MAXN];
int visit[MAXN][MAXN];
int arc[MAXN*MAXN][MAXN*MAXN];
int start_x,start_y,end_x,end_y;
int shortpathtable[MAXN*MAXN][MAXN*MAXN];
int patharc[MAXN*MAXN];
int index=1,index_vex=1;
void init_map(){
    for(int i=0;i<hight;i++){
        for(int j=0;j<weight;j++){
            char ch;
            cin>>ch;
            if(ch == '@'){
                map[i][j]=1;
                numvex++;
                visit[i][j]=numvex;
            }
        }
    }
}

void init_dijkstar(){
    for(int i=1;i<=numvex;i++){
		for(int j=1;j<=numvex;j++){
			arc[i][j]=MAXN;
		}
	}
    for(int i=0;i<hight;i++){
        for(int j=0;j<weight;j++){
            if(map[i][j]==1){
                for(int k=0;k<3;k++){
                    if(map[i+dir_x[k]][j+dir_y[k]] == 1){
                        arc[visit[i][j]][visit[i+dir_x[k]][j+dir_y[k]]]=1;
                    }
                }
            }
        }
    }
}

void dijkstar(int x,int y){
	int start=visit[x][y];
	int end = visit[end_x][end_y];
	
	for(int i=1;i<=numvex;i++){
		shortpathtable[i][index]=arc[start][i];
//		cout<<shortpathtable[i][index]<<" "<<arc[start][i]<<endl;
		patharc[i]=0;
	}
	patharc[start]=index_vex;
	shortpathtable[start][index]=0;//
	for(int i=2;i<=numvex;i++){
//		cout<<shortpathtable[i][index]<<" ";
		int minpath=MAXN;
		int k=0;
		for(int j=2;j<=numvex;j++){
//			if(patharc[j]==0 && shortpathtable[j][index]<=30)
//				cout<<shortpathtable[j]<<" ";
			if(patharc[j]==0 && minpath>shortpathtable[j][index]){
				k=j;
				minpath=shortpathtable[j][index];
			}
		}
//		patharc[k]=1;
//		cout<<endl;
//		cout<<k<<"号点被纳入 最短距离是"<<minpath<<endl;
		index_vex++;
		patharc[k]=index_vex;
		index++;
		if(k==end){
			cout<<"找到终点最短长度为"<<minpath<<endl;
			return ;
		}
		for(int j=2;j<=numvex;j++){
			if(patharc[j]==0){
//				cout<<"比较   "<<shortpathtable[j][index-1]<<" "<<minpath+arc[k][j]<<endl;
				if(shortpathtable[j][index-1]>minpath+arc[k][j]){
					shortpathtable[j][index]=minpath+arc[k][j];
//					cout<<"233"<<endl;
				}else{
					shortpathtable[j][index]=shortpathtable[j][index-1];
//					cout<<"114514"<<endl;
				}
			}
//			cout<<shortpathtable[j][index]<<" ";
		}
//		cout<<endl;
	}
}
void findpath(){
	stack<int> s;
	int pre=visit[end_x][end_y];
	int n=index-1;
	s.push(pre);
	while(pre!=1){
		if(shortpathtable[pre][n]==shortpathtable[pre][n-1]){
			n--;
		}
		else{
			for(int i=1;i<=numvex;i++){
				 if(patharc[i]==n){
//				 	cout<<"路过的节点:"<<i<<endl;
				 	s.push(i);
				 	pre=i;
				 	n--;
					break;	
				 }
			}
		}
	}
	while(!s.empty()){
		int t=s.top();
		cout<<"经过: "<<t<<" 号节点"<<endl;
		s.pop();
	}
}
int main(){
    cin>>hight>>weight;
    cin>>start_x>>start_y>>end_x>>end_y;
    init_map();
    init_dijkstar();
    dijkstar(start_x,start_y);
	findpath();
    return 0;
}
/*
5 11
0 1
4 10
#@#####@@@@
#@#####@##@
#@@@@@@@##@
#@#@@#@###@
#@##@@@@@@@
*/
