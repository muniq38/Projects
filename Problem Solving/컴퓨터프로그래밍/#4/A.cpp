
#include <bits/stdc++.h>
using namespace std;

int Hanoi(int N, int From, int To, int Else){
    if(N==1) return 1;
    int Ans=0;
    Ans += Hanoi(N-1,From,Else,To); Ans++;
    Ans += Hanoi(N-1,Else,To,From);
    return Ans;
}

void Print(int N, int From, int To, int Else){
    if(N==1){ printf("move disk 1 %c->%c\n", From+'A', To+'A'); return; }
    Print(N-1,From,Else,To);
    printf("move disk %d %c->%c\n", N, From+'A', To+'A'); 
    Print(N-1,Else,To,From);
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Hanoi(N,0,2,1));
    Print(N,0,2,1);
    return 0;
}
