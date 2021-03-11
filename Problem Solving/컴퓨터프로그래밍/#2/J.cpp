
#include <bits/stdc++.h>
using namespace std;
int Mem[20][20]={};

int DP(int A, int B){ // 1행에 A개 2행에 B개 
    if(A<B) swap(A,B);
    if(A<0 || B<0) return 0;
    if(!A && !B) return 1;
    if(Mem[A][B]) return Mem[A][B];
    if(A==B) Mem[A][B]+=DP(A-1,B-1);
    Mem[A][B] += DP(A-3, B)+DP(A-2, B)+DP(A-1, B);
    return Mem[A][B];
}

int main()
{
    int N; scanf("%d", &N); 
    printf("%d\n", DP(N,N));
    return 0;
}
