
#include <bits/stdc++.h>
#define INF 123456789
using namespace std;
int Vis[1100][1100]={}, 
 Sum[1100][1100]={}, 
 Board[1100][1100]={};
int mv[4][2]={{0,1},{0,-1},{1,0},{-1,0}}; 
int N, M;
queue<int> X, Y;

void BFS(){
    while(!X.empty()){
        int x = X.front(), y = Y.front();
        X.pop(); Y.pop();
        for(int i=0; i<4; i++){
            int xn = x+mv[i][0], yn = y+mv[i][1];
            if(1<=xn && xn<=N && 1<=yn && yn<=M)
            if(Board[xn][yn]!=1 && !Vis[xn][yn]){
                Vis[xn][yn] = Vis[x][y]+1;
                X.push(xn); Y.push(yn);
            }
        }
    }for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        Sum[i][j] += Vis[i][j] ? Vis[i][j]-1 : INF;
        Vis[i][j] = 0;
    }
}

int main()
{
    scanf("%d %d", &M, &N);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++)
    scanf("%d", &Board[i][j]);
    
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if(Board[i][j]==2){
            X.push(i); Y.push(j); Vis[i][j]=1;
        }
    } BFS();
    
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if(Board[i][j]==3){
            X.push(i); Y.push(j); Vis[i][j]=1;
        }
    } BFS();
    
    int Min = INF;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if(Board[i][j]==4) Min = min(Min, Sum[i][j]);
    }printf("%d\n", Min);
    return 0;
}

