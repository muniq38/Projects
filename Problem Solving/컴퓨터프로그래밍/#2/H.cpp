
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint DP[40][40]={};

lint Comb(int a, int b){
    if(a==1) return 1;
    if(!b || a==b) return 1;
    if(DP[a][b]) return DP[a][b];
    return Comb(a-1,b-1)+Comb(a-1,b);
}


int main()
{
    int N, K;
    scanf("%d %d", &N, &K);
    printf("%lld\n", Comb(N,K));
    return 0;
}
