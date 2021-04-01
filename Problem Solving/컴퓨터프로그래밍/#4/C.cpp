
#include <bits/stdc++.h>
using namespace std;
int H3[40]={}, H4[40]={};

int Hanoi3(int N){
    if(!N) return 0;
    if(H3[N]) return H3[N];
    int Ans=0;
    Ans += Hanoi3(N-1); Ans++; Ans += Hanoi3(N-1);
    return H3[N]=Ans;
}

int Hanoi4(int N){
    if(!N) return 0;
    if(H4[N]) return H4[N];
    int Min=Hanoi3(N), Ans=0;
    for(int k=1; k<N; k++){
        Ans=0;
        Ans += Hanoi4(k); 
        Ans += Hanoi3(N-k); 
        Ans += Hanoi4(k);
        Min=min(Min,Ans);
    }return H4[N]=Min;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Hanoi4(N));
    return 0;
}

