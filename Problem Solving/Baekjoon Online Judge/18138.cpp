
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
vector<int> Vis, Mate;
int VisCount=0;

int DFS(int X){
    if(Vis[X]==VisCount) return 0;
    Vis[X]=VisCount;
    for(auto Y: Graph[X]) if(!Mate[Y] || DFS(Mate[Y])){
        Mate[Y]=X; return 1;
    }return 0;
}

int main()
{
    int N, M, T, i, j, X, Ans=0;
    scanf("%d %d", &N, &M);
    vector<int> A(N+1), B(M+1);
    Mate.resize(M+1); Vis.resize(N+1);
    Graph.resize(N+1);
    
    for(int i=1; i<=N; i++) scanf("%d", &A[i]);
    for(int i=1; i<=M; i++) scanf("%d", &B[i]);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if((2*A[i]<=B[j]*4 && B[j]*4<=3*A[i]) || (A[i]<=B[j] && B[j]*4<=5*A[i])) 
        Graph[i].push_back(j);
    }
    
    for(i=1; i<=N; i++){
        VisCount++;
        if(DFS(i)) Ans++;
    }printf("%d\n", Ans);
    return 0;
}


