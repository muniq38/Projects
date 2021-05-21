
#include <bits/stdc++.h>
#define INF 1000000007
using namespace std;
typedef long long lint;
lint Mem[1200000]={};
lint DMem[1200000]={};

/*
lint DoubleHanoi(int N){ // A B -> C
    lint Ans=0;
    Ans += Merge(N-1);
    Ans++;
    Ans += 2*Hanoi3(N-1);
    Ans++;
    Ans += 2*Hanoi3(N-1);
    return Ans;
}

lint Merge(int N){ // A B -> A
    lint Ans=0;
    Ans += DoubleHanoi(N-1);
    Ans++;
    Ans += 2*Hanoi3(N-1);
    return Ans;
}
*/

lint Hanoi3(int N){
    if(N==1) return 1;
    if(Mem[N]) return Mem[N];
    return Mem[N]=(2*Hanoi3(N-1)+1)%INF;    
}

lint DoubleHanoi(int N){
    if(N==1) return 2;
    if(N==2) return 7;
    if(DMem[N]) return DMem[N];
    lint Ans=0;
    Ans = DoubleHanoi(N-2);
    Ans++; Ans %= INF;
    Ans += 2*Hanoi3(N-2);
    Ans++; Ans %= INF;
    Ans += 4*Hanoi3(N-1);
    Ans++; Ans %= INF;
    return DMem[N]=Ans;
}

int main(){
    int N; scanf("%d", &N);
    for(int i=1; i<=N; i++) Hanoi3(i);
    for(int i=1; i<=N; i++) DoubleHanoi(i);
    printf("%lld\n", DoubleHanoi(N));
    return 0;
}
