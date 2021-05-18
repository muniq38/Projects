
#include <bits/stdc++.h>
#define MOD 9901
using namespace std;
int DP[300][200]={};

int Tree(int N, int K){ // N개, 높이는 K 이하
    if(K==0) return 0;
    if(N==1) return 1;
    if(DP[N][K]!=-1) return DP[N][K];
    int Ans=0; 
    for(int i=1; i<N-1; i++) // 무조건 양갈래가 따여야 함
    Ans = ( Ans + Tree(N-1-i,K-1)*Tree(i,K-1) )%MOD; 
    return DP[N][K]=Ans;
}

int main()
{
    int N, K; scanf("%d %d", &N, &K);
    for(int i=0; i<300; i++) for(int j=0; j<200; j++) DP[i][j]=-1;
    printf("%d\n", (Tree(N,K)-Tree(N,K-1)+MOD)%MOD);
    return 0;
}

