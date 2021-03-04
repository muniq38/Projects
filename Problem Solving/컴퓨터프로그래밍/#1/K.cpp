
#include <bits/stdc++.h>
using namespace std;
vector<int> Vis(2000000);

void BFS(int N){
    queue<int> Q;
    Q.push(N); Vis[N]=1;
    int K,T;
    while(!Q.empty()){
        T = Q.front(); Q.pop();
        for(int i=0; i<=17; i++){
            K = T^(7<<i);
            if(!Vis[K]){ Q.push(K); Vis[K]=Vis[T]+1; }
        }K = T^3;
        if(!Vis[K]){ Q.push(K); Vis[K]=Vis[T]+1; }
        K = T^(3<<18);
        if(!Vis[K]){ Q.push(K); Vis[K]=Vis[T]+1; }
    }
}

int main()
{
    int N=0, a;
    for(int i=0; i<20; i++){
        scanf("%d", &a);
        N*=2; N+=a;
    }BFS(N);
    printf("%d\n", Vis[0]-1);
    return 0;
}
