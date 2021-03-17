
#include <bits/stdc++.h>
int K;

void Print(int N){
    if(N<K){ printf("%X", N); return; } 
    int i=N%K, j=N/K;
    Print(j); Print(i);
}

int main()
{
    int N; scanf("%d %d", &N, &K);
    Print(N);
    return 0;
}
