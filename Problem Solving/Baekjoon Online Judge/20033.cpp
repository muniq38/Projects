
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, Ans=0; scanf("%d", &N);
    
    stack<int> Hei, Len;
    Hei.push(0); Len.push(0);
    
    for(int i=0; i<N; i++){
        int pLen=0, pHei; scanf("%d", &pHei);
        while(Hei.top()>=pHei){
            pLen += Len.top();
            Ans = max(Ans, min(pLen, Hei.top()));
            Hei.pop(); Len.pop();
        }Hei.push(pHei); Len.push(++pLen);
    }
    
    int pLen=0;
    while(Hei.top()){
        pLen += Len.top();
        Ans = max(Ans, min(pLen, Hei.top()));
        Hei.pop(); Len.pop();
    }
    
    printf("%d\n", Ans);
    return 0;
}
