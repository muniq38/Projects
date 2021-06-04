
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph, revGraph;
vector<int> Vis;

int DFS(int X, vector<vector<int>>& G){
    if(Vis[X]) return 0; Vis[X]=1;
    int Ans=1;
    for(int Y : G[X]) 
    if(!Vis[Y]) Ans += DFS(Y,G);
    return Ans;
}

int main()
{
    int N, M; scanf("%d %d", &N, &M);
    Graph.resize(N+1); revGraph.resize(N+1);
    for(int i=0; i<M; i++){
        int a, b; scanf("%d %d", &a, &b);
        Graph[a].push_back(b);
        revGraph[b].push_back(a);
    }
    
    int Ans=0;    
    for(int i=1; i<=N; i++){
        int Check=0;
        Vis = vector<int>(N+1);
        Check += DFS(i,Graph);
        Vis = vector<int>(N+1);
        Check += DFS(i,revGraph);
        if(Check==N+1) Ans++;
    }
    
    printf("%d\n", Ans);
    return 0;
}
