
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> Board(3);
int DP[20][5][5]={}, Idx[20]={};

int nearHanoi(int N, int From, int To, int Else){
    if(!N) return 0;
    if(DP[N][From][To]) return DP[N][From][To];
    int Ans=0;
    if(abs(From-To)==1){
        Ans += nearHanoi(N-1,From,Else,To); Ans++;
        Ans += nearHanoi(N-1,Else,To,From);
    }else{
        Ans += nearHanoi(N-1,From,To,Else); Ans++;
        Ans += nearHanoi(N-1,To,From,Else); Ans++;
        Ans += nearHanoi(N-1,From,To,Else);
    }return DP[N][From][To]=Ans;
}

int fullHanoi(int N, int From, int To, int Else){ // Obj = 0,1,2
    if(!N) return 0;
    if(From==To) return fullHanoi(N-1,Idx[N-1],To,3-Idx[N-1]-To);
    int Ans=0;
    if(abs(From-To)==1){ // From = A, To = B, Else = C (ex)
        Ans += fullHanoi(N-1,Idx[N-1],Else,3-Idx[N-1]-Else); Ans++;
        Ans += nearHanoi(N-1,Else,To,From);
    }else{
        Ans += fullHanoi(N-1,Idx[N-1],To,3-Idx[N-1]-To); Ans++;
        Ans += nearHanoi(N-1,To,From,Else); Ans++;
        Ans += nearHanoi(N-1,From,To,Else);
    }return Ans;
}

int main()
{
    int N, M, K, a;
    scanf("%d %d", &N, &M);
    for(int i=0; i<3; i++){
        scanf("%d", &K);
        for(int j=0; j<K; j++){
            scanf("%d", &a); 
            Board[i].push_back(N+1-a); 
            Idx[N+1-a]=i;
        }
    }int Ans = min(fullHanoi(N,Idx[N],2,3-Idx[N]-2),fullHanoi(N,Idx[N],0,3-Idx[N]));
    printf("%d\n", Ans, (Ans>M)?-1:Ans);
    return 0;
}
