
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int mv[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

int main()
{
    int N, M, K, X, Y, Z, Count=0; 
    scanf("%d %d %d", &N, &M, &K);
    int Vis[110][110][110]={};
    queue<int> A, B, C;
    
    for(int i=0; i<M; i++){
        scanf("%d %d %d", &X, &Y, &Z);
        A.push(X); B.push(Y); C.push(Z); 
        Vis[X][Y][Z]=1;
    }
    
    while(!A.empty()){
        X = A.front(); Y = B.front(); Z = C.front();
        A.pop(); B.pop(); C.pop();
        for(int i=0; i<6; i++){
            int x = X+mv[i][0], y = Y+mv[i][1], z = Z+mv[i][2];
            if(1<=x && x<=N && 1<=y && y<=N && 1<=z && z<=N && !Vis[x][y][z]){
                A.push(x); B.push(y); C.push(z); Vis[x][y][z]=Vis[X][Y][Z]+1;
            }
        }
    }
    
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) for(int k=1; k<=N; k++) 
    if(Vis[i][j][k]<=K) Count++;
    printf("%d\n", Count);
    return 0;
}
