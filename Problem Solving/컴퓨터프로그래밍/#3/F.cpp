
#include <bits/stdc++.h>
using namespace std;
int Stack[50]={}, idx=0;

void Print(int N, int K){
    if(!N){ for(int i=0; i<idx; i++) printf("%d ", Stack[i]); printf("\n"); return; }
    if(!K) return;
    if(N>=K){ Stack[idx++]=K; Print(N-K,K); idx--; }
    Print(N,K-1);
}

int main()
{
    int N; scanf("%d", &N);
    Print(N,N);
    return 0;
}
