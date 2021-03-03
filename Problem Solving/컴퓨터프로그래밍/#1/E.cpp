
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // 1이면 1, 2이면 2-1=1, 3이면 3-2-1=0, 4이면 4+3-2-1=4, ...
    int N, i, Ans=0;
    scanf("%d", &N);
    if(N%4==1 || N%4==2) i=2; else i=1;
    for(i; i<=N; i+=2) Ans += i;
    printf("%d", Ans);
    return 0;
}
