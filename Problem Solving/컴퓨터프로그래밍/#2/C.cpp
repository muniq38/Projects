
#include <bits/stdc++.h>
using namespace std;
int DP[30][5][5]={};

int Step(int N, int K, int St){ // K는 앞서 St번 쓰였고, N만큼 써야함
    if(DP[N][K][St]) return DP[N][K][St];
    if(!N) return 1; if(N<0) return 0;
    int Ans=0;
    for(int i=1; i<=2; i++){
        if(i==K && St==3) continue;
        if(i==K) Ans += Step(N-i,K,St+1);
        else Ans += Step(N-i,i,1);
    }DP[N][K][St] = Ans;
    return Ans;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Step(N,0,0));
    return 0;
}


