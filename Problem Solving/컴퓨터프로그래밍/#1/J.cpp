
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N; scanf("%d", &N);
    long long Ans=0;
    for(int i=(N+2)/3; i<(N+1)/2; i++){
        Ans += 1+(3*i-N)/2;
    }printf("%lld\n", Ans);
    return 0;
}
