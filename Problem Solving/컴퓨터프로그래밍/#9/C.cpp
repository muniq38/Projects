
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
int Prime[21]={0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0};

lint Stair(int N, int K, int Total){
    if(N==Total) return (!K);
    if(N>Total) return 0;
    lint Ans=0;
    if(Prime[N+1]){ Ans += K?Stair(N+1, 0, Total):0;}
    else Ans += Stair(N+1,K,Total);
    if(Prime[N+2]){ Ans += K?Stair(N+2, 0, Total):0;}
    else Ans += Stair(N+2,K,Total);
    if(Prime[N+3]){ Ans += K?Stair(N+3, 0, Total):0;}
    else Ans += Stair(N+3,K,Total);
    return Ans;
}

int main()
{
    int N; scanf("%d", &N);
    lint Ans=0;
    for(int i=1; i<=N; i++) Ans += Stair(0,1,i);
    printf("%lld\n", Ans);
    return 0;
}
