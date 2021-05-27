
#include <bits/stdc++.h>
#define MOD 9901
using namespace std;
int N, M, Mem[20000][20]={}, Count=0;

vector<int> List;

void makeList(int Bit, int i){
    if(i>=N-1){ List.push_back(Bit); return; }
    makeList(Bit,i+1);
    makeList(Bit|(1<<i)|(1<<(i+1)),i+2);
}

int DP(int Bit, int i){ // 좌측 튀어나온 모양
    Count++;
    if(i==M) return !Bit;
    if(Mem[Bit][i]) return Mem[Bit][i]; 
    for(int k=0; k<N; k++) Bit^=(1<<k); // 일단 빈칸만 1로 세워보자.
    int Ans=0;
    for(int tBit : List){ // tBit = 세로로 꼽을 수 있는 모든 배치비트
        if((tBit & Bit) == tBit) Ans = (Ans+DP(Bit^tBit,i+1))%MOD;
    }return Mem[Bit][i]=Ans;
}

int main()
{
    scanf("%d %d", &N, &M);
    makeList(0,0);
    printf("%d\n", List.size());
    for(int i=M-1; i>=0; i--)
    for(int j=(1<<N)-1; j>=0; j--){ printf("%d %d %d %d\n", j, i, Count, DP(j,i)); Count=0; }
    printf("%d %d\n", Count, DP(0,0));
    return 0;
}

