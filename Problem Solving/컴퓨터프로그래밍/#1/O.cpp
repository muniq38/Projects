
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pint;
int Vis[1500][1500];

int main()
{
    int N, M, x, y;
    scanf("%d %d %d %d", &N, &M, &x, &y);
    queue<pint> Q;
    Q.push({x,y}); Vis[x][y]=1;
    while(!Q.empty()){
        pint T = Q.front(); Q.pop();
        x = T.first; y = T.second;
        if(x+1<=N && y+2<=M && !Vis[x+1][y+2]){
            Vis[x+1][y+2]=Vis[x][y]+1; Q.push({x+1,y+2});
        }if(x+1<=N && y-2>=1 && !Vis[x+1][y-2]){
            Vis[x+1][y-2]=Vis[x][y]+1; Q.push({x+1,y-2});
        }if(x+2<=N && y+1<=M && !Vis[x+2][y+1]){
            Vis[x+2][y+1]=Vis[x][y]+1; Q.push({x+2,y+1});
        }if(x+2<=N && y-1>=1 && !Vis[x+2][y-1]){
            Vis[x+2][y-1]=Vis[x][y]+1; Q.push({x+2,y-1});
        }if(x-1>=1 && y-2>=1 && !Vis[x-1][y-2]){
            Vis[x-1][y-2]=Vis[x][y]+1; Q.push({x-1,y-2});
        }if(x-1>=1 && y+2<=M && !Vis[x-1][y+2]){
            Vis[x-1][y+2]=Vis[x][y]+1; Q.push({x-1,y+2});
        }if(x-2>=1 && y-1>=1 && !Vis[x-2][y-1]){
            Vis[x-2][y-1]=Vis[x][y]+1; Q.push({x-2,y-1});
        }if(x-2>=1 && y+1<=M && !Vis[x-2][y+1]){
            Vis[x-2][y+1]=Vis[x][y]+1; Q.push({x-2,y+1});
        }
    }for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++) printf("%d ", Vis[i][j]-1);
        printf("\n");
    }
    return 0;
}
