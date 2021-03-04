
#include <bits/stdc++.h>
using namespace std;
vector<int> Line;

void LineSwap(int x, int y){
    if(x>y) swap(x,y);
    for(int i=x; i<=(x+y)/2; i++){
        int temp = Line[i];
        Line[i] = Line[x+y-i];
        Line[x+y-i] = temp;
    }
}

int main(){
    int N, A=0, B=0, pA=0, pB=0; scanf("%d", &N);
    Line.resize(N+2); Line[N+1]=N+1;
    for(int i=1; i<=N; i++) scanf("%d", &Line[i]);
    for(int i=0; i<=N; i++){
        if(Line[i]==i && Line[i+1]!=i+1) A=i+1;
        if(Line[i]!=i && Line[i+1]==i+1) B=i;
    }if(A==0 && B==0){ printf("1 1\n2 2\n"); return 0; }
    
    for(int i=1; i<=N; i++) if(Line[i]==A) pA=i;
    LineSwap(A,pA); 
    for(int i=1; i<=N; i++) if(Line[i]==B) pB=i;
    LineSwap(B,pB);
    for(int i=1; i<=N; i++){
        if(Line[i]!=i){ LineSwap(B,pB); LineSwap(A,pA); break; }
        if(i==N){ printf("%d %d\n%d %d\n", min(A,pA), max(A,pA), min(B,pB), max(B,pB)); return 0; }
    }
    
    for(int i=1; i<=N; i++) if(Line[i]==B) pB=i;
    LineSwap(B,pB);
    for(int i=1; i<=N; i++) if(Line[i]==A) pA=i;
    LineSwap(A,pA);
    for(int i=1; i<=N; i++){
        if(Line[i]!=i){ LineSwap(A,pA); break; }
        if(i==N){ printf("%d %d\n%d %d\n", min(B,pB), max(B,pB), min(A,pA), max(A,pA)); return 0; }
    }
    
    printf("%d %d\n", min(B,pB), max(B,pB));
    for(int i=0; i<=N; i++) if(Line[i]==i && Line[i+1]!=i+1) A=i+1;
    for(int i=1; i<=N; i++) if(Line[i]==A) pA=i;
    printf("%d %d\n", min(A,pA), max(A,pA));
    return 0; 
}