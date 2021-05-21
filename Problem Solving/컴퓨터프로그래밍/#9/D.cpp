
#include <bits/stdc++.h>
#define INF 1000000007
using namespace std;
struct Edge{ int a; int b; int X; };
typedef pair<int,int> pint;
vector<vector<pint>> Graph;
vector<Edge> E;

vector<int> Dijkstra(int N, int K, int V){
    vector<priority_queue<pair<int,int>>> Dist(N+1);
    priority_queue<pair<int,int>> Heap;
    Dist[V].push({0,0}); Heap.push({0,V});
    while(!Heap.empty()){
        auto T = Heap.top(); Heap.pop();
        int pDist = -T.first, px = T.second;
        if(Dist[px].size()>K && pDist > Dist[px].top().first) continue;
        for(auto e : Graph[px]){
            priority_queue<pair<int,int>> Temp;
            while(!Dist[px].empty()){
                Temp.push(Dist[px].top());
                int nDist = Dist[px].top().first+e.second;
                int nx = e.first;   
                if(Dist[nx].empty() || (nDist < Dist[nx].top().first && Dist[px].top().second != nx)){
                    Dist[nx].push({nDist,px}); 
                    if(Dist[nx].size()>K) Dist[nx].pop();
                    Heap.push({-nDist,nx});
                }Dist[px].pop();
            }Dist[px]=Temp;
        }
    }
    
    vector<int> Ans;
    while(!Dist[N].empty()){
        Ans.push_back(Dist[N].top().first);
        Dist[N].pop();
    }return Ans;
}

int main()
{
    int N, M, K; scanf("%d %d %d", &N, &M, &K);
    for(int i=0; i<M; i++){
        int a, b, X;
        scanf("%d %d %d", &a, &b, &X);
        E.push_back({a,b,X});
    }
    
    vector<int> minDist;
    for(int i=0; i<M; i++){
        Graph = vector<vector<pint>>(N+1);
        for(int j=0; j<M; j++){
            Edge e = E[j];
            int a = e.a, b = e.b, X = e.X;
            if(j==i){ 
                Graph[a].push_back({b,X/2});
                Graph[b].push_back({a,X/2});
            }else{
                Graph[a].push_back({b,X});
                Graph[b].push_back({a,X});
            }
        }
        vector<int> Mins = Dijkstra(N,(K/3)+5,1);
        for(int j=0; j<Mins.size(); j++) minDist.push_back(Mins[j]);
    }
    
    sort(minDist.begin(), minDist.end());
    if(minDist.size()<K) printf("-1\n"); 
    else printf("%d\n", minDist[K-1]);
    return 0;
}
