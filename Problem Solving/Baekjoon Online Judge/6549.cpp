
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main()
{
    while(1){
        int N; lint Ans=0; 
        scanf("%d", &N); if(!N) return 0;
        stack<lint> Hei, Len;
        Hei.push(-1); Len.push(0);
    
        for(int i=0; i<N; i++){
            lint pHei, pLen=0; scanf("%lld", &pHei);
            while(pHei<=Hei.top()){
                pLen += Len.top(); 
                Ans = max(Ans, pLen*Hei.top());
                Len.pop(); Hei.pop();
            }Hei.push(pHei); Len.push(++pLen);
        }
        
        int pLen=0;
        while(Hei.top()>=0){
            pLen += Len.top();
            Ans = max(Ans, pLen*Hei.top());
            Len.pop(); Hei.pop();
        }printf("%lld\n", Ans);
    }
}
