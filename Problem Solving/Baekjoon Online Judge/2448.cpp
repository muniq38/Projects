
#include <bits/stdc++.h>
using namespace std;

char Ans[4000][8000]={};
int Exp[12]={1,2,4,8,16,32,64,128,256,512,1024,2048};

void Fill(int X, int Y, int N){
    if(N==1){
        Ans[X][Y]='*'; Ans[X+1][Y-1]=Ans[X+1][Y+1]='*';
        for(int i=-2; i<=2; i++) Ans[X+2][Y+i]='*';
        return;
    }
    
    Fill(X,Y,N-1);
    Fill(X+3*Exp[N-2],Y-3*Exp[N-2],N-1); // 2일때 2, 3일때 5
    Fill(X+3*Exp[N-2],Y+3*Exp[N-2],N-1);
}

int main()
{
    int N; scanf("%d", &N); 
    for(int i=0; i<=10; i++) if(N==Exp[i]*3){ N=i+1; break; }
    Fill(1,3*Exp[N-1],N);
    for(int i=1; i<=3*Exp[N-1]; i++){
        for(int j=1; j<=3*Exp[N]-1; j++) printf("%c", Ans[i][j]?Ans[i][j]:' ');
        printf("\n");
    }
}
