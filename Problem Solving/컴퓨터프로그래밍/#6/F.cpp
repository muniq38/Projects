
#include <bits/stdc++.h>
using namespace std;
int mv[6]={1,-1,5,-5,10,-10};

int main()
{
    int Vis[100]={}; // Vis[0]=-20 : T대신 T+20, 
    int A, B; scanf("%d %d", &A, &B);
    int Q[500]={}, front=0, end=0; // front=end일때 비어있다
    Q[end++]=A+20; Vis[A+20]=1;
    while(front<end){
        int X = Q[front++]; 
        for(int i=0; i<6; i++){
            if(0<=X+mv[i] && X+mv[i]<100 && !Vis[X+mv[i]]){
                Q[end++]=X+mv[i]; Vis[X+mv[i]]=Vis[X]+1;
            }
        }
    }printf("%d\n", Vis[B+20]-1);
    return 0;
}
