
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, a, b, K, Count=0, I, i; 
    scanf("%d", &N); int M, m;
    queue<int> Maja, Majb, Mina, Minb;
    vector<int> Ans(N+1);
    Maja.push(1); Majb.push(N);
    
    while(!Maja.empty() || !Majb.empty()){
        M = Maja.size(); m = Mina.size(); I=0; i=0;
        while(i!=m || I!=M){
    
            if( i==m || ( I!=M && Maja.front()<Mina.front()) ){
                a = Maja.front(); b = Majb.front(); 
                Maja.pop(); Majb.pop(); I++; 
                K = (a+b)/2; Ans[K] = Count+I;
                if(b-a==1) continue; // Minor 1 예외처리
                
                if((b-a)%2){
                    if(K+1<=b){ Maja.push(K+1); Majb.push(b); }
                    if(a<=K-1){ Mina.push(a); Minb.push(K-1); }
                } else {
                    if(a<=K-1){ Maja.push(a); Majb.push(K-1); }
                    if(K+1<=b){ Maja.push(K+1); Majb.push(b); }
                }
            } else {
                a = Mina.front(); b = Minb.front();
                Mina.pop(); Minb.pop(); i++; 
                if(a==b){ i--; m--; continue; } // Minor 1 예외처리
                K = (a+b)/2; Ans[K] = M+Count+i;
            
                if((b-a)%2){
                    if(K+1<=b){ Maja.push(K+1); Majb.push(b); }
                    if(a<=K-1){ Mina.push(a); Minb.push(K-1); }
                }else{
                    if(a<=K-1){ Mina.push(a); Minb.push(K-1); }
                    if(K+1<=b){ Mina.push(K+1); Minb.push(b); }
                }
            }
        } Count += M+m;
    }
    
    for(int i=1; i<=N; i++) 
    printf("%d ", Ans[i]?Ans[i]:++Count);
    return 0;
}




