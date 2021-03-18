
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int Comb(int N, int M){ // 길이 N에 M개 넣어야 함
    if(!M) return 1;
    if(!N) return 0;
    if(N<2*M-1) return 0;
    return Comb(N-2,M-1)+Comb(N-1,M);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    printf("%d\n", Comb(N-1,M)+Comb(N-3,M-1));
    return 0;
}
