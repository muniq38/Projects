#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Graph;
vector<int> Vis;
vector<int> Ocp;
int VisCount=0;

bool DFS(int X){ // X가 새로운 매칭을 만들어 낼 수 있다.
    if(Vis[X]==VisCount) return false;
    Vis[X]=VisCount;
    for(int j=0; j<Graph[X].size(); j++){
        int Y = Graph[X][j]; // X랑 매칭이 가능할 지도 모르는 Y
        if(!Ocp[Y] || DFS(Ocp[Y])){ Ocp[Y]=X; return true; }
    }return false;
}

int main()
{
    int N, M, i, j, a=1, b=1, Ans=0;
    scanf("%d %d\n", &N, &M);
    char Board[N+3][M+3], F; int A[N][M];
    for(i=0; i<N; i++){
        for(j=0; j<M; j++) scanf("%c", &Board[i][j]);
        scanf("%c", &F);
    }for(i=0; i<N; i++) for(j=0; j<=M; j++){
        if(Board[i][j]!='*') a++; else A[i][j]=a;
    }Graph.resize(a+1); Vis.resize(a+1);
    for(i=0; i<M; i++) for(j=0; j<=N; j++){
        if(Board[j][i]!='*') b++; 
        else Graph[A[j][i]].push_back(b); 
    }Ocp.resize(b+1);
    for(i=1; i<Graph.size(); i++){
        VisCount++; 
        if(DFS(i)) Ans++;
    }printf("%d\n", Ans);
    return 0;
}
