
#include <bits/stdc++.h>
using namespace std;
int idx=0, Board[1100][1100]={};
string Str;

void Read(int i, int j, int size){
    if(Str[idx]=='X'){ 
        idx++;
        Read(i,j,size/2); Read(i,j+size/2,size/2);
        Read(i+size/2,j,size/2); Read(i+size/2,j+size/2,size/2);
        return;
    }for(int I=i; I<i+size; I++) for(int J=j; J<j+size; J++) 
    Board[I][J]=Str[idx]-'0'; idx++;
}

int main()
{
    int N; scanf("%d", &N);
    cin >> Str;
    Read(0,0,N);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) printf("%d ", Board[i][j]);
        printf("\n"); 
    }return 0;
}
