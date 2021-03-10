
#include <bits/stdc++.h>
using namespace std;
int DP[30]={};

int Step(int N){ // N만큼 써야함
    if(DP[N]) return DP[N];
    if(!N) return 1; if(N<0) return 0;
    DP[N] = Step(N-1)+Step(N-2)+Step(N-3);
    return DP[N];
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Step(N));
    return 0;
}


