
#include <bits/stdc++.h>
using namespace std;

int inv(int N, int K){
    if(N<10) return 10*K+N; 
    int i=N%10, j=N/10; 
    return inv(j,10*K+i);
}

int main()
{
    int N, i=0; scanf("%d", &N);
    while(N!=inv(N,0)){ N += inv(N,0); i++; }
    printf("%d %d\n", i, N);
    return 0;
}
