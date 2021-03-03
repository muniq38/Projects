
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
vector<int> Vis;
queue<int> Q;
int N, M;

int BFS(int k){ // 양방향 BFS
    Vis = vector<int>(N+1);
    Vis[k]=1; Q.push(k); int Count=1;
    while(!Q.empty()){
        int T = Q.front(); Q.pop();
        for(int i=1; i<=N; i++) if(!Vis[i] && Graph[i][T]){
            Vis[i]=1; Q.push(i); Count++;
        }
    }Q.push(k); // 간선을 반대방향으로 바꾸면 갈 수 있었던 점은 방문 못하므로 Vis 유지해도 됨
    while(!Q.empty()){
        int T = Q.front(); Q.pop(); 
        for(int i=1; i<=N; i++) if(!Vis[i] && Graph[T][i]){
            Vis[i]=1; Q.push(i); Count++;
        }
    }return Count;
}

int main()
{
    int i, j, Ans=0;
    scanf("%d %d", &N, &M);
    Graph.resize(N+1);
    for(i=1; i<=N; i++) Graph[i].resize(N+1);
    for(i=0; i<M; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        Graph[a][b]=1;
    }for(i=1; i<=N; i++) if(BFS(i)==N) Ans++;
    printf("%d\n", Ans);
    return 0;
}
