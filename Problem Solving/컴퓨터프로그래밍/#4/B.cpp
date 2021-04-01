
#include <bits/stdc++.h>
using namespace std;

int Print(int N, int From, int To, int Else){
    if(!N) return 0;
    int Ans=0;
    if(abs(From-To)==1){
        Ans += Print(N-1,From,Else,To);
        printf("%d : %c->%c\n", N, From+'A', To+'A'); Ans++;
        Ans += Print(N-1,Else,To,From);
    }else{
        Ans += Print(N-1,From,To,Else);
        printf("%d : %c->%c\n", N, From+'A', Else+'A'); Ans++;
        Ans += Print(N-1,To,From,Else);
        printf("%d : %c->%c\n", N, Else+'A', To+'A'); Ans++;
        Ans += Print(N-1,From,To,Else);
    }return Ans;
}

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", Print(N,0,2,1));
    return 0;
}
