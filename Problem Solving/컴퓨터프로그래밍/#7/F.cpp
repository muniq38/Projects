
#include <bits/stdc++.h>
#define INF 1000000007
using namespace std;
typedef long long lint;
int N, M;
vector<vector<pair<int,lint>>> Graph;

vector<lint> Dijkstra(int X){
    
    vector<lint> Dist(N+1,INF);
    priority_queue<pair<lint,int>> Heap; 
    Dist[X] = 0; Heap.push({0,X});
    
    while(!Heap.empty())
    {
        lint cost = -Heap.top().first; 
        int here = Heap.top().second; Heap.pop(); 
        if(Dist[here] < cost) continue;
        for(auto Y : Graph[here]) 
        {
            int there = Y.first;
            int nextDist = cost + Y.second; 
            if (Dist[there] > nextDist)
            {
                Dist[there] = nextDist;
                Heap.push({-nextDist, there});
            }
        }
    } return Dist;
}

int main()
{
    int a, b; lint X;
    scanf("%d %d", &N, &M);
    Graph.resize(N+1);
    
    for(int i=0; i<M; i++){
        scanf("%d %d %lld", &a, &b, &X);
        Graph[a].push_back({b,X});
        Graph[b].push_back({a,X});
    }
    
    lint Max=0; int Place, Count=0;
    vector<lint> Dist = Dijkstra(1);
    for(int i=1; i<=N; i++) if(Dist[i]==INF) Dist[i]=-1;
    for(int i=1; i<=N; i++) if(Dist[i]>Max) Max=Dist[i];
    for(int i=N; i>=1; i--) if(Dist[i]==Max){ Count++; Place=i; }
    printf("%d %d\n", Place, Count);
    return 0;
}
