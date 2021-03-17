
#include <bits/stdc++.h>
using namespace std;

int Star(int N){
   if(!N) return 0;
   int Ans=0;
   Ans += Star(N-1);
   for(int i=0; i<N; i++) printf("*"); printf("\n");
   Ans += N+Star(N-1);
   return Ans;
}

int main(){
   int N; scanf("%d", &N);
   printf("%d\n", Star(N));
   return 0;
}
