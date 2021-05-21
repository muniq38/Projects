
#include <bits/stdc++.h>
using namespace std;

void Res(int a, int b){
    if(a==b) return;
    if(a>b){ printf("R"); Res(b,a-b); }
    else{ printf("L"); Res(b-a,a); }
}

int main()
{
    int a, b; scanf("%d/%d", &a, &b);
    Res(a,b); 
    return 0;
}

/* 풀이

1/(bird+1) = L연산 : a/b -> b/(a+b)
(1/bird)+1 = R연산 : a/b -> (a+b)/a

LRR로 갈수 있는 노드의 값 A/B
= 1/1부터 R연산, R연산, L연산으로 얻어짐 

그러므로 A/B에서 L역, R역, R역 연산을 해주면 1/1

L역연산 : a/b -> (b-a)/a : b>a이면
R역연산 : a/b -> b/(a-b) : a>b이면
a=b : 종결조건

*/