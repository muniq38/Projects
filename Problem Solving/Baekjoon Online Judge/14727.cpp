
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main()
{
    int N; lint Ans=0; scanf("%d", &N);
    stack<int> Hei, Len; 
    Hei.push(0); Len.push(0);
    
    for(int i=0; i<N; i++){
        int pHei, pLen=0; scanf("%d", &pHei);
        while(Hei.top()>pHei){
            pLen += Len.top();
            Ans = max(Ans, (lint)Hei.top()*pLen);
            Len.pop(); Hei.pop();
        }Len.push(++pLen); Hei.push(pHei);
    }
    
    int pLen=0;
    while(Hei.top()){
        pLen += Len.top();
        Ans = max(Ans, (lint)Hei.top()*pLen);
        Len.pop(); Hei.pop();
    }
    
    printf("%lld\n", Ans);
    return 0;
}
