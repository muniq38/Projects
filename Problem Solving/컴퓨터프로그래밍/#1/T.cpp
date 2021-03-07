
#include <bits/stdc++.h>
using namespace std;
int Ans[150000]={};
struct query{ int a; int b; int c; };
vector<query> Query;

void Fill(int x, int y, int i){ // x~y까지 빈칸, i번째 쿼리 수행중
    if(y<x || i<0) return;
    query Q = Query[i];
    if(Q.a>y || Q.b<x) Fill(x,y,i-1); // 색칠범위가 벗어나는 경우
    else if(Q.a<=x && Q.b>=y){
        for(int j=x; j<=y; j++) Ans[j]=Q.c; // 왼쪽 끝 ~ 오른쪽 끝까지 색칠 
        return;
    }else if(Q.a>=x && Q.b>=y){
        for(int j=Q.a; j<=y; j++) Ans[j]=Q.c; // Q.a ~ 오른쪽 끝까지 색칠완료
        Fill(x,Q.a-1,i-1); 
    }else if(Q.b<=y && Q.a<=x){
        for(int j=x; j<=Q.b; j++) Ans[j]=Q.c; // 왼쪽 끝 ~ Q.b까지 색칠완료
        Fill(Q.b+1,y,i-1);
    }else{
        for(int j=Q.a; j<=Q.b; j++) Ans[j]=Q.c; // Q.a ~ Q.b까지 색칠완료
        Fill(x,Q.a-1,i-1); Fill(Q.b+1,y,i-1);
    }
}

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    for(int i=0; i<Q; i++){
        query A;
        scanf("%d %d %d", &A.a, &A.b, &A.c);
        Query.push_back(A);
    }Fill(1, N, Q-1);
    for(int i=1; i<=N; i++) printf("%d ", Ans[i]);
    return 0;
}


