
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<vector<int>> Graph(N+1);
    vector<int> Vis(N+1);
    for(int i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }
    
    for(int i=1; i<=N; i++) sort(Graph[i].begin(), Graph[i].end());
    queue<int> Q; Q.push(1); Vis[1]=1; printf("1 ");
    while(!Q.empty()){
        int T = Q.front(); Q.pop(); 
        for(int Y : Graph[T]) if(!Vis[Y]){
            Vis[Y]=1; Q.push(Y); printf("%d ", Y);
        }
    }

    return 0;
}
