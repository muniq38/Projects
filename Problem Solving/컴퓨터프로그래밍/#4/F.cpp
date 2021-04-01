
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long lint;
lint H3[1500000]={}, Db[1500000]={};

lint Hanoi3(int N){
    if(!N) return 0;
    if(H3[N]) return H3[N];
    lint Ans=0;
    Ans += Hanoi3(N-1); Ans++; 
    Ans += Hanoi3(N-1);
    return H3[N]=Ans%MOD;
}

lint Double(int N){ // A and B -> C
    if(!N) return 0;
    if(N==1) return 2;
    if(Db[N]) return Db[N];
    lint Ans=0;
    //Ans += Merge(N-1);
    Ans += Double(N-2); Ans++;
    Ans += Hanoi3(N-2)*2; Ans++;
    Ans += Hanoi3(N-1)*2; Ans++;
    Ans += Hanoi3(N-1)*2;
    return Db[N]=Ans%MOD;
}

/*
int Merge(int N){ // A and B -> A
    Ans += Double(N-1);
    Ans++;
    Ans += Hanoi3(N-1)*2;
}
*/

int main()
{
    int N; scanf("%d", &N);
    for(int i=2; i<=N; i++) Double(i);
    printf("%lld\n", Double(N));
    return 0;
}

