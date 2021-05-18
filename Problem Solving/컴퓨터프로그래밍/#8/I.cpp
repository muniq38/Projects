
#include <bits/stdc++.h>
using namespace std;
struct tple{ int x; int y; int dir=0; };
char Board[12][12]={}; int N=10;
int mv[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

void Move(tple& Thing){
    int X = Thing.x, Y = Thing.y, Dir = Thing.dir;
    if(Board[X+mv[Dir][0]][Y+mv[Dir][1]] == '*'){
        Thing.dir = (Dir+1)%4;
    }else{
        Thing.x = X+mv[Dir][0];
        Thing.y = Y+mv[Dir][1];
    }
}

int main()
{
    tple Cow, Fmr; int Ans=0;
    for(int i=0; i<=N+1; i++) for(int j=0; j<=N+1; j++) Board[i][j]='*';
    for(int i=1; i<=N; i++) scanf("%s", Board[i]+1);
    
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++){
        if(Board[i][j]=='C'){ Cow.x = i; Cow.y = j; }
        if(Board[i][j]=='F'){ Fmr.x = i; Fmr.y = j; } 
    }
    
    while((Cow.x != Fmr.x || Cow.y != Fmr.y) && Ans<1000000){ Move(Cow); Move(Fmr); Ans++; 
        //printf("\n%d %d %d\n%d %d %d\n", Cow.x, Cow.y, Cow.dir, Fmr.x, Fmr.y, Fmr.dir); 
    }printf("%d\n", (Ans<1000000)?Ans:0);
    return 0;
}

