#include<iostream>
#define MAXN 100
using namespace std;
struct Point{
	int x;
	int y;
};
Point visitlist[MAXN];
Point resultlist[MAXN][MAXN];
int map[MAXN][MAXN];
int visit[MAXN][MAXN];
int dir_x[4]={0,1,0,-1};
int dir_y[4]={1,0,-1,0};
int final_x,final_y;
int minstep=9999;
int step=1;
int path_num=0;
int minpath=9999;
void dfs(int step,int x,int y){
	if(x==final_x&&y==final_y){//到终点 
		cout<<"step=="<<step<<endl;//输出步数 
		if(step<minstep){//判断最短路径 
			minstep=step;
			minpath=path_num;
		}
		resultlist[path_num][0].x=step;
		for(int i=1;i<=step;i++){
//			cout<<"visitlist:"<<visitlist[i].x<<" "<<visitlist[i].y<<endl;
			resultlist[path_num][i]=visitlist[i];
		}
		path_num++;
		return;
	}
	for(int i=0;i<4;i++){//递归找路 
		if(visit[x+dir_x[i]][y+dir_y[i]]==0 && map[x+dir_x[i]][y+dir_y[i]]==1){
			visit[x+dir_x[i]][y+dir_y[i]]=1;
			visitlist[step].x=x+dir_x[i];
			visitlist[step].y=y+dir_y[i];
			dfs(step+1,x+dir_x[i],y+dir_y[i]);
			visit[x+dir_x[i]][y+dir_y[i]]=0;
		}
	}
}
int main(){
    int hight,kuan;
    cin>>hight>>kuan;//输入长宽 
    final_x=0,final_y=10;
     	for(int i=0;i<hight;i++){//输入迷宫 
        	for(int j=0;j<kuan;j++){
            char ch;
            cin>>ch;
            if(ch=='@'){
               map[i][j]=1;
            }
        }
    }
    for(int i=0;i<hight;i++){
        for(int j=0;j<kuan;j++){//输出迷宫数组 
            cout<<map[i][j]<<" ";
        }
        cout<<endl;		
    }
	dfs(step,0,1);
	cout<<"最短长度："<<"  "<<minstep<<endl;
	cout<<">---------------------<"<<endl;
	for(int k=0;k<path_num;k++){
		cout<<"第 "<<k+1<<" 条路径"<<endl;
		if(k==minpath){
			cout<<"这个是最短路径:"<<endl;
		}
		for(int i=0;i<hight;i++){
			for(int j=0;j<kuan;j++){
				bool flag=false;
				for(int l=1;l<resultlist[k][0].x;l++){
				//	cout<<resultlist[k][l].x<<" "<<resultlist[k][l].y<<endl;
					if((resultlist[k][l].x==i && resultlist[k][l].y==j) || (i==0 & j==1)){
						flag=true;
						cout<<'&';
						break;
					}
				}
				if(!flag){
					if(map[i][j]==1){
						cout<<'@';
					}else{
						cout<<'#';
					}
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
    return 0;
}
/*
5 11
#@#####@@@@
#@#####@##@
#@@@@@@@##@
#@#@@#@###@
#@##@@@@@@@
*/
