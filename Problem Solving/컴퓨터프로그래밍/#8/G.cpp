
#include <bits/stdc++.h>
using namespace std;
char Board[1100][100]={};
int Vis[1100][100]={};
int mv[4][2]={{1,0},{-1,0},{0,-1},{0,1}};

int main()
{
    int N, M; scanf("%d %d", &M, &N);
    for(int i=1; i<=N; i++)
    scanf("%s", Board[i]+1);
    
    vector<int> Ans;
    queue<int> X, Y;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++){
        if(!Vis[i][j] && Board[i][j]=='*'){
            X.push(i); Y.push(j); Vis[i][j]=1;
            int Count = 1;
            while(!X.empty()){
                int x = X.front(), y = Y.front();
                X.pop(); Y.pop();
                for(int k=0; k<4; k++){
                    int xn = mv[k][0]+x, yn = mv[k][1]+y;
                    if(!Vis[xn][yn] && Board[xn][yn]=='*'){
                        X.push(xn); Y.push(yn);
                        Vis[xn][yn]=1; Count++;
                    }
                }
            }
            Ans.push_back(Count);
        }
    }
    
    sort(Ans.begin(), Ans.end());
    printf("%d\n", Ans[Ans.size()-1]);
    return 0;
}


