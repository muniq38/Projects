 
#include <bits/stdc++.h>
using namespace std;
int N, DP[20][20]={};

int Step(int n, int K){ // 정확히 K번으로 n에 도달할 경우의 수
    if(n<0) return 0; 
    if(!K && n) return 0;
    if(!n && K) return 0; 
    if(!n && !K) return 1; 
    if(DP[n][K]) return DP[n][K];
    int Ans=0;
    for(int i=1; i<=2; i++) Ans += Step(n-i, K-1);
    DP[n][K] = Ans;
    return Ans;
}

int main()
{
    scanf("%d", &N);
    int Ans=0;
    for(int i=1; i<=N; i++) Ans += Step(N,i)*Step(N,i);
    printf("%d\n", Ans);
    return 0;
}




