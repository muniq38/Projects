
#include <bits/stdc++.h>
int zero=0;

void inv(int N){
    if(!N && !zero) return;
    if(N<10){ printf("%d",N); zero=1; return; }
    int i=N%10, j=N/10;
    inv(i); inv(j);
}

int main()
{
    int N; scanf("%d", &N);
    inv(N);
    return 0;
}
