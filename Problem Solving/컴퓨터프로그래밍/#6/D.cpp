
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long lint;
typedef pair<int,int> pint;

int main()
{
    int N, M, X, Y; 
    scanf("%d %d", &N, &M);
    int Vis[1100][1100];
    queue<pint> Q;
    
    scanf("%d %d", &X, &Y);
    Q.push({X,Y}); Vis[X][Y]=1;
    
    while(!Q.empty()){
        pint F = Q.front(); Q.pop();
        int X = F.first, Y = F.second;
        if(X+1<N && Y<M && !Vis[X+2][Y+1]){ Q.push({X+2,Y+1}); Vis[X+2][Y+1]=Vis[X][Y]+1; }
        if(X+1<N && Y>1 && !Vis[X+2][Y-1]){ Q.push({X+2,Y-1}); Vis[X+2][Y-1]=Vis[X][Y]+1; }
        if(X>2 && Y<M && !Vis[X-2][Y+1]){ Q.push({X-2,Y+1}); Vis[X-2][Y+1]=Vis[X][Y]+1; }
        if(X>2 && Y>1 && !Vis[X-2][Y-1]){ Q.push({X-2,Y-1}); Vis[X-2][Y-1]=Vis[X][Y]+1; }
        if(X<N && Y+1<M && !Vis[X+1][Y+2]){ Q.push({X+1,Y+2}); Vis[X+1][Y+2]=Vis[X][Y]+1; }
        if(X<N && Y>2 && !Vis[X+1][Y-2]){ Q.push({X+1,Y-2}); Vis[X+1][Y-2]=Vis[X][Y]+1; }
        if(X>1 && Y+1<M && !Vis[X-1][Y+2]){ Q.push({X-1,Y+2}); Vis[X-1][Y+2]=Vis[X][Y]+1; }
        if(X>1 && Y>2 && !Vis[X-1][Y-2]){ Q.push({X-1,Y-2}); Vis[X-1][Y-2]=Vis[X][Y]+1; }
    }
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) printf("%d ",  Vis[i][j]-1);
        printf("\n");
    }return 0;
}
