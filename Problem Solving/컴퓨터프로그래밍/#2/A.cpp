
#include <bits/stdc++.h>
using namespace std;
int DP[30][10]={};

int Step(int N, int K){ // K는 못쓰고, N만큼 써야함
    if(N<0) return 0;
    if(!N) return 1;
    if(DP[N][K]) return DP[N][K];
    int Ans=0;
    for(int i=1; i<=3; i++){
        if(i==K) continue;
        Ans += Step(N-i,i);
    }DP[N][K] = Ans;
    return Ans;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Step(N,0));
    return 0;
}


