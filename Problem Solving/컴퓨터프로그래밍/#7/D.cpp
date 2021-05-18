
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint DP[100]={};

lint Tree(int N){
    if(N<=1) return 1;
    if(DP[N]) return DP[N];
    lint Ans=0; 
    for(int i=0; i<=N-1; i++)
    Ans += Tree(N-1-i)*Tree(i);
    return DP[N]=Ans;
}

int main()
{
    int X; scanf("%d", &X);
    printf("%lld\n", Tree(X));
    return 0;
}
