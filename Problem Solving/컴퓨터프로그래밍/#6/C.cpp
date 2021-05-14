
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long lint;
typedef pair<int,int> pint;

int main()
{
    int N, M, K, X, Y; 
    scanf("%d %d %d", &N, &M, &K);
    int Vis[1100][1100];
    queue<pint> Q;
    
    for(int i=0; i<K; i++){
        scanf("%d %d", &X, &Y);
        Q.push({X,Y}); Vis[X][Y]=1;
    }
    
    while(!Q.empty()){
        pint F = Q.front(); Q.pop();
        int X = F.first, Y = F.second;
        if(X<N && !Vis[X+1][Y]){ Q.push({X+1,Y}); Vis[X+1][Y]=Vis[X][Y]+1; }
        if(X>1 && !Vis[X-1][Y]){ Q.push({X-1,Y}); Vis[X-1][Y]=Vis[X][Y]+1; }
        if(Y>1 && !Vis[X][Y-1]){ Q.push({X,Y-1}); Vis[X][Y-1]=Vis[X][Y]+1; }
        if(Y<M && !Vis[X][Y+1]){ Q.push({X,Y+1}); Vis[X][Y+1]=Vis[X][Y]+1; }
    }
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) printf("%d ",  Vis[i][j]);
        printf("\n");
    }return 0;
}
