
#include <bits/stdc++.h>
#define INF 1000000009
using namespace std;
vector<vector<pair<int,int>>> Graph;
vector<int> notPrime(100000);

void findPrime(){
    notPrime[1]=notPrime[0]=1;
    for(int i=2; i<100000; i++){
        if(notPrime[i]) continue;
        for(int j=2; i*j<100000; j++) notPrime[i*j]=1;
    }
}

vector<int> Dijkstra(int V, int N){
    vector<int> Dist(N+1,INF);
    priority_queue<pair<int,int>> Heap;
    Dist[V]=0; Heap.push({0,V});
    while(!Heap.empty()){
        auto T = Heap.top(); Heap.pop();
        int pDist = -T.first, px = T.second;
        if(pDist > Dist[px]) continue;
        for(auto e : Graph[px]){
            int nDist = e.second+Dist[px];
            int nx = e.first;
            if(nDist < Dist[nx]){ 
                Dist[nx]=nDist; Heap.push({-nDist,nx});
            }
        }
    }return Dist;
}

int main()
{
    findPrime();
    vector<int> X(5000), Y(5000); 
    Graph.resize(5000);
    int x, y, N;
    
    scanf("%d %d %d %d %d", &X[1], &Y[1], &X[2], &Y[2], &N);
    for(int i=1; i<=N; i++) scanf("%d %d", &X[i+2], &Y[i+2]);
    for(int i=1; i<=N+2; i++){
        for(int j=1; j<i; j++){
            int w = (int)sqrt(pow(X[i]-X[j],2)+pow(Y[i]-Y[j],2));
            if(!notPrime[w]){
                Graph[i].push_back({j,w});
                Graph[j].push_back({i,w});
            }
        }
    }
    
    vector<int> Dist = Dijkstra(1,N+2);
    printf("%d\n", Dist[2]==INF?-1:Dist[2]);
    return 0;
}
