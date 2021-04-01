
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int N;
long long DP[250][1100]={};
int Exp[6]={0,1,3,9,27,81};
vector<int> P(10);

long long mHanoi(int X, int M){ 
    if(!M) return (X==Exp[N]*3-1);
    if(X>Exp[N]*3-1){ printf("씨발\n"); return 0; }
    if(X==Exp[N]*3-1) return 0;
    if(DP[X][M]) return DP[X][M];
    int a=10, b=10, c=10, Y=X;
    long long Ans=0;
    for(int i=1; i<=N; i++){ 
        switch(Y%3){
            case 0: if(a==10) a=i; break;
            case 1: if(b==10) b=i; break;
            case 2: if(c==10) c=i; break;
        }Y/=3; 
    }if(a!=10 || b!=10){
        if(a>b) Ans += mHanoi(X-Exp[b],M-1); 
        else Ans += mHanoi(X+Exp[a], M-1); 
        Ans %= MOD;
    }if(a!=10 || c!=10){
        if(a>c) Ans += mHanoi(X-2*Exp[c], M-1); 
        else Ans += mHanoi(X+2*Exp[a], M-1);
        Ans %= MOD;
    }if(b!=10 || c!=10){
        if(b>c) Ans += mHanoi(X-Exp[c], M-1);
        else Ans += mHanoi(X+Exp[b], M-1);
        Ans %= MOD;
    }return DP[X][M]=Ans;
}

int main()
{
    int M;
    scanf("%d %d", &N, &M);
    long long Ans=0;
    for(int i=1; i<=3*Exp[N]-1; i++) for(int j=1; j<=1000; j++) mHanoi(i,j);
    for(int i=1; i<=M; i++) Ans = (Ans+mHanoi(0,i))%MOD;
    printf("%lld\n", Ans);
    return 0;
}

