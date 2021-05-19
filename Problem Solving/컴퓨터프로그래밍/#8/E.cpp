
#include <bits/stdc++.h>
#define INF 1000000009
using namespace std;

int main()
{
    int N, M, Dist[15][15]={};
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) Dist[i][j]=INF;
    for(int i=0; i<M; i++){
        int a, b, X;
        scanf("%d %d %d", &a, &b, &X);
        Dist[a][b]=X; Dist[b][a]=X;
    }
    
    for(int m=1; m<=N; m++) for(int s=1; s<=N; s++) for(int e=1; e<=N; e++)
    Dist[s][e] = min(Dist[s][e], Dist[s][m]+Dist[m][e]);
    printf("%d\n", (Dist[1][N]<INF)?Dist[1][N]:-1);
    
    return 0;
}
