
#include <bits/stdc++.h>
using namespace std;
int mv[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    int T, M, N, K;
    int Vis[150][150]={}, Board[150][150]={};
    scanf("%d", &T);
    while(T--){
        
        scanf("%d %d %d", &M, &N, &K);
        for(int i=0; i<=M+1; i++) for(int j=0; j<=N+1; j++){
            Board[i][j]=0; Vis[i][j]=0;
        }for(int i=1; i<=M; i++) for(int j=1; j<=N; j++){
            int X; scanf("%d", &X); Board[i][j] = (X>K); 
        }
        
        queue<int> X, Y; int Ans=0;
        for(int i=1; i<=M; i++) for(int j=1; j<=N; j++) if(Board[i][j] && !Vis[i][j]){
            Ans++; X.push(i); Y.push(j); Vis[i][j]=1;
            while(!X.empty()){
                int x = X.front(), y = Y.front(); 
                X.pop(); Y.pop(); 
                for(int i=0; i<4; i++){
                    int nx = x+mv[i][0], ny = y+mv[i][1];
                    if(Board[nx][ny] && !Vis[nx][ny]){
                        X.push(nx); Y.push(ny); Vis[nx][ny]=Vis[x][y]+1;
                    }
                }
            }
        }
        
        printf("%d\n", Ans);
    }
    return 0;
}
