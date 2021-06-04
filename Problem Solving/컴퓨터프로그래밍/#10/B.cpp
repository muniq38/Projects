
#include <bits/stdc++.h>
using namespace std;
int mv[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
char Board[1500][1500]={};
int Vis[1500][1500]={};

int main()
{
    int N, M; scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++) scanf("%s", Board[i]+1);
    queue<int> X, Y;
    
    int Ans=0;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++)
    if(!Vis[i][j] && Board[i][j]=='1'){
        X.push(i); Y.push(j); Ans++; Vis[i][j]=Ans;
        while(!X.empty()){
            int x = X.front(), y = Y.front();
            X.pop(); Y.pop();
            for(int k=0; k<4; k++){
                int nx = x+mv[k][0], ny = y+mv[k][1];
                if(!Vis[nx][ny] && Board[nx][ny]=='1'){
                    Vis[nx][ny]=Ans; X.push(nx); Y.push(ny);
                }
            }
        }
    }
    
    printf("%d\n", Ans);
}

