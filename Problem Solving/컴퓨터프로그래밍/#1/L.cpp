
#include <bits/stdc++.h>
using namespace std;
int Score=0;

void Hanoinum(int N, char from, char to, char els){ // from에서 to로
    if(N==1){ Score++; return; }
    Hanoinum(N-1, from, els, to);
    Score++;
    Hanoinum(N-1, els, to, from);
}


void Hanoi(int N, char from, char to, char els){ // from에서 to로
    if(N==1){ printf("move disk 1 %c->%c\n", from, to); return; }
    Hanoi(N-1, from, els, to);
    printf("move disk %d %c->%c\n", N, from, to); 
    Hanoi(N-1, els, to, from);
}

int main()
{
    int N; scanf("%d", &N);
    Hanoinum(N,'A','C','B'); 
    printf("%d\n", Score);
    Hanoi(N,'A','C','B');
    return 0;
}
