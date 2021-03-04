
#include <bits/stdc++.h>
using namespace std;
int Cur[30]={}, idx=0;

void star(int n, int k){ // n개 출력해야 하고, 현재 줄에 최대 k개 출력가능 (n>=k)
    if(n && k==0) return; // star(n,k-1)을 반복하다 보면 star(n,0)으로 옴 - 종료
    if(n==0){ // 만약 별을 다 소진한 상태 - 스택에서 출력
        for(int i=0; i<idx; i++){ 
            for(int j=0; j<Cur[i]; j++) printf("*"); 
            printf("\n");
        }printf("\n"); return;
    }Cur[idx++]=k; // k개를 쓸 수 있음 - 사용하고 스택에 넣기
    star(n-k,min(k,n-k)); // 현재 층에 k개를 쓴경우 - star(n-k,min(k,n-k))
    idx--; star(n,k-1); // k보다 적게 쓸거라면 - star(n,k-1)로 재귀
}

int main()
{
    int N; scanf("%d", &N);
    star(N,N);
    return 0;
}
