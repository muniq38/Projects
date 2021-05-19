
#include <bits/stdc++.h>
using namespace std;

int Ans(int N){
    if(N==3) return 0;
    if(N==4) return 1;
    if(N&1) return Ans(N+1);
    return Ans(N/2)+2;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Ans(N));
    return 0;
}
