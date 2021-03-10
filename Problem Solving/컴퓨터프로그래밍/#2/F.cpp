
#include <bits/stdc++.h>
using namespace std;
int DP[30][30]={};
int K;

int Step(int N, int n){ 
    if(DP[N][n]) return DP[N][n];
    if(!n) return 1; if(n<0) return 0;
    int Ans=0;
    for(int i=1; i<=3; i++){
        if(N+i==K) continue;
        Ans += Step(N+i, n-i);
    }DP[N][n] = Ans;
    return Ans;
}

int main()
{
    int N; scanf("%d %d", &N, &K);
    printf("%d\n", Step(0,N));
    return 0;
}



