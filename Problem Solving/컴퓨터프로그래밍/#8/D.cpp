
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
int Vis[2500]={}, N, M;

int main()
{
    scanf("%d %d", &N, &M);
    Graph.resize(N+1);
    for(int i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }
    
    queue<int> Q;
    Q.push(1); Vis[1]=1;
    
    while(!Q.empty()){
        int X = Q.front(); Q.pop();
        printf("%d ", X); 
        for(auto Y : Graph[X]) if(!Vis[Y])
        { Q.push(Y); Vis[Y]=1; }
    }return 0;
}
