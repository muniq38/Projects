
#include <bits/stdc++.h>
#define INF 123456789
using namespace std;

int main()
{
    int N, VisCount=1; scanf("%d\n", &N);
    vector<vector<int>> Graph(N+1);
    queue<int> Q; char X[1100]={};
    int Vis[1100]={};
    
    for(int i=1; i<=N; i++){
        scanf("%s", X+1);
        for(int j=1; i>j; j++) if(X[j]=='1'){ 
            Graph[i].push_back(j); 
            Graph[j].push_back(i); 
        }
    }
    
    for(int i=1; i<=N; i++){
        if(Vis[i]) continue;
        Q.push(i); Vis[i]=VisCount;
        while(!Q.empty()){
            int X = Q.front(); Q.pop();
            for(int Y : Graph[X]) if(!Vis[Y]){
                Q.push(Y); Vis[Y]=Vis[X];
            }
        }
        VisCount++;
    }
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++) 
        printf("%d ", i!=j && Vis[i]==Vis[j] && Vis[i]);
        printf("\n");
    }return 0;
}


