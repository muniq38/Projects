
#include <bits/stdc++.h>
using namespace std;
int Board[15][15]={};
vector<int> Check(200);
int N;

int BackTrack(int i, int j){ // 칸 i에 j번째 말을 놓을 때
    int Max=0;
    for(int k=0; k<j; k++) if(abs((Check[k]/5)-(i/5))==abs((Check[k]%5)-(i%5))) return j-1; // i에 불가능하면 종료
    if(i==N*N-1) return j; // 설치 가능한데 i가 마지막 칸이었다면 j 반환
    Check[j]=i; // i에 설치
    for(int k=i+1; k<N*N; k++) if(Board[k/5][k%5]) Max=max(Max,BackTrack(k,j+1)); // k(i+1~N*N)번째 칸에 j+1번째
    return Max;
}

int main()
{
    int Ans=-1;
    scanf("%d", &N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) scanf("%d", &Board[i][j]);
    for(int i=0; i<N*N; i++) if(Board[i/5][i%5]) Ans = max(Ans, BackTrack(i,0)); 
    printf("%d\n", Ans+1);
    return 0;
}

