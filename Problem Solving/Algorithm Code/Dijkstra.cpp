
#include <bits/stdc++.h>
#define INF 1000000007
using namespace std;
typedef long long lint;
int N, M;
vector<vector<pair<int,lint>>> Graph;

vector<lint> Dijkstra(int V){ 
    
    vector<lint> Dist(N+1,INF);
    priority_queue<pair<lint,int>> Heap; 
    Dist[V] = 0; Heap.push({0,V});
    
    while(!Heap.empty()) // dist[x] : Dist[x]의 후보군
    {
        lint pDist = -Heap.top().first;  // pDist = min(inheap(dist[])) (더 좋은 dist[]는 나오지 않는다)
        int x = Heap.top().second; Heap.pop(); // pDist = one of dist[x]  
        if(Dist[x] < pDist) continue; // Dist[x] = min(dist[x]) = pDist이면 Dist[x] 확정 
        for(auto edge : Graph[x])  
        {
            int nx = edge.first;
            lint nDist = pDist + edge.second; // Dist[x] + (x-nx) => try dist[nx]
            if (Dist[nx] > nDist)
            {
                Dist[nx] = nDist; // dist[nx]생김, 정의에 의해 Dist[nx]에 min(dist[nx]) 저장
                Heap.push({-nDist, nx});
            }
        }
    } return Dist;
    
}
