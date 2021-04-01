
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint H3[110]={}, H4[110]={}, Tri[110]={}, Sq[110]={};

lint Hanoi3(int N){
    if(!N) return 0;
    if(H3[N]) return H3[N];
    lint Ans=0;
    Ans += Hanoi3(N-1); Ans++; Ans += Hanoi3(N-1);
    return H3[N]=Ans;
}

lint Hanoi4(int N){
    if(!N) return 0;
    if(N==1) return 1;
    if(H4[N]) return H4[N];
    lint Min=1000000000000, Ans=0;
    for(int k=1; k<N; k++){
        Ans=0; if(N-k>60) continue;
        Ans += Hanoi4(k); 
        Ans += Hanoi3(N-k); 
        Ans += Hanoi4(k);
        Min = min(Min,Ans);
    }return H4[N]=Min;
}

lint TriDouble(int N){ 
    if(!N) return 0;  
    if(N==1) return 2;  
    if(Tri[N]) return Tri[N];
    lint Ans=0;   
    Ans += TriDouble(N-2); Ans++;  
    Ans += Hanoi3(N-2)*2; Ans++;  
    Ans += Hanoi3(N-1)*2; Ans++;  
    Ans += Hanoi3(N-1)*2;  
    return Tri[N]=Ans;  
}  
  
lint SqDouble(int N){ 
    if(!N) return 0;
    if(N==1) return 2;
    if(Sq[N]) return Sq[N];
    lint Min=1000000000000, Ans=0;
    for(int k=1; k<N; k++){
        Ans=0; if(N-k>60) continue;
        Ans += SqDouble(k);
        Ans += TriDouble(N-k);
        Ans += Hanoi4(k)*2;
        Min = min(Min,Ans);
    }return Sq[N]=Min;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%lld\n", SqDouble(N));
    return 0;
}
