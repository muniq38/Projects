
#include <bits/stdc++.h>
using namespace std;
int Board[15][15]={};
vector<int> Check(200);
int N;

int BackTrack(int i, int j, int mode){ // 칸 i에 j번째 말을 놓을 때
    for(int k=1; k<j; k++) if(abs((Check[k]/N)-(i/N))==abs((Check[k]%N)-(i%N))) return j-1; // i에 불가능하면 종료
    int Max=j; Check[j]=i; // i에 설치
    for(int k=i+1; k<N*N; k++) if(Board[k/N][k%N] && ((k/N)+(k%N))%2==mode) Max=max(Max,BackTrack(k,j+1,mode)); // k(i+1~N*N)번째 칸에 j+1번째
    return Max;
}

int main()
{
    int Ans1=0, Ans2=0;
    scanf("%d", &N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) scanf("%d", &Board[i][j]);
    for(int i=1; i<N*N; i++) if(Board[i/N][i%N] && ((i/N)+(i%N))%2) Ans1 = max(Ans1, BackTrack(i,1,1));
    for(int i=0; i<N*N; i++) if(Board[i/N][i%N] && !(((i/N)+(i%N))%2)) Ans2 = max(Ans2, BackTrack(i,1,0));
    printf("%d\n", Ans1+Ans2);
    return 0;
}


