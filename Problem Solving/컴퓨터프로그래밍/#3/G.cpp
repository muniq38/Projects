
#include <bits/stdc++.h>
using namespace std;

int Board[1100][1100]={};

void Search(int size, int i, int j){
    int Fail=0;
    for(int I=i; I<i+size; I++) for(int J=j; J<j+size; J++){
        if(Board[I][J]!=Board[i][j]) Fail=1;
        if(I==i+size-1 && J==j+size-1 && !Fail){ 
            printf("%d", Board[i][j]); return; 
        }
    }printf("X");
    Search(size/2, i, j);
    Search(size/2, i, j+(size/2));
    Search(size/2, i+(size/2), j);
    Search(size/2, i+(size/2), j+(size/2));
}

int main(){
    int N; scanf("%d", &N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++)
    scanf("%d", &Board[i][j]);
    Search(N,0,0);
    return 0;
}
