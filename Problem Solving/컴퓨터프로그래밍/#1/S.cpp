
#include <bits/stdc++.h>
using namespace std;
long long Board[600][600]={};
long long Ans[600][600]={};

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    while(Q--){
        int a, b, c, d, w;
        scanf("%d %d %d %d %d", &a, &b, &c, &d, &w);
        Board[a][b] += w; Board[a][d+1] -= w;
        Board[c+1][b] -= w; Board[c+1][d+1] += w;
    }for(int i=1; i<=N; i++){
        Ans[i][1] = Board[i][1];
        for(int j=2; j<=N; j++) Ans[i][j] = Ans[i][j-1]+Board[i][j];
        for(int j=1; j<=N; j++){ Ans[i][j] += Ans[i-1][j];
        printf("%d ", Ans[i][j]); }
        printf("\n");
    }
    return 0;
}
