
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
vector<int> Vis;

int main()
{
    int P, M, X;
    scanf("%d %d %d", &P, &M, &X);
    Graph.resize(P+1);
    Vis.resize(P+1);
    
    for(int i=1; i<=M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Graph[a].push_back(b); Graph[b].push_back(a);
        Graph[b].push_back(c); Graph[c].push_back(b);
        Graph[c].push_back(a); Graph[a].push_back(c);
    }
    
    queue<int> Q;
    stack<int> Print;
    Q.push(1); Vis[1]=1;
    while(!Q.empty()){
        int T = Q.front(); Q.pop();
        for(auto Y: Graph[T]) if(!Vis[Y]){
            Vis[Y]=Vis[T]+1; Q.push(Y);
        }
    }printf("%d\n", Vis[X]);
    
    int Cur = X;
    while(Vis[Cur]>1){
        Print.push(Cur);
        for(auto Y: Graph[Cur]) if(Vis[Y]==Vis[Cur]-1){
            Cur = Y; break;
        }
    }printf("1\n");
    while(!Print.empty()){ printf("%d\n", Print.top()); Print.pop(); }
    return 0;
}
