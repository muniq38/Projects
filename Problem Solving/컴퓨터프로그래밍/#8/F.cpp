
#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;

int main()
{
    int N, M, Dist[20][20]={}, Mem[20][20]={}, Vis[20][20]={};
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) Dist[i][j]=INF;
    for(int i=0; i<M; i++){
        int a, b, X;
        scanf("%d %d %d", &a, &b, &X);
        Dist[a][b] = Dist[b][a] = min(Dist[a][b],X);
    }
    
    int Min=INF;
    while(M--){
        
        int Visited=0;
        for(int i=1; i<=N; i++) for(int j=1; j<=i; j++){
            Mem[i][j] = Mem[j][i] = Dist[i][j]; 
            if(!Vis[i][j] && !Visited && Dist[i][j]<1000){
                Mem[i][j] = Mem[j][i] = Dist[i][j]/2; 
                Visited=1; Vis[i][j]=1; Vis[j][i]=1;
            }
        }
        
        for(int m=1; m<=N; m++) for(int s=1; s<=N; s++) for(int e=1; e<=N; e++)
        Mem[s][e] = min(Mem[s][e], Mem[s][m]+Mem[m][e]);
        Min = min(Min,Mem[1][N]);
        
    }
    printf("%d\n", (Min<1000000)?Min:-1);
    return 0;
}
