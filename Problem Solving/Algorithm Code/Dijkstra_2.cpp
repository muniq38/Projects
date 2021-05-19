
#include <bits/stdc++.h>
#define INF 1000000009
using namespace std;
vector<vector<pair<int,int>>> Graph;

vector<int> Dijkstra(int V, int N){
    vector<int> Dist(N+1,INF);
    priority_queue<pair<int,int>> Heap;
    Dist[V]=0; Heap.push({0,V});
    
    while(!Heap.empty()){
        auto T = Heap.top(); Heap.pop();
        int pDist = -T.first, px = T.second; // px pDist
        if(pDist > Dist[px]) continue; // only pass when pDist=Dist[px]
        for(auto Edge : Graph[px]){
            int nx = Edge.first, nDist = Dist[px]+Edge.second; // nx nDist
            if(nDist < Dist[nx]){ Dist[nx]=nDist; Heap.push({-nDist,nx}); } // Update+push
        }
    }return Dist;
}

