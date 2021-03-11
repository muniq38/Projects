
#include <bits/stdc++.h>
using namespace std;
int Mem[30][30]={};

int DP(int M, int N){ // M이 사람 수 N이 좌석 수
    if(N<0 || M<0 || M>N) return 0;
    if(!M) return 1;
    if(N==1 && M==1) return 1;
    if(N==2 && M==2) return 1;
    if(Mem[M][N]) return Mem[M][N];
    Mem[M][N] = DP(M-2, N-3)+DP(M-1, N-2)+DP(M,N-1); // 1 1 0, or 1 0, 0
    return Mem[M][N];
}

int main()
{
    int M, N;
    scanf("%d %d", &N, &M);
    printf("%d\n", DP(M,N)); 
    return 0;
}
