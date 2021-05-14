#include <bits/stdc++.h>
using namespace std;
char Board[1100][1100]={}; 
int Count[1100][1100]={}, Vis[1100][1100]={};
int mv[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{0,-1},{1,1},{1,0},{1,-1}};

int main()
{
    int N, M, VisCount=0; char ping; 
    scanf("%d %d\n", &N, &M);
    queue<int> X, Y;
    for(int i=1; i<=N; i++) scanf("%s", Board[i]+1);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if(Board[i][j]=='.'){
            X.push(i); Y.push(j); 
            Vis[i][j]=VisCount+1;   
        }
    }
    
    while(!X.empty()){
        VisCount++; 
        while(!X.empty() && Vis[X.front()][Y.front()]==VisCount){
            int x = X.front(), y = Y.front(); 
            X.pop(); Y.pop();
            for(int i=0; i<8; i++){
                int xn = x+mv[i][0], yn = y+mv[i][1]; 
                Count[xn][yn]++;
                if('0'<=Board[xn][yn] && Board[xn][yn]<='9')
                if(!Vis[xn][yn] && Count[xn][yn] >= Board[xn][yn]-'0'){
                    X.push(xn); Y.push(yn);
                    Board[xn][yn]='.'; Vis[xn][yn]=VisCount+1;
                } 
            }
        } 
    }
    
    printf("%d\n", VisCount-1);
    return 0;
}



