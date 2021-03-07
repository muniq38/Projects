
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main()
{
    string s; cin >> s;
    int N = s.size();
    long long Ans=0;
    vector<int> Rem(N), Sum(N), Count(2019);
    Rem[0]=1;
    for(int i=1; i<N; i++) Rem[i]=(Rem[i-1]*10)%2019;
    for(int i=N-1; i>=0; i--){ Rem[N-1-i]*=(s[i]-'0'); Rem[N-1-i]%=2019; }
    Sum[0]=Rem[0]; Count[0]++; Count[Sum[0]]++;
    for(int i=1; i<N; i++){ Sum[i]=(Sum[i-1]+Rem[i])%2019; Count[Sum[i]]++; }
    for(int i=0; i<2019; i++) Ans += (lint)Count[i]*(Count[i]-1)/2;
    printf("%lld\n", Ans);
    return 0;
}
