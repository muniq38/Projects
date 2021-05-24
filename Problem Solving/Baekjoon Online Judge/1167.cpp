
#include <bits/stdc++.h>
using namespace std;
struct Edge{ int node; int w; };
vector<vector<Edge>> Graph;
vector<int> Diam;
vector<int> Vis;

int DFS(int X){
    Vis[X]=1; vector<int> Line(2);
    for(auto E : Graph[X]) if(!Vis[E.node])
    Line.push_back(DFS(E.node)+E.w);
    
    sort(Line.begin(), Line.end(), greater<int>());
    Diam[X]=Line[0]+Line[1];
    return Line[0];
}

int main()
{
    int N; scanf("%d", &N); Diam.resize(N+1); 
    Graph.resize(N+1); Vis.resize(N+1);
    
    for(int i=1; i<=N; i++){
        int a; scanf("%d", &a);
        while(1){
            int b, X; scanf("%d", &b);
            if(b==-1) break;
            scanf("%d", &X);
            Graph[a].push_back({b,X});
        }
    }
    
    DFS(1); int Ans=0; 
    for(int i=1; i<=N; i++) Ans = max(Ans, Diam[i]);
    printf("%d\n", Ans);
    return 0;
}
