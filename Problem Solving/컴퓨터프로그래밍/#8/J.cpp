
#include <bits/stdc++.h>
using namespace std;
#define INF 123456789
struct Cord{ int x,y; };

double getDist(Cord a, Cord b){
    double dx = (double)a.x-b.x;
    double dy = (double)a.y-b.y;
    return sqrt(pow(dx,2)+pow(dy,2));
}

int main(){

    int N; scanf("%d", &N);
    Cord V[160]={}; char Graph[160][160]={};
    double Dist[160][160]={}, Mm[160]={};
    
    for(int i=1; i<=N; i++) scanf("%d %d", &V[i].x, &V[i].y);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) 
    Dist[i][j]=(i==j)?0:INF;
    
    for(int i=1; i<=N; i++) scanf("%s", Graph[i]+1);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) 
    if(Graph[i][j]=='1') Dist[i][j]=getDist(V[i],V[j]);
    
    for(int k=1; k<=N; k++) for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
    Dist[i][j]=min(Dist[i][j],Dist[i][k]+Dist[k][j]); // 최단경로 구하기
                
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
    if(Dist[i][j]!=INF) Mm[i]=max(Mm[i],Dist[i][j]);
    
    double Ans=INF, pMax=0;
    for(int i=1; i<=N; i++) pMax=max(pMax,Mm[i]); 
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
    if(Dist[i][j]==INF) Ans=min(Ans, Mm[i]+Mm[j]+getDist(V[i],V[j]));
    Ans=max(pMax,Ans);
    
    printf("%8lf\n", Ans);
    return 0;
}
