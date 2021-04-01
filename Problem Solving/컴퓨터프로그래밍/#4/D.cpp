
#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int Count=0;

void Print(int N, int From, int To, int Else){ // From From
    if(!N) return;
    if(Count>=100) return;
    Print(N-1,From,To,Else); if(Count>=100) return; // From To
    printf("%d : %c->%c\n", N, 'A'+From, 'A'+Else); // Else To
    Count++; if(Count>=100) return;
    Print(N-1,To,From,Else); if(Count>=100) return; // Else From
    printf("%d : %c->%c\n", N, 'A'+Else, 'A'+To); // To From
    Count++; if(Count>=100) return;
    Print(N-1,From,To,Else); // To To
}

/*
int Hanoi(int N, int From, int To, int Else){ // From From
    if(!N) return 0;
    int Ans=0;
    Ans += Hanoi(N-1,From,To,Else); Ans++;
    Ans += Hanoi(N-1,To,From,Else); Ans++; 
    Ans += Hanoi(N-1,From,To,Else); 
    return Ans;
}  //Results = 2 10 42 170 682 2730 ...
*/

int main()
{
    int N; scanf("%d", &N);
    Print(min(N,20),0,1,2);
    vector<long long> Exp(12000000); Exp[0]=1;
    for(int i=1; i<=N; i++) Exp[i]=(Exp[i-1]*3)%MOD;
    printf("%lld\n", Exp[N]-1);
    return 0;
}
