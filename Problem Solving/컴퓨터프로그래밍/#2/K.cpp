
#include <bits/stdc++.h>
using namespace std;
int Mem[20][20][20]={};

int DP(int A, int B, int C){ // 1행에 A개 2행에 B개 
    if(A<B) swap(A,B); if(A<C) swap(A,C);
    if(A<0 || B<0 || C<0) return 0;
    if(!A && !B && !C) return 1;
    if(Mem[A][B][C]) return Mem[A][B][C];
    if(A==B && B==C) Mem[A][B][C] += DP(A-1, B-1, C-1);
    Mem[A][B][C] += DP(A-1,B,C)+DP(A-3,B,C);
    return Mem[A][B][C];
}

int main()
{
    int N; scanf("%d", &N); 
    printf("%d\n", DP(N,N,N));
    return 0;
}
