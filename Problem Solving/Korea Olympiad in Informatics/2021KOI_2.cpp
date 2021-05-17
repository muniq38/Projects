
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main(){
    int N, K;
    lint A0, B0, C0, D0;
    priority_queue<lint, vector<lint>> A, B, C, D;
    scanf("%d %d\n", &N, &K);
    scanf("%lld %lld %lld %lld\n", &A0, &B0, &C0, &D0);
    char X; lint Val;
    while(N--){
        scanf("%c %lld\n", &X, &Val);
        switch(X){
            case 'A': A.push(Val); break;
            case 'B': B.push(Val); break;
            case 'C': C.push(Val); break;
            case 'D': D.push(Val); break;
            default: printf("ERROR\n"); break;
        }
    }

    lint dA, dB, dC, dD;
    while(K--){
        dA=dB=dC=dD=0;
        if(!A.empty()){ dA=A.top(); A.pop(); }
        if(!B.empty()){ dB=B.top(); B.pop(); }
        if(!C.empty()){ dC=C.top(); C.pop(); }
        if(!D.empty()){ dD=D.top(); D.pop(); }
        if((A0+dA)*B0 > (B0+dB)*A0 && (A0+dA)*C0 > (C0+dC)*A0 && (A0+dA)*D0 > (D0+dD)*A0){
            A0 += dA; printf("A %lld\n", dA);
            B.push(dB); C.push(dC); D.push(dD);
        }else if((B0+dB)*C0 > (C0+dC)*B0 && (B0+dB)*D0 > (D0+dD)*B0){
            B0 += dB; printf("B %lld\n", dB);
            A.push(dA); C.push(dC); D.push(dD);
        }else if((C0+dC)*D0 > (D0+dD)*C0){
            C0 += dC; printf("C %lld\n", dC);
            B.push(dB); A.push(dA); D.push(dD);
        }else{
            D0 += dD; printf("D %lld\n", dD);
            B.push(dB); C.push(dC); A.push(dA);
        }
    }
}
