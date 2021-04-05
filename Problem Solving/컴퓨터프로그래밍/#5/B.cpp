
#include <bits/stdc++.h>
using namespace std;
int St[100000]={};

int main()
{
    int T=0, N, X;
    long long Ans=0; cin >> N;
    while(N--){
        cin >> X;
        while(T>0 && St[T-1]<=X){ T--; Ans+=T; }
        St[T]=X; T++;
    }while(T>0){ T--; Ans+=T; }
    printf("%lld\n", Ans);
    return 0;
}

