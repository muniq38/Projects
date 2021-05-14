
#include <bits/stdc++.h>
using namespace std;
int DP[300000][70]={};

int main()
{
    int N, Max=0; scanf("%d", &N);
    vector<int> Line(N+1);
    for(int i=1; i<=N; i++) scanf("%d", &Line[i]);
    for(int i=1; i<=N; i++){
        DP[i][Line[i]]=i;
        Max = max(Max, Line[i]);
        for(int j=Line[i]+1; j<65; j++){
            if(!DP[i][j-1]) break;
            if(!DP[DP[i][j-1]-1][j-1]) break;
            DP[i][j] = DP[DP[i][j-1]-1][j-1];
            Max = max(Max,j);
        }
    }printf("%d\n", Max);
    return 0;
}
