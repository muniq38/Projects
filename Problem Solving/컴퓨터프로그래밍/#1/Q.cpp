
#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;
int Graph[50][50]={};

int main(){
    int N, M, i, j, k, e, Min=INF;
    vector<int> Edges[3];
    scanf("%d %d", &N, &M);
    for(i=1; i<=N; i++) for(j=1; j<=N; j++) if(i!=j) Graph[i][j]=INF;
    for(i=1; i<=M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Graph[a][b] = min(Graph[a][b], c);
        Graph[b][a] = min(Graph[b][a], c);
    }
    
    for(i=1; i<=N; i++) for(j=1; j<i; j++) if(Graph[i][j]!=INF)
    { Edges[0].push_back(i); Edges[1].push_back(j); Edges[2].push_back(Graph[i][j]); } // 저장용
    
    for(e=1; e<=M; e++){
        for(i=1; i<=N; i++) for(j=1; j<=N; j++) if(i!=j) Graph[i][j]=INF;
        for(i=1; i<=M; i++){ 
            Graph[Edges[0][i]][Edges[1][i]] = Edges[2][i]; 
            Graph[Edges[1][i]][Edges[0][i]] = Edges[2][i]; 
        }Graph[Edges[0][e]][Edges[1][e]] = Edges[2][e]/2;
        Graph[Edges[1][e]][Edges[0][e]] = Edges[2][e]/2;
        for(k=1; k<=N; k++) for(i=1; i<=N; i++) for(j=1; j<=N; j++)
        if(Graph[i][k]+Graph[k][j]<Graph[i][j]) Graph[i][j]=Graph[i][k]+Graph[k][j];
        if(Min>Graph[1][N]) Min=Graph[1][N];
    }printf("%d\n", Min);
}