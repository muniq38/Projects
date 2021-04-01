#include <bits/stdc++.h>  
using namespace std;  
  
int Hanoi3(int N){  
    if(!N) return 0;  
    int Ans=0;  
    Ans += Hanoi3(N-1); Ans++;   
    Ans += Hanoi3(N-1);  
    return Ans;  
}  
  
int Double(int N){ // A and B -> C  
    if(!N) return 0;  
    if(N==1) return 2;  
    int Ans=0;  
    //Ans += Merge(N-1);  
    Ans += Double(N-2); Ans++;  
    Ans += Hanoi3(N-2)*2; Ans++;  
    Ans += Hanoi3(N-1)*2; Ans++;  
    Ans += Hanoi3(N-1)*2;  
    return Ans;  
}  
  
/* 
int Merge(int N){ // A and B -> A 
    Ans += Double(N-1); 
    Ans++; 
    Ans += Hanoi3(N-1)*2; 
} 
*/  
  
int main()  
{  
    int N; scanf("%d", &N);  
    printf("%d\n", Double(N));  
    return 0;  
}  