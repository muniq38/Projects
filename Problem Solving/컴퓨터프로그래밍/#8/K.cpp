
#include <bits/stdc++.h>
using namespace std;
int mv[4][2]={{0,-1},{0,1},{1,0},{-1,0}};

int main()
{
    int N, M, Board[150][150]={};
    scanf("%d %d", &N, &M);
    queue<int> X, Y; X.push(1); Y.push(1);
    queue<int> chX, chY; // 치즈저장
    
    for(int i=0; i<150; i++) for(int j=0; j<150; j++) Board[i][j]=-1;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){ 
        scanf("%d", &Board[i][j]); Board[1][1]=2;
    
    int VisNum=0; bool Fail=false;
    while(1){
        
        while(!X.empty()){ // 1. 바람불기 작업 (공기채우기)
            int x = X.front(), y = Y.front(); X.pop(); Y.pop();
            for(int k=0; k<4; k++){
                int nx = x+mv[k][0], ny = y+mv[k][1];
                if(Board[nx][ny]==0){ X.push(nx); Y.push(ny); Board[nx][ny]=2; }  
            }
        }
        
        for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if(Board[i][j]==1){ // 2. 치즈체크 작업
            int contam = 0;
            for(int k=0; k<4; k++){
                int nx = i+mv[k][0], ny = j+mv[k][1];
                if(Board[nx][ny]==2) contam++;
            }if(contam>=2){ X.push(i); Y.push(j); Board[i][j]=3; }
        }
        
        for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) 
        if(Board[i][j]==3) Board[i][j]=2;
        if(!X.empty()) VisNum++; else break; // 3. 종결조건

    }printf("%d\n", VisNum);
    return 0;
}
