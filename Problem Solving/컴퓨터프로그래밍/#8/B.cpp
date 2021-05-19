
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
int Vis[2500]={}, N, M;

void DFS(int X){
    Vis[X]=1; printf("%d ", X);
    for(auto Y : Graph[X]) if(!Vis[Y]) DFS(Y);
}

int main()
{
    scanf("%d %d", &N, &M);
    Graph.resize(N+1);
    for(int i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }DFS(1);
    return 0;
}
