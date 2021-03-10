
#include <bits/stdc++.h>
using namespace std;
int DP[30][30][2]={};
int Prime[30]={};

int Step(int N, int n, int K){ // 소수 쓸수 있는지 여부(K) n만큼 써야함
    if(DP[N][n][K]) return DP[N][n][K];
    if(!n) return !K; if(n<0) return 0;
    int Ans=0;
    for(int i=1; i<=3; i++){
        if(Prime[N+i] && !K) continue;
        if(Prime[N+i]) Ans += Step(N+i, n-i, 0);
        else Ans += Step(N+i, n-i, K);
    }DP[N][n][K] = Ans;
    return Ans;
}

int main()
{
    int N; scanf("%d", &N);
    for(int i=1; i<=25; i++){
        Prime[2]=1; Prime[3]=1; Prime[5]=1; Prime[7]=1; Prime[11]=1;
        Prime[13]=1; Prime[17]=1; Prime[19]=1; Prime[23]=1;
    }printf("%d\n", Step(0,N,1));
    return 0;
}


