#include <bits/stdc++.h> 
#define MAXN 1000010 
typedef long long lint;
lint arr[MAXN]; 
lint tree[3*MAXN]={}, lazy[3*MAXN]={};


lint Init(int X, int xl, int xr){ // 배열을 보며 초기 트리 생성
    int xm = (xl+xr)/2;
    if(xl == xr) return tree[X] = arr[xl]; 
    else return tree[X] = Init(X*2,xl,xm) + Init(X*2+1,xm+1,xr); 
} 

void Prop(int X, int xl, int xr){ // lazy 비우기
    tree[X] += (xr-xl+1)*lazy[X]; 
    if(xl != xr){ lazy[X*2] += lazy[X]; lazy[X*2+1] += lazy[X]; }
    lazy[X] = 0; 
}

void LRQuery(int X, int xl, int xr, int L, int R, lint Q){ // 구간 Q 처리
    Prop(X, xl, xr); int xm = (xl+xr)/2;
    if(L > xr || R < xl) return; 
    if(L <= xl && xr <= R){ lazy[X] = Q; Prop(X, xl, xr); return; } 
    LRQuery(X*2, xl, xm, L, R, Q); LRQuery(X*2+1, xm+1, xr, L, R, Q); 
    tree[X] = tree[X*2] + tree[X*2+1];  
} 

lint Sum(int X, int xl, int xr, int L, int R){ // 구간에 들어온 쿼리 처리하기 
    Prop(X, xl, xr); int xm = (xl+xr)/2;
    if(L > xr || R < xl) return 0; 
    if(L <= xl && xr <= R) return tree[X]; 
    return Sum(X*2, xl, xm, L, R) + Sum(X*2+1, xm+1, xr, L, R); 
} 

int main(){ 
    int N, M, K; 
    scanf("%d%d%d", &N, &M, &K); 
    for(int i=1; i<= N; i++) scanf("%lld", &arr[i]); 
    Init(1, 1, N); 
    for(int i=1; i<= M+K; i++){ 
        int t1, a, b; lint Q; 
        scanf("%d", &t1); 
        if(t1==1){ 
            scanf("%d %d %lld", &a, &b, &Q); 
            LRQuery(1, 1, N, a, b, Q); 
        }else{ 
            scanf("%d %d", &a, &b); 
            printf("%lld\n", Sum(1, 1, N, a, b)); 
        } 
    } 
}

