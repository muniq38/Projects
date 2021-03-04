
#include <bits/stdc++.h>
using namespace std;
vector<int> Check(13);
int N, Count=0, Ans=0;

void BackTrack(int i, int j){ // i번째 행 j번째 열에 놓았을 때
    for(int k=0; k<i; k++) if(Check[k]==j || k-i==Check[k]-j || i-k==Check[k]-j) return; // 불가능하면 0
    Check[i]=j;
    if(i==N-1){ Ans++; return; } // 가능한데 마지막 행이었다면 1추가
    for(int k=0; k<N; k++) BackTrack(i+1,k); // i+1번째 행 k=1~N-1번째 열에 놓았을 때
}

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; i++) BackTrack(0,i);
    printf("%d\n", Ans);
    return 0;
}

