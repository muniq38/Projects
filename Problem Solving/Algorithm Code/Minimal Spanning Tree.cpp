
#include <bits/stdc++.h>
using namespace std;

vector<int> Root(15000); // Union-Find
struct Edge{ int a; int b; int X; };
vector<Edge> Graph;

int Find(int X){
    if(Root[X]==X) return X;
    return Root[X] = Find(Root[X]);
}

void Union(int X, int Y){
    int a = Find(X), b = Find(Y);
    if(a!=b) Root[a]=b;
}

bool Comp(Edge a, Edge b){ return (a.X < b.X); }

int main()
{
    int N, M; scanf("%d %d", &N, &M);
    Graph.resize(M+1);
    for(int i=1; i<=M; i++) scanf("%d %d %d", &Graph[i].a, &Graph[i].b, &Graph[i].X);
    sort(Graph.begin()+1, Graph.end(), Comp);
    
    int Ans=0, Count=0;
    for(int i=1; i<=N; i++) Root[i]=i;
    for(int i=1; Count!=N-1; i++) if(Find(Graph[i].a)!=Find(Graph[i].b)){
        Union(Graph[i].a, Graph[i].b);
        Ans += Graph[i].X; Count++;
    }printf("%d\n", Ans);
    return 0;
}